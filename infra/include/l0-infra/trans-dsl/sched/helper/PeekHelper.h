/*
 * PeekHelper.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PEEKHELPER_H_
#define PEEKHELPER_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/event/concept/Event.h"

namespace details
{
   template <EventId EVENT_ID>
   struct PEEK__ : SchedAction
   {
       OVERRIDE(Status exec(TransactionContext&))
       {
           return USI_CONTINUE;
       }

       OVERRIDE(Status handleEvent(TransactionContext&, const Event& event))
       {
           if(event.matches(EVENT_ID))
           {
              return USI_SUCCESS;
           }

           return USI_UNKNOWN_EVENT;
       }

       OVERRIDE(Status stop(TransactionContext&, const Status cause))
       {
           return cause;
       }

       OVERRIDE(void kill(TransactionContext&, const Status))
       {
       }
   };
}

////////////////////////////////////////////////////////////////////
#define __peek(...) \
    ::details::PEEK__< __VA_ARGS__ >

////////////////////////////////////////////////////////////////////

#endif /* PEEKHELPER_H_ */

