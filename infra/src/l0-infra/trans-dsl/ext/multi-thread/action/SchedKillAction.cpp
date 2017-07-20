/*
 * SchedKillAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/ext/multi-thread/action/SchedKillAction.h"
#include "l0-infra/event/concept/Event.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionInfo.h"

Status SchedKillAction::getFinalCause(TransactionContext& context) const
{
    return getCause() == USI_SUCCESS ? context.getStatus() : getCause();
}

Status SchedKillAction::exec(TransactionContext& context)
{
    MultiThreadContext* mt = dci::unknown_cast<MultiThreadContext>(&context);
    USI_ASSERT_VALID_PTR(mt);

    return mt->killThread(getThreadId(), getFinalCause(context)); 
}

Status SchedKillAction::handleEvent(TransactionContext&, const Event& event)
{
    return USI_UNKNOWN_EVENT;
}

Status SchedKillAction::stop(TransactionContext&, const Status)
{
   return USI_CONTINUE;
}

void SchedKillAction::kill(TransactionContext&, const Status)
{
}

