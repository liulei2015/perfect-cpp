#ifndef INCL_USI_COMMON_UNKNOWN_EVENT_HANDLER_H
#define INCL_USI_COMMON_UNKNOWN_EVENT_HANDLER_H

#include "l0-infra/proc/EventHandler.h"
#include <l0-infra/event/concept/Event.h>

USI_NS_BEGIN

struct UnknownEventHandler
{
    Status handleEvent(const Event& /*event*/) const
    {
        return USI_FAILED;
    }
};

USI_NS_END

#endif

