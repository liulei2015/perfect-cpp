/*
 * BufferedEventFactory.h
 *
 *  Created on: Nov 11, 2012
 *      Author: arthur
 */

#ifndef BUFFEREDEVENTFACTORY_H_
#define BUFFEREDEVENTFACTORY_H_

#include <l0-infra/dci/Role.h>

struct Event;
struct EventInfo;

USI_NS_BEGIN

struct BufferedEventInfo;
struct TransStrategyDecisionMaker;
struct FailedRequestListener;

DEFINE_ROLE(BufferedEventFactory)
{
   ABSTRACT(BufferedEventInfo* createBufferedEvent
        (const Event&, TransStrategyDecisionMaker&, FailedRequestListener*));
   ABSTRACT(bool isBufferedEvent(const EventInfo&) const);
};

USI_NS_END

#endif /* BUFFEREDEVENTFACTORY_H_ */

