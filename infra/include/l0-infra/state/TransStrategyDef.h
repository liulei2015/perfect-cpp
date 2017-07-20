/*
 * TransStrategyDef.h
 *
 *  Created on: Oct 28, 2012
 *      Author: arthur
 */

#ifndef TRANSSTRATEGYDEF_H_
#define TRANSSTRATEGYDEF_H_

#include "l0-infra/state/TransStrategy.h"
#include "l0-infra/event/concept/Event.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

USI_NS_BEGIN

inline void dummyInstanceId(const InstanceId) {}

#define BEGIN_NORMAL_STATE_STRATEGY_TABLE(state)     \
TransStrategy state::getStrategy                     \
    (const Event& event) const                       \
{                                                    \
    switch(event.getEventId()) {

#define BEGIN_STATE_STRATEGY_TABLE(state)            \
TransStrategy state::getStrategy                     \
    (const InstanceId iid, const Event& event) const \
{                                                    \
    dummyInstanceId(iid);                            \
    switch(event.getEventId()) {

#define END_STATE_STRATEGY_TABLE()                   \
    }                                                \
    return TS_NIL;                                   \
}

#define STATE_STRATEGY(eventId, strategy)            \
   case eventId: return strategy;

#define DEFAULT_STRATEGY(strategy)                   \
   default : return strategy;

#define DEFAULT_STRATEGY_MAKER(strategyMaker)       \
default: return strategyMaker::getInstance().getStrategy(iid, event);

#define STABLE_ACCEPTED_EVENT(eventId) STATE_STRATEGY(eventId, TS_REPLACE)

USI_NS_END

#endif /* TRANSSTRATEGYDEF_H_ */

