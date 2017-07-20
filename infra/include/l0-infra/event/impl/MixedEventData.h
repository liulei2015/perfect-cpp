#ifndef _INCL_USI_MixedEventData_20140106115754_H_
#define _INCL_USI_MixedEventData_20140106115754_H_

#include "l0-infra/base/usi.h"

USI_NS_BEGIN

struct MixedEventData
{
    MixedEventData(const void* const  orignalMsg, const void* const decodedMsg)
        : orignalMsg(orignalMsg), decodedMsg(decodedMsg)
    {
    }

    const void* const  orignalMsg;
    const void* const  decodedMsg;
};

USI_NS_END

#endif

