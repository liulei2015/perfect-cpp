
/*
 * SchedSwitchCaseAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */


#include "l0-infra/trans-dsl/sched/action/SchedSwitchCaseAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/base/Likely.h"

///////////////////////////////////////////////////////////////////////////////////
SchedSwitchCaseAction::SchedSwitchCaseAction() :
    selectedAction(0)
{
}

///////////////////////////////////////////////////////////////////////////////////
void SchedSwitchCaseAction::pushBackActionPath(ActionPath& path)
{
   paths.pushBack(path);
}

///////////////////////////////////////////////////////////////////////////////////
SchedAction* SchedSwitchCaseAction::findMatchedAction(TransactionContext& context)
{
   LIST_FOREACH(ActionPath, i, paths)
   {
      if(i->shouldExecute(context))
      {
         return &(i->action);
      }
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::exec(TransactionContext& context)
{
   selectedAction = findMatchedAction(context);
   if(selectedAction == 0) return USI_SUCCESS;

   return selectedAction->exec(context);
}

///////////////////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::handleEvent(TransactionContext& context, const Event& event)
{
   if(__unlikely(selectedAction == 0)) return USI_FATAL_BUG;
   return selectedAction->handleEvent(context, event);
}

//////////////////////////////////////////////////////////////////////
Status SchedSwitchCaseAction::stop(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return USI_SUCCESS;
   return selectedAction->stop(context, cause);
}

//////////////////////////////////////////////////////////////////////
void SchedSwitchCaseAction::kill(TransactionContext& context, const Status cause)
{
   if(selectedAction == 0) return;
   selectedAction->kill(context, cause);
}
