/*
 * SchedSafeModeAction.cc
 *
 * Created on: Jun 10, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/action/SchedSafeModeAction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionMode.h"

Status SchedSafeModeAction::final(TransactionContext& context, Status status)
{
   if(__unlikely(!ActionStatus(status).isWorking()))
   {
      USI_ASSERT_SUCC_CALL(context.getTransactionMode().leaveSafeMode());
   }

   return status;
}

#define FINAL(method) final(context, ROLE(SchedAction).method)

Status SchedSafeModeAction::exec(TransactionContext& context)
{
   USI_ASSERT_SUCC_CALL(context.getTransactionMode().enterSafeMode());

   return FINAL(exec(context));
}

Status SchedSafeModeAction::handleEvent(TransactionContext& context, const Event& event)
{
   return FINAL(handleEvent(context, event));
}

Status SchedSafeModeAction::stop(TransactionContext& context, const Status cause)
{
   return FINAL(stop(context, cause));
}

void SchedSafeModeAction::kill(TransactionContext& context, const Status cause)
{
   ROLE(SchedAction).kill(context, cause);
   USI_ASSERT_SUCC_CALL_VOID(context.getTransactionMode().leaveSafeMode());
}

