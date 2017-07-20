/*
 * WaitHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef WAITHELPER_H_
#define WAITHELPER_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/event/concept/Event.h"

namespace details
{
   template <EventId EVENT_ID>
   struct WAIT__ : SchedAction
   {
       OVERRIDE(Status exec(TransactionContext&))
       {
           return USI_CONTINUE;
       }

       OVERRIDE(Status handleEvent(TransactionContext&, const Event& event))
       {
           if(event.matches(EVENT_ID))
           {
              event.consume();
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

///////////////////////////////////////////////////////////
#define __wait(...) \
    ::details::WAIT__< __VA_ARGS__ >

///////////////////////////////////////////////////////////

#endif /* WAITHELPER_H_ */

