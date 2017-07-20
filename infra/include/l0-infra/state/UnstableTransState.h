#ifndef INCL_DCM_UnstableTransState_H__
#define INCL_DCM_UnstableTransState_H__

#include "l0-infra/base/usi.h"
#include "l0-infra/state/UnstableState.h"

struct LockableTransaction;

USI_NS_BEGIN

struct UnstableTransState : UnstableState
{
    OVERRIDE(void updateMutexScheduler(TransMutexScheduler&));
    OVERRIDE(void updateSignalScheduler(TransSignalScheduler&));
    OVERRIDE(void init(const InstanceId&));
    OVERRIDE(void destroy());

private:
    OVERRIDE(Status doEnter());
    OVERRIDE(Status doLeave(const Status cause));
    OVERRIDE(Status doHandleEvent(const Event&));
    OVERRIDE(void doKill(const Status cause));

private:
    Status postprocess(const Event& event);

private:
    virtual Status postTransaction(const Event&);

private:
    USE_ROLE(LockableTransaction);

protected:
    virtual TransStrategy getRuntimeStrategy(const InstanceId, const Event&) const;
};

//////////////////////////////////////////////////////////////////////////

#define DECL_UNSTABLE_TRANS_METHODS()                             \
    DECL_UNSTABLE_STATE_STRATEGY()                               

//////////////////////////////////////////////////////////////////////////

#define BEGIN_UNSTABLE_TRANS_STATE_STRATEGY_TABLE(transState)       \
    BEGIN_UNSTABLE_STRATEGY_TABLE(transState) 

#define END_UNSTABLE_TRANS_STATE_STRATEGY_TABLE(transState)         \
    END_UNSTABLE_STRATEGY_TABLE(transState)                         \
    TransStrategy transState::getStrategy                           \
        (const InstanceId iid, const Event& event) const            \
    {                                                               \
        TransStrategy strategy = getRuntimeStrategy(iid, event);    \
        if(strategy != TS_UNKNOWN) return strategy;                 \
        return getStrategyDecisionMaker()->getStrategy(iid, event); \
    }

//////////////////////////////////////////////////////////////////////////
#define CCM_BEGIN_UNSTABLE_STRATEGY_TABLE(state) BEGIN_UNSTABLE_STRATEGY_TABLE(state)
#define CCM_END_UNSTABLE_STRATEGY_TABLE(state) END_UNSTABLE_STRATEGY_TABLE(state)    \
    TransStrategy state::getStrategy(const InstanceId iid, const Event& event) const \
    {                                                                                \
        return getStrategyDecisionMaker()->getStrategy(iid, event);                  \
    }

USI_NS_END

#endif
