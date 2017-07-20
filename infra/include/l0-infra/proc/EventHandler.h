#ifndef INCL_COMMON_EVENT_HANDLER_H
#define INCL_COMMON_EVENT_HANDLER_H

#include "l0-infra/base/Status.h"

struct Event;

USI_NS_BEGIN

#define USI_MAIN_EVENT_HANDLER(handler) \
struct handler\
{ \
    static Status handleEvent(const Event& event); \
}

#define DEF_HANDLER_HANDLE_EVENT(handler)\
Status handler::handleEvent(const Event& event)

#define USI_BMAIN_EVENT_HANDLER(handler) USI_MAIN_EVENT_HANDLER(handler)

USI_NS_END

#endif

