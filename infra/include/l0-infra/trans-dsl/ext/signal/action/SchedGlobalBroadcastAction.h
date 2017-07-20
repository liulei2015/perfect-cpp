#ifndef INCL_USI_SchedGlobalBroadcastAction_2013095134000_H__
#define INCL_USI_SchedGlobalBroadcastAction_2013095134000_H__

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalId.h"

struct SchedGlobalBroadcastAction : SchedAction
{
    OVERRIDE(Status exec(TransactionContext&));
    OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
    OVERRIDE(Status stop(TransactionContext&, const Status));
    OVERRIDE(void   kill(TransactionContext&, const Status));

private:
    ABSTRACT(TransSignalId getGlobalSignalId());
};

#endif

