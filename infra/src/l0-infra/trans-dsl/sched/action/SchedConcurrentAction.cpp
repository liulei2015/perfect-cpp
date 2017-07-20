/*
 * SchedConcurrentAction.cc
 *
 * Created on: Apr 22, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#include "l0-infra/trans-dsl/sched/action/SchedConcurrentAction.h"
#include "l0-infra/trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "l0-infra/base/Likely.h"

///////////////////////////////////////////////////////////////////////
SchedConcurrentAction::SchedConcurrentAction()
  : stopping(false)
{
}

///////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::init()
{
    SimpleRuntimeContext::init();
    stopping = false;
    threads.concat(idleThreads);
}

////////////////////////////////////////////////////////////////////
inline bool SchedConcurrentAction::hasWorkingThreads() const
{
   return ! threads.isEmpty();
}

////////////////////////////////////////////////////////////////////
inline Status SchedConcurrentAction::getFinalStatus() const
{
   return hasWorkingThreads() ? USI_CONTINUE : objectStatus;
}

////////////////////////////////////////////////////////////////////
inline Status SchedConcurrentAction::process(const ActionStatus status,
         TransactionContext& context)
{
   if (status.eventNotAccepted())
   {
      return status;
   }

   if(__unlikely(IS_FAILED_STATUS(getStatus())))
   {
      doStop(context, getStatus());
   }

   return getFinalStatus();
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::doneCheck(const ActionStatus status, Thread& thread)
{
   if (!status.isWorking())
   {
      threads.erase(thread);
      idleThreads.pushBack(thread);
   }

   if(__unlikely(status.isFailed()))
   {
      reportFailure(status);
   }

   return status;
}

////////////////////////////////////////////////////////////////////
#define DONE_CHECK(thread, method) doneCheck(thread->method, thread)

////////////////////////////////////////////////////////////////////
#define FOREACH_THREAD(thread) \
      LIST_FOREACH(LinkedActionThread, thread, threads)

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::doExec(TransactionContext& context)
{
   FOREACH_THREAD(thread)
   {
      ActionStatus status = DONE_CHECK(thread, exec(context));
      if (__unlikely(status.isFailed()))
      {
         return status;
      }
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::doStop(TransactionContext& context, const Status cause)
{
   if(stopping) return;

   FOREACH_THREAD(thread)
   {
      DONE_CHECK(thread, stop(context, cause));
   }

   stopping = true;
}

///////////////////////////////////////////////////////////////////////
inline Status SchedConcurrentAction::doHandleEvent(TransactionContext& context, const Event& event)
{
   FOREACH_THREAD(thread)
   {
      ActionStatus status = DONE_CHECK(thread, handleEvent(context, event));
      if (status.eventAccepted())
      {
         return status;
      }
   }

   return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////
struct SchedConcurrentAction::AutoSwitch : RuntimeContextAutoSwitch
{
   AutoSwitch(SchedConcurrentAction& action, TransactionContext& context)
        : RuntimeContextAutoSwitch(action, action.parent, context)
   {
   }
};

///////////////////////////////////////////////////////////////////////
#define __AUTO_SWITCH()  AutoSwitch autoSwitch(*this, context)

////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::exec(TransactionContext& context)
{
   init();

   __AUTO_SWITCH();
   return process(doExec(context), context);
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::handleEvent(TransactionContext& context, const Event& event)
{
   __AUTO_SWITCH();
   return process(doHandleEvent(context, event), context);
}

///////////////////////////////////////////////////////////////////////
Status SchedConcurrentAction::stop(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();

   doStop(context, cause);

   return getFinalStatus();
}

///////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::kill(TransactionContext& context, const Status cause)
{
   __AUTO_SWITCH();

   FOREACH_THREAD(thread)
   {
      thread->kill(context, cause);
   }
}

///////////////////////////////////////////////////////////////////////
void SchedConcurrentAction::addThread(LinkedActionThread& thread)
{
   threads.pushBack(thread);
}
