#ifndef _INCL_USI_MixedEventInfo_20140106114547_H_
#define _INCL_USI_MixedEventInfo_20140106114547_H_

#include "l0-infra/event/impl/BaseEventInfo.h"
#include "l0-infra/event/impl/MixedEventData.h"

USI_NS_BEGIN

struct MixedEventInfo : BaseEventInfo
{
    MixedEventInfo(const EventId eventId, const void* const  orignalMsg, const void* const decodedMsg);
    MixedEventInfo(const EventId eventId, const void* const decodedMsg);

    OVERRIDE(const void* getMsg() const);
    OVERRIDE(size_t getMsgSize() const);

private:
    MixedEventData  data;
};

USI_NS_END

#endif

