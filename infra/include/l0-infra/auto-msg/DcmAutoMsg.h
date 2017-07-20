#ifndef INCL_USI_DcmAutoMsg_H
#define INCL_USI_DcmAutoMsg_H

#include "l0-infra/auto-msg/Message.h"
#include "l0-infra/auto-msg/MsgAllocator.h"

USI_NS_BEGIN

template <typename T>
struct DcmAutoMsg : T, Message<MsgAllocator>
{
};

USI_NS_END


#endif // INCL_USI_DcmAutoMsg_H

