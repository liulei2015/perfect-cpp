/*
 * TransactionEvent.h
 *
 *  Created on: Oct 28, 2012
 *      Author: arthur
 */

#ifndef TRANSACTIONEVENT_H_
#define TRANSACTIONEVENT_H_

#include <l0-infra/dci/Role.h>
#include "l0-infra/state/TransStrategyDecisionMaker.h"

struct EventInfo;

USI_NS_BEGIN

struct TransactionEvent : TransStrategyDecisionMaker
{
   ABSTRACT(const EventInfo& getEventInfo() const);
   ABSTRACT(void reject(const InstanceId iid) const);
};

USI_NS_END

#endif /* TRANSACTIONEVENT_H_ */

