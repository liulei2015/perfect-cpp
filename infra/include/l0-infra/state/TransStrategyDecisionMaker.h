/*
 * TransStrategyDecisionMaker.h
 *
 *  Created on: Oct 28, 2012
 *      Author: arthur
 */

#ifndef TRANSSTRATEGYDECISIONMAKER_H_
#define TRANSSTRATEGYDECISIONMAKER_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/state/TransStrategy.h>
#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>
#include "l0-infra/event/concept/Event.h"

USI_NS_BEGIN

DEFINE_ROLE(TransStrategyDecisionMaker)
{
    ABSTRACT(TransStrategy getStrategy(const InstanceId, const Event&) const);
};

//////////////////////////////////////////////////////////////////////////
#define STATE_STRATEGY_DECL() \
    OVERRIDE(TransStrategy getStrategy(const InstanceId, const Event&) const)

#define STATE_RUNTIME_STRATEGY_DECL() \
    OVERRIDE(TransStrategy getSpecialRuntimeStrategy(const InstanceId, const Event&) const)

//////////////////////////////////////////////////////////////////////////
#define STATIC_STRATEGY_DECL(p_name) \
struct p_name : TransStrategyDecisionMaker \
{ \
    static TransStrategyDecisionMaker& getInstance(); \
    STATE_STRATEGY_DECL(); \
}

//////////////////////////////////////////////////////////////////////////
#define __STRATEGY_TABLE() switch(event.getEventId()) 

//////////////////////////////////////////////////////////////////////////
#define __BEGIN_STRATEGY_TABLE() __STRATEGY_TABLE() {
#define __END_STRATEGY_TABLE()  default: return TS_UNKNOWN; }

//////////////////////////////////////////////////////////////////////////
#define __DEF_STATIC_STRATEGY(p_name)                \
TransStrategyDecisionMaker& p_name::getInstance()    \
{                                                    \
    static p_name instance;                          \
    return instance;                                 \
}                                                    \
TransStrategy p_name::getStrategy(const InstanceId iid, const Event& event) const

//////////////////////////////////////////////////////////////////////////
#define BEGIN_STATIC_STRATEGY_DEF(p_name)  \
/*lint -e715*/__DEF_STATIC_STRATEGY(p_name)  {           \
    __BEGIN_STRATEGY_TABLE()

//////////////////////////////////////////////////////////////////////////
#define END_STATIC_STRATEGY_DEF()          \
default:break;}                                      \
    return TS_UNKNOWN; }

#define END_STATIC_STRATEGY_DEF_WITHOUT_DEFAULT()   \
    }                                               \
}

USI_NS_END

#endif /* TRANSSTRATEGYDECISIONMAKER_H_ */

