#ifndef INCL_USI_StateEventHandler_20140227171843_H__
#define INCL_USI_StateEventHandler_20140227171843_H__

#include "l0-infra/base/Status.h"
#include "l0-infra/dci/Role.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

struct Event;

USI_NS_BEGIN

//DEFINE_ROLE(StateEventHandler)
//{
//    ABSTRACT(Status handleEvent(const InstanceId, const Event&));
//};

#define DECL_STATE_HANDLER(p_handler)                              \
struct p_handler                                                   \
{ static Status handleEvent(const InstanceId, const Event&); }

USI_NS_END

#endif
