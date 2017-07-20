/*
 * UnstableState.h
 *
 *  Created on: Oct 18, 2012
 *      Author: arthur
 */

#ifndef UNSTABLESTATE_H_
#define UNSTABLESTATE_H_

#include "l0-infra/state/State.h"
#include <l0-infra/state/StateId.h>
#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>
#include "l0-infra/state/TransStrategyDef.h"
#include "l0-infra/dci/Unknown.h"

struct ActionStatus;
struct TransMutexScheduler;
struct TransSignalScheduler;

USI_NS_BEGIN

struct UnstableState : State
{
   UnstableState();

   void startFrom(const StateId from);

   //////////////////////////////////////////////////////////////////////////
   DEFAULT(void, updateMutexScheduler(TransMutexScheduler&));
   DEFAULT(void, updateSignalScheduler(TransSignalScheduler&));

   DEFAULT(void, init(const InstanceId&));
   DEFAULT(void, destroy());

private:
   OVERRIDE(bool isStable() const);

   OVERRIDE(Status enter(StateMachine&));
   OVERRIDE(Status handleEvent(StateMachine&, const Event&));
   OVERRIDE(Status leave(StateMachine&, const Status cause));
   OVERRIDE(void kill(StateMachine& context, const Status cause));

private:
   Status finalProcess(StateMachine&, const ActionStatus& status);

private:
   StateId from;

private:
    ABSTRACT(Status doEnter());
    ABSTRACT(Status doHandleEvent(const Event&));
    ABSTRACT(Status doLeave(const Status));
    ABSTRACT(void doKill(const Status));
    ABSTRACT(StateId getToState() const);    
};

//////////////////////////////////////////////////////////////////////////

#define DECL_UNSTABLE_STATE_STRATEGY()                             \
    static TransStrategyDecisionMaker* getStrategyDecisionMaker(); \
    OVERRIDE(TransStrategy                                         \
    getStrategy(const InstanceId, const Event&) const)

//////////////////////////////////////////////////////////////////////////

#define BEGIN_UNSTABLE_STRATEGY_TABLE(state)                       \
    namespace                                                      \
    {                                                              \
        struct state##Strategy : TransStrategyDecisionMaker        \
        {                                                          \
            OVERRIDE(TransStrategy getStrategy                     \
                (const InstanceId, const Event&) const);           \
        };                                                         \
                                                                   \
        BEGIN_STATE_STRATEGY_TABLE(state##Strategy)


#define END_UNSTABLE_STRATEGY_TABLE(state)                         \
    END_STATE_STRATEGY_TABLE()                                     \
}                                                                  \
                                                                   \
    TransStrategyDecisionMaker* state::getStrategyDecisionMaker()  \
    {                                                              \
        static state##Strategy instance;                           \
        return &instance;                                          \
    } 

USI_NS_END

#endif /* UNSTABLESTATE_H_ */

