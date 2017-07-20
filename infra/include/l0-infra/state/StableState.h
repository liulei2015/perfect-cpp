/*
 * StableState.h
 *
 *  Created on: Oct 18, 2012
 *      Author: arthur
 */

#ifndef STABLESTATE_H_
#define STABLESTATE_H_

#include "State.h"

USI_NS_BEGIN

struct StableState : State
{
   OVERRIDE(bool   isStable() const);
   OVERRIDE(Status enter(StateMachine&));
   OVERRIDE(Status handleEvent(StateMachine&, const Event&));
   OVERRIDE(Status leave(StateMachine&, const Status));
   OVERRIDE(void   kill(StateMachine&, const Status));
};

USI_NS_END

#endif /* STABLESTATE_H_ */

