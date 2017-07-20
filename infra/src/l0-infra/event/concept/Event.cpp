/*
 * Event.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/event/concept/Event.h"
#include "l0-infra/event/concept/EventInfo.h"
#include "l0-infra/event/concept/InvalidMsgSize.h"
#include <l0-infra/base/Assertions.h>
#include <l0-infra/base/Singleton.h>

namespace
{
   DEF_SINGLETON(NilEventInfo)  EXTENDS(EventInfo)
   {
      OVERRIDE(EventId getEventId() const)
      {
         return INVALID_EVENT_ID;
      }

      const void* getMsg() const
      {
         return 0;
      }

      size_t getMsgSize() const
      {
         return INVALID_MSG_SIZE;
      }

      Status updateEventId(const EventId) const
      {
         return USI_FATAL_BUG;
      }
   };
}

Event::Event()
  : info(&NilEventInfo::getInstance())
  , consumed(false)
{
}


