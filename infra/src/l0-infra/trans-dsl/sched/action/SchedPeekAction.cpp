/*
 * SchedPeekAction.cc
 *
 *  Created on: Apr 28, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/SchedPeekAction.h"
#include "l0-infra/event/concept/Event.h"

Status SchedPeekAction::exec(TransactionContext&)
{
   return USI_CONTINUE;
}

Status SchedPeekAction::handleEvent(TransactionContext&, const Event& event)
{
   if(event.matches(getEventId()))
   {
      return USI_SUCCESS;
   }

   return USI_UNKNOWN_EVENT;
}

Status SchedPeekAction::stop(TransactionContext&, const Status cause)
{
   return cause;
}

void SchedPeekAction::kill(TransactionContext&, const Status)
{
}

