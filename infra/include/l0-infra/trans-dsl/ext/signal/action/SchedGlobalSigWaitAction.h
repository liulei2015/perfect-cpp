#ifndef INCL_USI_SchedGlobalSigWaitAction_2013095135345_H__
#define INCL_USI_SchedGlobalSigWaitAction_2013095135345_H__

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalId.h"

struct SchedGlobalSigWaitAction : SchedAction
{
    OVERRIDE(Status exec(TransactionContext&));
    OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
    OVERRIDE(Status stop(TransactionContext&, const Status));
    OVERRIDE(void   kill(TransactionContext&, const Status));

private:
    ABSTRACT(TransSignalId getGlobalSignalId());
};

#endif

