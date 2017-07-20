/*
 * BaseEventInfo.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/event/impl/BaseEventInfo.h"

BaseEventInfo::BaseEventInfo(const EventId eventId)
   : eventId(eventId)
{
}

EventId BaseEventInfo::getEventId() const
{
   return eventId;
}

Status BaseEventInfo::updateEventId(const EventId id) const
{
   eventId = id;
   return USI_SUCCESS;
}

