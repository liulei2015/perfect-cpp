/*
 * SchedExcldcmveAction.cc
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */


#include "l0-infra/trans-dsl/sched/action/SchedExclusiveAction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/base/Likely.h"

///////////////////////////////////////////////////////////////////////////
SchedExcldcmveAction::SchedExcldcmveAction()
  : selectedAction(0)
{
}

///////////////////////////////////////////////////////////////////////////
void SchedExcldcmveAction::init()
{
    selectedAction = 0;
    actions.concat(doneActions);
}

///////////////////////////////////////////////////////////////////////////
Status SchedExcldcmveAction::exec(TransactionContext& context)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      ActionStatus status = action->exec(context);
      if(__unlikely(status.isFailed()))
      {
         return status;
      }
      else if(status.isDone())
      {
         actions.erase(action);
         doneActions.pushBack(action);
      }
   }
   selectedAction = 0;
   return actions.isEmpty() ? USI_SUCCESS : USI_CONTINUE;
}

///////////////////////////////////////////////////////////////////////////
void SchedExcldcmveAction::interruptOthers(TransactionContext& context, Status status)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      if(&(*action) != selectedAction)
      {
         action->kill(context, status);
      }
   }
}

///////////////////////////////////////////////////////////////////////////
Status SchedExcldcmveAction::selectAction(TransactionContext& context, const Event& event)
{
   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      ActionStatus status = action->handleEvent(context, event);
      if(status.eventAccepted())
      {
         selectedAction = &(*action);
         interruptOthers(context, status);

         return status;
      }
   }

   return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////////
Status SchedExcldcmveAction::handleEvent(TransactionContext& context, const Event& event)
{
    if(selectedAction == 0)
    {
        return selectAction(context, event);
    }
    else
    {
        ActionStatus status = selectedAction->handleEvent(context, event);
        if(!status.isWorking())
        {
            selectedAction = 0;
        }
        return status;
    }
}

///////////////////////////////////////////////////////////////////////////
Status SchedExcldcmveAction::stop(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0)
   {
      kill(context, cause);
      return cause;
   }
   else
   {
       ActionStatus status =selectedAction->stop(context, cause);
       selectedAction = 0;
       return status;
   }
}

///////////////////////////////////////////////////////////////////////////
void SchedExcldcmveAction::kill(TransactionContext& context, const Status cause)
{
   if(selectedAction != 0)
   {
      selectedAction->kill(context, cause);
      selectedAction = 0;
      return;
   }

   LIST_FOREACH(LinkedSchedAction, action, actions)
   {
      action->kill(context, cause);
   }
}

///////////////////////////////////////////////////////////////////////////
void SchedExcldcmveAction::addAction(LinkedSchedAction& action)
{
   actions.pushBack(action);
}
