/*
 * BufferedEvent.cc
 *
 *  Created on: Oct 27, 2012
 *      Author: arthur
 */

#include "l0-infra/state//BufferedEventInfo.h"
#include <l0-infra/base/Assertions.h>
#include <string.h>
#include "l0-infra/state/FailedRequestListener.h"
#include <l0-infra/event/concept/Event.h>
#include "l0-infra/state/TransStrategyDecisionMaker.h"

USI_NS_BEGIN

////////////////////////////////////////////////////////////////////////////
BufferedEventInfo::BufferedEventInfo
   ( const TransStrategyDecisionMaker* strategy
   , const FailedRequestListener* listener)
   : strategy(strategy)
   , listener(listener)
   , eventId(0xFFFF)
   , inQueue(false)
{
}

////////////////////////////////////////////////////////////////////////////
EventId BufferedEventInfo::getEventId() const
{
   return eventId;
}

////////////////////////////////////////////////////////////////////////////
Status BufferedEventInfo::updateEventId(const EventId id) const
{
   eventId = id;
   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////
void BufferedEventInfo::reject(const InstanceId iid) const
{
   if(listener != 0)
   {
      listener->onReject(iid, Event(*this), STATE_NIL);
   }
}

////////////////////////////////////////////////////////////////////////////
TransStrategy BufferedEventInfo::getStrategy(const InstanceId iid, const Event& event) const
{
   return (strategy == 0) ? TS_FAIL : strategy->getStrategy(iid, event);
}

////////////////////////////////////////////////////////////////////////////
const EventInfo& BufferedEventInfo::getEventInfo() const
{
   return *this;
}

//////////////////////////////////////////////////////////////////////////
void BufferedEventInfo::enQueue()
{
    inQueue = true;
}

//////////////////////////////////////////////////////////////////////////
void BufferedEventInfo::deQueue()
{
    inQueue = false;
}

//////////////////////////////////////////////////////////////////////////
bool BufferedEventInfo::isInQueue() const
{
    return inQueue;
}

USI_NS_END

