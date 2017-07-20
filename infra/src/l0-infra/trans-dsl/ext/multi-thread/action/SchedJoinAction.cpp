/*
 * SchedJoinAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/ext/multi-thread/action/SchedJoinAction.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "l0-infra/event/concept/Event.h"
#include "l0-infra/trans-dsl/ext/multi-thread/def/ThreadDoneMsg.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/base/Likely.h"

////////////////////////////////////////////////////////////
SchedJoinAction::SchedJoinAction() 
                 : joinPointBitmap(0)
                 , initPointBitmap(0)
{
}

////////////////////////////////////////////////////////////
#define BITMASK(n) (1 << n)

Status SchedJoinAction::reschedule()
{
   return joinPointBitmap > 0 ? USI_CONTINUE : USI_SUCCESS;
}

////////////////////////////////////////////////////////////
bool SchedJoinAction::isWaiting(const ActionThreadId threadId) const
{
   return (joinPointBitmap & ((HostType) BITMASK(threadId))) > 0;
}

////////////////////////////////////////////////////////////
void SchedJoinAction::addThread(const ActionThreadId threadId)
{
   initPointBitmap |= ((HostType) BITMASK(threadId));
}

////////////////////////////////////////////////////////////
void SchedJoinAction::threadDone(const ActionThreadId threadId)
{
   joinPointBitmap &= ~((HostType) BITMASK(threadId));
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::addJoinThread(const ActionThreadId threadId)
{
   if (threadId >= sizeof(HostType) * 8)
   {
      return USI_OUT_OF_SCOPE;
   }

   addThread(threadId);

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::onThreadDone(const ActionThreadId tid, const Status result)
{
   if (__unlikely(!isWaiting(tid)))
   {
      return USI_UNKNOWN_EVENT;
   }

   if(__unlikely(IS_FAILED_STATUS(result)))
   {
      return result;
   }

   threadDone(tid);

   return reschedule();
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::handleEvent(TransactionContext&, const Event& event)
{
   if (!event.matches(EV_ACTION_THREAD_DONE))
   {
      return USI_UNKNOWN_EVENT;
   }

   const ThreadDoneMsg* msg = (const ThreadDoneMsg*) event.getMsg();
   USI_ASSERT_VALID_PTR(msg);

   return onThreadDone(msg->who, msg->result);
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::join(const ActionThreadId threadId,
         TransactionContext& context)
{
    MultiThreadContext* mt = dci::unknown_cast<MultiThreadContext>(&context);
   USI_ASSERT_VALID_PTR(mt);

   Status result = USI_SUCCESS;
   USI_ASSERT_SUCC_CALL(mt->joinThread(threadId, result));
   if (!ActionStatus(result).isWorking())
   {
      threadDone(threadId);
      return result;
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::exec(TransactionContext& context)
{
   joinPointBitmap = initPointBitmap;

   ActionThreadId tid = 0;
   for (HostType bitmap = joinPointBitmap; bitmap > 0; bitmap >>= 1, ++tid)
   {
      if (bitmap & 0x1)
      {
         USI_ASSERT_SUCC_CALL(join(tid, context));
      }
   }

   return reschedule();
}

////////////////////////////////////////////////////////////
Status SchedJoinAction::stop(TransactionContext& context, const Status cause)
{
   kill(context, cause);

   return cause;
}

////////////////////////////////////////////////////////////
void SchedJoinAction::kill(TransactionContext&, const Status)
{
   joinPointBitmap = 0;
}


