#ifndef INCL_USI_COMMON_AUTO_MSG_FACTORY_H
#define INCL_USI_COMMON_AUTO_MSG_FACTORY_H

#include "l0-infra/base/usi.h"

USI_NS_BEGIN

template<typename MSG_TYPE> 
struct AutoMsgFactory
{
    typedef MSG_TYPE MsgType;

    virtual MSG_TYPE* create() = 0;
    virtual void destroy(MSG_TYPE*) = 0;

    virtual ~AutoMsgFactory() {}
};

USI_NS_END

#endif

