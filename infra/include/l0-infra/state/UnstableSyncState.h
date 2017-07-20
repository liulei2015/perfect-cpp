#ifndef INCL_USI_UnstableSyncState_H__
#define INCL_USI_UnstableSyncState_H__

#include "l0-infra/base/usi.h"
#include "l0-infra/state/UnstableState.h"

USI_NS_BEGIN

struct UnstableSyncState : UnstableState
{
    UnstableSyncState(InstanceId iid, const StateId to);

private:
    OVERRIDE(Status doEnter());
    OVERRIDE(Status doHandleEvent(const Event&));
    OVERRIDE(Status doLeave(const Status cause));
    OVERRIDE(void doKill(const Status ));

    OVERRIDE(StateId getToState() const);

//    DEFAULT(dci::Unknown*, getContext());

    OVERRIDE(void init(const InstanceId& iid))
    {
        this->iid = iid;
    }

private:
    ABSTRACT(Status actualHandleEvent(const Event&));

private:
    const StateId to;

protected:
    InstanceId iid;
};

//////////////////////////////////////////////////////////////////////////

#define DECL_UNSTABLE_SYNC_METHODS()   DECL_UNSTABLE_STATE_STRATEGY()

//////////////////////////////////////////////////////////////////////////

#define BEGIN_UNSTABLE_SYNC_STATE_STRATEGY_TABLE(syncState)         \
    BEGIN_UNSTABLE_STRATEGY_TABLE(syncState) 

#define END_UNSTABLE_SYNC_STATE_STRATEGY_TABLE(syncState)           \
    END_UNSTABLE_STRATEGY_TABLE(syncState)                          \
    TransStrategy syncState::getStrategy                            \
        (const InstanceId iid, const Event& event) const            \
    {                                                               \
        return getStrategyDecisionMaker()->getStrategy(iid, event); \
    }


#define DEF_UNSTABLE_STATE(state)                              \
struct Dcm ##state## State : UnstableSyncState                 \
{                                                              \
    Dcm ##state## State(InstanceId iid);                       \
    DEF_STATE_ID(state);                                       \
    OVERRIDE(Status actualHandleEvent(const Event&));          \
    DECL_UNSTABLE_SYNC_METHODS();                              \
}

USI_NS_END

#endif

