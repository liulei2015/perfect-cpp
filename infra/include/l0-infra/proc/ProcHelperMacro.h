#ifndef INCL_USI_PROC_HELPER_MACRO_H
#define INCL_USI_PROC_HELPER_MACRO_H

#include "l0-infra/base/usi.h"
#include "l0-infra/proc/UnknownEventHandler.h"
#include "l0-infra/base/Assertions.h"
#include <l0-infra/event/concept/Event.h>
#include "l0-infra/event/impl/ConsecutiveEventInfo.h"

USI_NS_BEGIN

enum ProcHelperMacro
{
    USI_PROC_IDLE=0,
    USI_PROC_WORK,
};

//////////////////////////////////////////////////////////////////////////
#define BEGIN_STATE_ENTRY_TABLE() switch(state) {

#define END_STATE_ENTRY_TABLE() \
        default: break; }

#define HANDLE_ON_STATE(State, Handler) \
    case State: Handler(ConsecutiveEventInfo(eventId, msg, len), data); break;

//////////////////////////////////////////////////////////////////////////
#define BEGIN_MSG_ENTRY_TABLE() \
    switch (event.getEventId()) {

#define END_MSG_ENTRY_TABLE()  }

#define PROCESS_MSG(Event, Handler)									\
    case Event:	                                                    \
        Handler().handleEvent(event);                                \
		break;

#define P_ON_MSG(Event, Handler)									       \
    case Event:	                                                           \
    {                                                                      \
        Status status = Handler::handleEvent(event);                       \
        if (status != USI_SUCCESS)                                         \
        {                                                                  \
            OSS_SetDefaultNextState();                                     \
            return;                                                        \
        }                                                                  \
        break;                                                             \
    }

#define _P_ON_MSG(Event, Handler)									       \
    case Event:	                                                           \
    {                                                                      \
         Status status = Handler::handleEvent(getInstanceId(),event);                       \
         if (status != USI_SUCCESS)                                         \
                {                                                                  \
                    OSS_SetDefaultNextState();                                     \
                    return status;                                                        \
                }                                                                  \
                break;                                                             \
      }

#define PROCESS_DEFAULT_MSG(Handler) \
    default: Handler().handleEvent(event, data);

#define IDLE_PROCESS_DEFAULT_MSG() \
    default: {OSS_SetDefaultNextState(); return;}


#define WORK_PROCESS_DEFAULT_MSG(Handler) \
    default: Handler::handleEvent(event, data)

#define PROCESS_UNKOWON_MSG() \
    default: USI_NS::UnknownEventHandler().execute(event)

USI_NS_END

#endif

