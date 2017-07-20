#ifndef INCL_USI_ActorBasedSyncAction_20131029104610_H__
#define INCL_USI_ActorBasedSyncAction_20131029104610_H__

#include "l0-infra/trans-dsl/action/SyncAction.h"
#include "l0-infra/trans-dsl/sched/helper/ActionHelper.h"

template <typename T_ACTION, typename T_ACTOR>
struct ActorBasedSyncAction
{
    Status exec(const TransactionInfo& trans)
    {
        return T_ACTION()(trans, T_ACTOR()(trans));
    }
};

#define __sync_1(p_action, p_actor) __sync(ActorBasedSyncAction<p_action, p_actor>)

#endif

