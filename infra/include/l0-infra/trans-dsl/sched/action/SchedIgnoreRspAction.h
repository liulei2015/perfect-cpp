#ifndef INCL_USI_SchedIgnoreRspAction_H_
#define INCL_USI_SchedIgnoreRspAction_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"

struct SchedIgnoreRspAction : SchedAction
{
    OVERRIDE(Status exec(TransactionContext&));
    OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
    OVERRIDE(Status stop(TransactionContext&, const Status));
    OVERRIDE(void kill(TransactionContext&, const Status));

private:
    USE_ROLE(SchedAction);
};

#endif 

