/*
 * MultiThreadScheduler.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/ext/multi-thread/trans/MultiThreadScheduler.h"
#include "l0-infra/trans-dsl/sched/action/ActionThread.h"
#include "l0-infra/trans-dsl/ext/multi-thread/def/ThreadDoneMsg.h"
#include <l0-infra/event/impl/ConsecutiveEventInfo.h>
#include "l0-infra/event/concept/Event.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/trans-dsl/utils/SimpleRuntimeContextAutoSwitch.h"

/////////////////////////////////////////////////////////////////
MultiThreadScheduler::NamedThread::NamedThread()
   : thread(0)
{
}

/////////////////////////////////////////////////////////////////
inline void MultiThreadScheduler::NamedThread::reset()
{
    thread = 0;
} 

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::NamedThread::start(ActionThread& newThread, MultiThreadScheduler& scheduler)
{
    USI_ASSERT_FALSE(scheduler.stopping);
    USI_ASSERT_TRUE_R(thread == 0, USI_DUPTID);

   thread = &newThread;

   (void) thread->exec(scheduler.ROLE(TransactionContext));

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::NamedThread::handleEvent(MultiThreadScheduler& scheduler, const Event& event)
{
   if(thread == 0 || !thread->isWorking())
   {
      return USI_UNKNOWN_EVENT;
   }

   return thread->handleEvent(scheduler.ROLE(TransactionContext), event);
}

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::NamedThread::stop(MultiThreadScheduler& scheduler, const Status cause)
{
   if(thread == 0 || !thread->isWorking())
   {
      return USI_UNKNOWN_EVENT;
   }

   return thread->stop(scheduler.ROLE(TransactionContext), cause);
}

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::NamedThread::kill(MultiThreadScheduler& scheduler, const Status cause)
{
   if(thread == 0 || !thread->isWorking())
   {
      return USI_CONTINUE;
   }

   thread->kill(scheduler.ROLE(TransactionContext), cause);

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////
inline Status MultiThreadScheduler::NamedThread::getWorkingStatus() const
{
   if (thread == 0 || thread->isWorking())
   {
      return USI_CONTINUE;
   }

   return thread->getThreadStatus();
}

/////////////////////////////////////////////////////////////////
MultiThreadScheduler::MultiThreadScheduler()
  : current(NIL_TID)
  , stopping(false)
{
}

/////////////////////////////////////////////////////////////////
namespace
{
   struct AutoThreadSwitch
   {
      AutoThreadSwitch(const ActionThreadId newThread, ActionThreadId& current)
         : original(current)
         , current(current)
      {
         current = newThread;
      }

      ~AutoThreadSwitch()
      {
         current = original;
      }

   private:
      ActionThreadId original;
      ActionThreadId& current;
   };
}

/////////////////////////////////////////////////////////////////
#define FOREACH_THREAD(tid) \
   for(ActionThreadId tid = 0; tid < MAX_NUM_OF_THREADS; ++tid)

/////////////////////////////////////////////////////////////////
inline void MultiThreadScheduler::doneCheck(const ActionThreadId tid)
{
   ActionStatus status = threads[tid].getWorkingStatus();
   if (!status.isWorking())
   {
      broadcastActionDone(tid, status);
   }
}

/////////////////////////////////////////////////////////////////
inline void MultiThreadScheduler::notifyActionDone(const ActionThreadId tid, const ActionThreadId who, const Status result)
{
   if(tid == who) return;

   (void) handleEventOnThread(tid, ConsecutiveEventInfo(EV_ACTION_THREAD_DONE, ThreadDoneMsg(who, result)));
}

/////////////////////////////////////////////////////////////////
inline void MultiThreadScheduler::broadcastActionDone(const ActionThreadId who, const Status result)
{
   FOREACH_THREAD(tid)
   {
      notifyActionDone(tid, who, result);
   }
}

namespace
{
   struct AutoContextSwitch : SimpleRuntimeContextAutoSwitch
   {
      AutoContextSwitch(RuntimeContext& __THIS__, TransactionContext& context)
           : SimpleRuntimeContextAutoSwitch(__THIS__, context)
      {
      }
   };
}

#define SWITCH_TO(tid) \
   AutoThreadSwitch autoSwitch(tid, current); \
   AutoContextSwitch autoContextSwitch(*this, ROLE(TransactionContext))

/////////////////////////////////////////////////////////////////
#define CHECK_TID_SCOPE(tid)  \
   if (__unlikely(tid >= MAX_NUM_OF_THREADS)) return USI_OUT_OF_SCOPE

Status MultiThreadScheduler::startThread(const ActionThreadId tid, ActionThread& thread, Status& result)
{
   CHECK_TID_SCOPE(tid);

   SWITCH_TO(tid);

   USI_ASSERT_SUCC_CALL(threads[tid].start(thread, *this));
   doneCheck(tid);

   result = threads[tid].getWorkingStatus();

   return USI_SUCCESS;
}

Status MultiThreadScheduler::stopThread(const ActionThreadId tid, const Status cause)
{
   CHECK_TID_SCOPE(tid);

   SWITCH_TO(tid);

   Status status = threads[tid].stop(*this, cause);
   if(status != USI_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }

   return USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::doKillThread(const ActionThreadId tid, const Status cause)
{
   SWITCH_TO(tid);

   if(threads[tid].kill(*this, cause) != USI_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }
}

//////////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::killThread(const ActionThreadId tid, const Status cause)
{
   CHECK_TID_SCOPE(tid);

   USI_ASSERT_FALSE_R(current == tid, USI_INVALID_DATA);

   doKillThread(tid, cause);

   return USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::joinThread(const ActionThreadId tid, Status& result) const
{
   CHECK_TID_SCOPE(tid);
   USI_ASSERT_FALSE_R(current == tid, USI_INVALID_DATA);

   result = threads[tid].getWorkingStatus();

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::doStop(const Status cause)
{
   if (stopping)
   {
      return;
   }

   FOREACH_THREAD(tid)
   {
      (void) stopThread(tid, cause);
   }

   stopping = true;
}

/////////////////////////////////////////////////////////////////
ActionStatus MultiThreadScheduler::getMainThreadStatus() const
{
   return threads[MAIN_TID].getWorkingStatus();
}

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::finalProcess(ActionStatus status)
{
   if (ActionStatus(getStatus()).isFailed())
   {
      doStop(getStatus());
   }

   if (!getMainThreadStatus().isWorking())
   {
      kill(getStatus());
      return getMainThreadStatus();
   }

   return  status == USI_UNKNOWN_EVENT ? USI_UNKNOWN_EVENT : USI_CONTINUE;
}

/////////////////////////////////////////////////////////////////
inline void MultiThreadScheduler::handleEventOnThread(const ActionThreadId tid, const Event& event)
{
   SWITCH_TO(tid);

   Status status = threads[tid].handleEvent(*this, event);
   if(status != USI_UNKNOWN_EVENT)
   {
      doneCheck(tid);
   }
}

/////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::doHandleEvent(const Event& event)
{
   FOREACH_THREAD(tid)
   {
      handleEventOnThread(tid, event);
      if(event.isConsumed())
      {
         return USI_SUCCESS;
      }
   }

   return USI_UNKNOWN_EVENT;
}

void MultiThreadScheduler::init()
{
    SimpleRuntimeContext::init();

    for(int i=0; i<MAX_NUM_OF_THREADS; i++)
    {
        threads[i].reset();
    }

    current = NIL_TID;
    stopping = false;
}

//////////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::startMainThread(ActionThread& thread)
{
    init();

    Status result = USI_SUCCESS;

    return finalProcess(startThread(MAIN_TID, thread, result));
}

//////////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::handleEvent(const Event& event)
{
   return finalProcess(doHandleEvent(event));
}

//////////////////////////////////////////////////////////////////////
Status MultiThreadScheduler::stop(const Status cause)
{
   doStop(cause);
   return finalProcess(USI_SUCCESS);
}

//////////////////////////////////////////////////////////////////////
void MultiThreadScheduler::kill(const Status cause)
{
   FOREACH_THREAD(tid)
   {
      doKillThread(tid, cause);
   }
}

//////////////////////////////////////////////////////////////////////
bool MultiThreadScheduler::isWorking() const
{
   return threads[MAIN_TID].getWorkingStatus() == USI_CONTINUE;
}

