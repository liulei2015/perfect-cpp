/*
 * SchedSequentialAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/SchedSequentialAction.h"
#include "l0-infra/base/Likely.h"

///////////////////////////////////////////////////////////////
SchedSequentialAction::SchedSequentialAction() 
    : current(0)
    , finalStatus(USI_SUCCESS)
{
}

///////////////////////////////////////////////////////////////
void SchedSequentialAction::pushBackAction(LinkedSchedAction& action)
{
   actions.pushBack(action);
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::go(TransactionContext& context)
{
    while(!actions.isNull(current))
    {
        ActionStatus status = current->exec(context);
        if(!status.isDone())
        {
            return status;
        }

        current = Actions::getNext(current);
    }

    return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////
inline Status SchedSequentialAction::forward(TransactionContext& context)
{
   current = Actions::getNext(current);
   return go(context);
}

///////////////////////////////////////////////////////////////
inline Status SchedSequentialAction::getFinalStatus(const ActionStatus status)
{
    if(!status.isWorking())
    {
        current = 0;
    }

    return status.isDone() ? finalStatus : (Status)status;
}

///////////////////////////////////////////////////////////////
#define FINAL_STATUS(status) getFinalStatus(status)

inline Status SchedSequentialAction::doExec(TransactionContext& context)
{
    finalStatus = USI_SUCCESS;
    current = actions.first();

    return go(context);
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::exec(TransactionContext& context)
{
   return FINAL_STATUS(doExec(context));
}

///////////////////////////////////////////////////////////////
inline Status SchedSequentialAction::doHandleEvent(TransactionContext& context, const Event& event)
{
   if (__unlikely(current == 0))
   {
      return USI_UNKNOWN_EVENT;
   }

   ActionStatus status = current->handleEvent(context, event);
   if(!status.isDone())
   {
      return status;
   }
   
   return forward(context);
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::handleEvent(TransactionContext& context, const Event& event)
{
   return FINAL_STATUS(doHandleEvent(context, event));
}

///////////////////////////////////////////////////////////////
inline Status SchedSequentialAction::doStop(TransactionContext& context, const Status cause)
{
    if(__likely(current != 0))
    {
        finalStatus = cause;
        return current->stop(context, cause);
    }

    return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////
Status SchedSequentialAction::stop(TransactionContext& context, const Status cause)
{
   return FINAL_STATUS(doStop(context, cause));
}

///////////////////////////////////////////////////////////////
void SchedSequentialAction::kill(TransactionContext& context, const Status cause)
{
   if (__likely(current != 0))
   {
      current->kill(context, cause);
      current = 0;
   }
}
