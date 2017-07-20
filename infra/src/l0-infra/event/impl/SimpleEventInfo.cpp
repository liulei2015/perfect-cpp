/*
 * SimpleEventInfo.cc
 *
 *  Created on: Apr 23, 2013
 *      Author: arthur
 */

#include "l0-infra/event/impl/SimpleEventInfo.h"

SimpleEventInfo::SimpleEventInfo(const EventId eventId)
     : BaseEventInfo(eventId)
{
}

const void* SimpleEventInfo::getMsg() const
{
   return 0;
}

size_t SimpleEventInfo::getMsgSize() const
{
   return 0;
}



