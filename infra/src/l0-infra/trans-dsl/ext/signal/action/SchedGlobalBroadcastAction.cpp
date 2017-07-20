#include "l0-infra/trans-dsl/ext/signal/action/SchedGlobalBroadcastAction.h"
#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalScheduler.h"
#include "l0-infra/dci/Unknown.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"

Status SchedGlobalBroadcastAction::exec(TransactionContext& context)
{
    TransSignalScheduler* sched = dci::unknown_cast<TransSignalScheduler>(&context);
    USI_ASSERT_VALID_PTR(sched);

    return sched->broadcast(getGlobalSignalId());
}

Status SchedGlobalBroadcastAction::handleEvent(TransactionContext&, const Event&)
{
    return USI_UNKNOWN_EVENT;
}

Status SchedGlobalBroadcastAction::stop(TransactionContext&, const Status cause)
{
    return cause;
}

void   SchedGlobalBroadcastAction::kill(TransactionContext&, const Status)
{
}

