#include "l0-infra/trans-dsl/sched/action/SchedIgnoreRspAction.h"

Status SchedIgnoreRspAction::exec(TransactionContext& context)
{
    Status status = ROLE(SchedAction).exec(context);
    if(status == USI_CONTINUE)
    {
        ROLE(SchedAction).stop(context, USI_SUCCESS);
        return USI_SUCCESS;
    }

    return status;
}

Status SchedIgnoreRspAction::handleEvent(TransactionContext&, const Event&)
{
    return USI_UNKNOWN_EVENT;
}

Status SchedIgnoreRspAction::stop(TransactionContext& context, const Status status)
{
    return ROLE(SchedAction).stop(context, status);
}

void SchedIgnoreRspAction::kill(TransactionContext& context, const Status status)
{
    ROLE(SchedAction).kill(context, status);
}

