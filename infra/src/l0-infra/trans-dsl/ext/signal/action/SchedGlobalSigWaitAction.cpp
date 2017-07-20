#include "l0-infra/trans-dsl/ext/signal/action/SchedGlobalSigWaitAction.h"
#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalScheduler.h"
#include "l0-infra/dci/Unknown.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/event/concept/Event.h"
#include "l0-infra/trans-dsl/ext/signal/action/TransSignalMsg.h"

Status SchedGlobalSigWaitAction::exec(TransactionContext& context)
{
    return USI_CONTINUE;
}

Status SchedGlobalSigWaitAction::handleEvent(TransactionContext&, const Event& event)
{
    if(event.getEventId() != EV_GLOBAL_TRANS_SIGNAL)
    {
        return USI_UNKNOWN_EVENT;
    }

    const TransSignalMsg* msg = (const TransSignalMsg*)event.getMsg();
    USI_ASSERT_VALID_PTR(msg);

    if(msg->signal != getGlobalSignalId())
    {
        return USI_UNKNOWN_EVENT;
    }

    return USI_SUCCESS;
}

Status SchedGlobalSigWaitAction::stop(TransactionContext&, const Status cause)
{
    return cause;
}

void   SchedGlobalSigWaitAction::kill(TransactionContext&, const Status)
{
}

