/*
 * SchedLockAction.cc
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/ext/mutex/action/SchedLockAction.h"
#include "l0-infra/trans-dsl/ext/mutex/def/TransMutexAvailMsg.h"
#include "l0-infra/trans-dsl/ext/mutex/concept/TransMutexScheduler.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

#include "l0-infra/dci/Unknown.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/event/concept/Event.h"

///////////////////////////////////////////////////////////////////////////////////////////
SchedLockAction::SchedLockAction() : waiting(true)
{
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::lock(TransactionContext& context)
{
   TransMutexScheduler* mutex = dci::unknown_cast<TransMutexScheduler>(&context);
   USI_ASSERT_VALID_PTR(mutex);

   ActionStatus status = mutex->lock(getMutexId());
   if(!status.isDone())
   {
      return status;
   }

   waiting = false;

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::unlock(TransactionContext& context)
{
    TransMutexScheduler* mutex = dci::unknown_cast<TransMutexScheduler>(&context);
   USI_ASSERT_VALID_PTR(mutex);

   mutex->unlock(getMutexId());
   waiting = true;

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::final(Status result, TransactionContext& context)
{
   if(!ActionStatus(result).isWorking())
   {
      USI_ASSERT_SUCC_CALL(unlock(context));
   }

   return result;
}

///////////////////////////////////////////////////////////////////////////////////////////
#define __FINAL(method) final(ROLE(SchedAction).method, context)

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::exec(TransactionContext& context)
{
   waiting = true;

   ActionStatus status = lock(context);
   if(status.isDone())
   {
     return __FINAL(exec(context));
   }

   return status;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::tryExec(TransactionContext& context, const Event& event)
{
   if(event.matches(EV_MUTEX_UNLOCK))
   {
      TransMutexAvailMsg* msg = (TransMutexAvailMsg*)event.getMsg();
      USI_ASSERT_VALID_PTR(msg);

      if(msg->matches(getMutexId()))
      {
         event.consume();
         return exec(context);
      }
   }

   return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::handleEvent(TransactionContext& context, const Event& event)
{
   return waiting ? tryExec(context, event) : __FINAL(handleEvent(context, event));
}

///////////////////////////////////////////////////////////////////////////////////////////
Status SchedLockAction::stop(TransactionContext& context, const Status cause)
{
   if(waiting) return cause;

   return __FINAL(stop(context, cause));
}

///////////////////////////////////////////////////////////////////////////////////////////
void   SchedLockAction::kill(TransactionContext& context, const Status cause)
{
   if(waiting) return;

   ROLE(SchedAction).kill(context, cause);
   unlock(context);
}
