/*
 * SchedThrowAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/SchedThrowAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionInfo.h"

Status SchedThrowAction::exec(TransactionContext& context)
{
   return getStatus() == USI_RESERVED_FAILURE ? context.getStatus() : getStatus();
}

////////////////////////////////////////////////////////////////////////
Status SchedThrowAction::handleEvent(TransactionContext&, const Event&)
{
   return USI_FATAL_BUG;
}

////////////////////////////////////////////////////////////////////////
Status SchedThrowAction::stop(TransactionContext&, const Status)
{
   return USI_FATAL_BUG;
}

////////////////////////////////////////////////////////////////////////
void SchedThrowAction::kill(TransactionContext&, const Status)
{
}

