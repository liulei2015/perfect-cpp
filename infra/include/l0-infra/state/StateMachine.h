/*
 * StateMachine.h
 *
 *  Created on: Oct 27, 2012
 *      Author: arthur
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/state/StateId.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>

struct Event;

USI_NS_BEGIN

DEFINE_ROLE(StateMachine)
{
   ABSTRACT(InstanceId getInstanceId() const);
   ABSTRACT(void transitTo(const StateId));
   DEFAULT(void, resetEventQueue());
    virtual Status schedEvent(const Event&) {return USI_UNKNOWN_EVENT;}
};

USI_NS_END

#endif /* STATEMACHINE_H_ */

