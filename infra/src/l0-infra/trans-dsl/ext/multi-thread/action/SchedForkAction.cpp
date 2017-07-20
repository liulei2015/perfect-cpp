/*
 * SchedForkAction.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/ext/multi-thread/action/SchedForkAction.h"
#include "l0-infra/trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

Status SchedForkAction::exec(TransactionContext& context)
{
   MultiThreadContext* mt = dci::unknown_cast<MultiThreadContext>(&context);
   USI_ASSERT_VALID_PTR(mt);

   Status result = USI_SUCCESS;
   USI_ASSERT_SUCC_CALL(mt->startThread(getThreadId(), ROLE(ActionThread), result));

   return IS_FAILED_STATUS(result) ? result : USI_SUCCESS;
}

Status SchedForkAction::handleEvent(TransactionContext&, const Event&)
{
   return USI_UNKNOWN_EVENT;
}

Status SchedForkAction::stop(TransactionContext&, Status)
{
   return USI_SUCCESS;
}

void   SchedForkAction::kill(TransactionContext&, Status)
{
}


