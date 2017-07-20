/*
 * UnstableState.cc
 *
 *  Created on: Oct 18, 2012
 *      Author: arthur
 */

#include "l0-infra/state/UnstableState.h"
#include "l0-infra/state/StateMachine.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
UnstableState::UnstableState()
   : from(STATE_NIL)
{
}

//////////////////////////////////////////////////////////////////////////
void UnstableState::startFrom(const StateId from)
{
    this->from = from;
}

//////////////////////////////////////////////////////////////////////////
bool UnstableState::isStable() const
{
   return false;
}

//////////////////////////////////////////////////////////////////////////
Status UnstableState::enter(StateMachine& context)
{
   return finalProcess(context, doEnter());
}

//////////////////////////////////////////////////////////////////////////
Status UnstableState::handleEvent(StateMachine& context, const Event& event)
{
   return finalProcess(context, doHandleEvent(event));
}

//////////////////////////////////////////////////////////////////////////
Status UnstableState::leave(StateMachine& context, const Status cause)
{
   return finalProcess(context, doLeave(cause));
}

//////////////////////////////////////////////////////////////////////////
void UnstableState::kill(StateMachine& context, const Status cause)
{
    doKill(cause); 
}

//////////////////////////////////////////////////////////////////////////
Status UnstableState::finalProcess(StateMachine& context, const ActionStatus& result)
{
    if(result.isDone())
    {
        context.transitTo(getToState());
        return DCM_SUCCESS;
    }

    if(result.isNothingChanged())
    {
        context.transitTo(from);
        return DCM_SUCCESS;
    }

    if(result.isFailed())
    {
      //todo
    }

    return result;
}


USI_NS_END

