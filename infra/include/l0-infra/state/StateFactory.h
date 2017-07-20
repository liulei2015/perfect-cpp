/*
 * StateFactory.h
 *
 *  Created on: Oct 29, 2012
 *      Author: arthur
 */

#ifndef STATEFACTORY_H_
#define STATEFACTORY_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>
#include <l0-infra/event/concept/EventId.h>
#include <l0-infra/state/StateId.h>

struct Event;

USI_NS_BEGIN

struct State;
struct PostProcessHandler;
struct FailedRequestListener;
struct TransStrategyDecisionMaker;


DEFINE_ROLE(StateFactory)
{
   
   ABSTRACT(State* createInitialState());
   ABSTRACT(State* createStableState(const StateId));
   ABSTRACT(State* createFailState(const Status));
   ABSTRACT(State* createUnstableState(const EventId));
   ABSTRACT(bool isTransEvent(const EventId));
   ABSTRACT(bool isStrategyEvent(const EventId));
   ABSTRACT(TransStrategyDecisionMaker* getStrategyMaker(const EventId));
   ABSTRACT(Status getFailCauseByEvent(const Event&) const);
   ABSTRACT(Status getInterruptCauseByEvent(const Event&) const);
   ABSTRACT(Status getPreemptCauseByEvent(const Event&) const);
   ABSTRACT(Status destroyState(State*));
   ABSTRACT(void reset());
};

USI_NS_END

#endif /* STATEFACTORY_H_ */

