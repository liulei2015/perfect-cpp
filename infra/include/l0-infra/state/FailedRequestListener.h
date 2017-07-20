/*
 * FailedRequestListener.h
 *
 *  Created on: Oct 28, 2012
 *      Author: arthur
 */

#ifndef FAILEDREQUESTLISTENER_H_
#define FAILEDREQUESTLISTENER_H_

#include "l0-infra/base/Keywords.h"
#include "l0-infra/dci/Role.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"
#include "l0-infra/state/StateId.h"

struct Event;

USI_NS_BEGIN

DEFINE_ROLE(FailedRequestListener)
{
   DEFAULT(void, onReject(const InstanceId iid, const Event& event, const StateId sid) const);
   DEFAULT(void, onDiscard(const InstanceId iid, const Event& event, const StateId sid) const);
};

USI_NS_END

#endif

