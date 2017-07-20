/*
 * BufferedEventInfo.h
 *
 *  Created on: Oct 27, 2012
 *      Author: arthur
 */

#ifndef BUFFEREDEVENTINFO_H_
#define BUFFEREDEVENTINFO_H_

#include <l0-infra/base/ListElem.h>
#include <l0-infra/event/concept/EventInfo.h>
#include "l0-infra/state/TransStrategy.h"
#include "l0-infra/state/TransactionEvent.h"

struct Event;

USI_NS_BEGIN

struct TransStrategyDecisionMaker;
struct FailedRequestListener;

struct BufferedEventInfo : ListElem<BufferedEventInfo>
                         , EventInfo
                         , TransactionEvent
{
   BufferedEventInfo(const TransStrategyDecisionMaker* strategy, const FailedRequestListener* listener);

   OVERRIDE(EventId getEventId() const);
   OVERRIDE(Status updateEventId(const EventId) const);

   void enQueue();
   void deQueue();

   bool isInQueue() const;

public:
   OVERRIDE(void reject(const InstanceId iid) const);
   OVERRIDE(const EventInfo& getEventInfo() const);
   OVERRIDE(TransStrategy getStrategy(const InstanceId, const Event&) const);

private:
   const TransStrategyDecisionMaker*  strategy;
   const FailedRequestListener* listener;
   mutable EventId eventId;
   bool inQueue;

public:
   ABSTRACT(Status saveEvent(const EventInfo&));

   ABSTRACT(const void* getMsg() const);
   ABSTRACT(const void* getMsgBuffer() const);
   ABSTRACT(size_t getMsgSize() const);
};

USI_NS_END

#endif /* BUFFEREDEVENTINFO_H_ */

