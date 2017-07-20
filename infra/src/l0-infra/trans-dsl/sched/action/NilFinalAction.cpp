/*
 * NilFinalAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/NilFinalAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"

Status NilFinalAction::exec(TransactionContext&)
{
   return USI_SUCCESS;
}

Status NilFinalAction::handleEvent(TransactionContext&, const Event&)
{
   return USI_FATAL_BUG;
}

void NilFinalAction::kill(TransactionContext&, const Status)
{
}

