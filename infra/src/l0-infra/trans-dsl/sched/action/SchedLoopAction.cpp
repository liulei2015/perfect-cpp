/*
 * SchedLoopAction.cc
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/action/SchedLoopAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionInfo.h"

///////////////////////////////////////////////////////////
SchedLoopAction::SchedLoopAction() : state(IDLE_STATE), stopCause(USI_SUCCESS)
{
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::restart(TransactionContext& context)
{
   if(state == STOPPED_STATE) return USI_RESTART_REQUIRED;

   while(1)
   {
      ActionStatus status = doRestart(context);
      if(status != USI_RESTART_REQUIRED)
      {
         return status;
      }
   }

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doExec(TransactionContext& context)
{
   if(shouldExecute(context))
   {
      return restart(context);
   }

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::getFinalStatus(const ActionStatus status)
{
   if(status == USI_RESTART_REQUIRED)
   {
      return state == STOPPED_STATE ? stopCause : USI_FATAL_BUG;
   }

   if(!status.isWorking())
   {
      state = IDLE_STATE;
   }
   else
   {
      state = EXEC_STATE;
   }

   return status;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::exec(TransactionContext& context)
{
   return getFinalStatus(doExec(context));
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doRestart(TransactionContext& context)
{
   reset();

   return ROLE(SchedAction).exec(context);
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::doHandleEvent(TransactionContext& context, const Event& event)
{
   Status status = ROLE(SchedAction).handleEvent(context, event);
   if(status == USI_RESTART_REQUIRED)
   {
      return restart(context);
   }

   return status;
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::handleEvent(TransactionContext& context, const Event& event)
{
   return getFinalStatus(doHandleEvent(context, event));
}

///////////////////////////////////////////////////////////
Status SchedLoopAction::stop(TransactionContext& context, const Status cause)
{
   if(state == EXEC_STATE)
   {
      state = STOPPED_STATE;
      stopCause = cause;

      return getFinalStatus(ROLE(SchedAction).stop(context, cause));
   }

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////
void SchedLoopAction::kill(TransactionContext& context, const Status cause)
{
   if(state == EXEC_STATE)
   {
      state = IDLE_STATE;
      ROLE(SchedAction).kill(context, cause);
   }
}

///////////////////////////////////////////////////////////
Status LoopCondCheckAction::exec(TransactionContext& context)
{
   if(shouldExecute(context))
   {
      return USI_RESTART_REQUIRED;
   }

   return context.getStatus();
}

///////////////////////////////////////////////////////////
Status LoopCondCheckAction::handleEvent(TransactionContext&, const Event&)
{
   return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////
void LoopCondCheckAction::kill(TransactionContext&, const Status)
{
}

