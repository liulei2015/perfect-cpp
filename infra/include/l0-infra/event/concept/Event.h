/*
 * Event.h
 *
 * Created on: Apr 21, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef EVENT_H_
#define EVENT_H_

#include "l0-infra/event/concept/EventId.h"
#include <l0-infra/base/Status.h>
#include "l0-infra/base/Assertions.h"
#include <stddef.h>
#include "l0-infra/event/concept/EventInfo.h"

struct Event
{
   Event();
   Event(const EventInfo& info)
   	   : info(&info)
   	   , consumed(false)
   {
   }

   EventId getEventId() const
   {
      return info->getEventId();
   }

   const void* getMsg() const
   {
      return info->getMsg();
   }

   size_t getMsgSize() const
   {
      return info->getMsgSize();
   }

   bool matches(const EventId eventId) const
   {
      return eventId == getEventId();
   }

   Status updateEventId(const EventId eventId) const
   {
      return info->updateEventId(eventId);
   }

   void updateEventInfo(const EventInfo& newInfo) const
   {
       info = &newInfo;
   }

   void assignEventInfoTo(Event& another) const
   {
      another.info = info;
   }

   const EventInfo& getEventInfo() const
   {
       return *info;
   }


   void consume() const
   {
      consumed = true;
   }

   bool isConsumed() const
   {
      return consumed;
   }


private:
   mutable const EventInfo* info;
   mutable bool consumed;
};

#define GET_MSG_PTR(type) (static_cast<const type*>(event.getMsg()))
#define GET_MSG_REF(type) *(GET_MSG_PTR(type))

#define EVENT_TO_MSG(type, var)          \
    const type* var = GET_MSG_PTR(type); \
    USI_ASSERT_VALID_PTR(var);

#define EVENT_TO_MSG_VOID(type, var)          \
    const type* var = GET_MSG_PTR(type); \
    USI_ASSERT_VALID_PTR_VOID(var);


#endif /* EVENT_H_ */

