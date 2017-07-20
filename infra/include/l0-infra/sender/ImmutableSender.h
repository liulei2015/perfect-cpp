#ifndef INCL_USI_SingletonSender_H_
#define INCL_USI_SingletonSender_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"
#include <stddef.h>

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
template <WORD16 PROC_TYPE>
struct ImmutableSender
{
    static Status sendMsg(WORD16 eventId, const void* msg, size_t size);
};

template <WORD16 PROC_TYPE>
struct ImmutableMainCtrlSender
{
    static Status sendMsg(WORD16 eventId, const void* msg, size_t size);
};

USI_NS_END

#endif

