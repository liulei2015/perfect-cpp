#ifndef INCL_USI_EventName_H
#define INCL_USI_EventName_H

#include "l0-infra/base/usi.h"

USI_NS_BEGIN

#define EVENT_MAP_BEGIN() switch (eventId) {
#define EVENT_MAP_END() \
        default: break;  } \
		return "THIS_IS_A_UNKOWN_EVENT";

#define ON_EVENT(eventId) case eventId: return #eventId;

USI_NS_END

#endif

