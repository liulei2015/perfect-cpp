/*
 * SchedSafeAction.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/action/SchedSafeAction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

SchedSafeAction::SchedSafeAction()
   : running(false)
{
}

Status SchedSafeAction::final(const Status status)
{
    running = ActionStatus(status).isWorking();

    return status;
}

Status SchedSafeAction::exec(TransactionContext& context)
{
   running = false;

   return final(ROLE(SchedAction).exec(context));
}

Status SchedSafeAction::handleEvent(TransactionContext& context, const Event& event)
{
   if(!running) return USI_UNKNOWN_EVENT;

   return final(ROLE(SchedAction).handleEvent(context, event));
}

Status SchedSafeAction::stop(TransactionContext&, Status)
{
   return running ? USI_CONTINUE : USI_SUCCESS;
}

void SchedSafeAction::kill(TransactionContext& context, Status cause)
{
   if(running) ROLE(SchedAction).kill(context, cause);
}
