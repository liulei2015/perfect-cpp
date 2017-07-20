#include "l0-infra/event/impl/MixedEventInfo.h"
#include "l0-infra/event/concept/InvalidMsgSize.h"

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
MixedEventInfo::MixedEventInfo
    ( const EventId eventId
    , const void* const  orignalMsg
    , const void* const decodedMsg)
    : BaseEventInfo(eventId)
    , data(orignalMsg, decodedMsg)
{
}

//////////////////////////////////////////////////////////////////////////
MixedEventInfo::MixedEventInfo(const EventId eventId, const void* const decodedMsg)
    : BaseEventInfo(eventId)
    , data(0, decodedMsg)
{
}

//////////////////////////////////////////////////////////////////////////
const void* MixedEventInfo::getMsg() const
{
    return data.orignalMsg == 0 ? data.decodedMsg : (const void*)&data;
}

//////////////////////////////////////////////////////////////////////////
size_t MixedEventInfo::getMsgSize() const
{
    return INVALID_MSG_SIZE;
}


USI_NS_END

