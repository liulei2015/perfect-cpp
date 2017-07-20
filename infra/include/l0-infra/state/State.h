/*
 * State.h
 *
 *  Created on: Sep 23, 2012
 *      Author: arthur
 */

#ifndef STATE_H_
#define STATE_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include "TransStrategy.h"
#include "l0-infra/event/concept/EventId.h"
#include "l0-infra/state/TransStrategyDecisionMaker.h"
#include "IdDef.h"

struct Event;

USI_NS_BEGIN

struct StateMachine;

struct State : TransStrategyDecisionMaker
{
   ABSTRACT(StateId getId() const);
   ABSTRACT(bool   isStable() const);

   ABSTRACT(Status enter(StateMachine&));
   ABSTRACT(Status handleEvent(StateMachine&, const Event&));
   ABSTRACT(Status leave(StateMachine&, const Status cause = USI_SUCCESS));
   ABSTRACT(void   kill(StateMachine&, const Status cause = USI_SUCCESS));

   virtual Status onIdle(StateMachine&) { return USI_SUCCESS; }
   virtual Status onIdleTransSchedule(StateMachine&) { return USI_SUCCESS; }
   virtual void onReentry(StateMachine&) {}
   virtual bool isInitState() const { return false; }

   virtual bool ignoreFailure() const { return false; }
};

USI_NS_END

#endif /* STATE_H_ */

