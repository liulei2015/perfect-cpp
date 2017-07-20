/*
 * SchedWaitAction.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/SchedWaitAction.h"
#include "l0-infra/event/concept/Event.h"

Status SchedWaitAction::exec(TransactionContext&)
{
   return USI_CONTINUE;
}

Status SchedWaitAction::handleEvent(TransactionContext&, const Event& event)
{
   if(event.matches(getEventId()))
   {
      event.consume();
      return USI_SUCCESS;
   }

   return USI_UNKNOWN_EVENT;
}

Status SchedWaitAction::stop(TransactionContext&, const Status cause)
{
   return cause;
}

void SchedWaitAction::kill(TransactionContext&, const Status)
{
}

