#ifndef INCL_USI_COMMON_AUTO_MSG_H
#define INCL_USI_COMMON_AUTO_MSG_H

#include "l0-infra/auto-msg/Message.h"
#include "l0-infra/auto-msg/MsgAllocator.h"

USI_NS_BEGIN

template <typename MSG, typename MSG_ALLOCATOR>
struct GenericMsg : MSG, Message<MSG_ALLOCATOR>
{
};

template <typename MSG, typename MSG_ALLOCATOR = MsgAllocator>
struct AutoMsg
{
    AutoMsg()
    {
        msg = new GenericMsg<MSG, MSG_ALLOCATOR>;        
    }

    ~AutoMsg()
    {
        if(msg != 0)
        {
            msg->operator delete((void*)msg);
            msg = 0;
        }
    }

    MSG* operator->()
    {
        return msg;
    }

    const MSG* getPointer() const
    {
        return msg;
    }

    MSG* getPointer()
    {
        return msg;
    }

    const MSG& getRef() const
    {
        return *msg;
    }

    MSG& getRef()
    {
        return *msg;
    }

private:
    GenericMsg<MSG, MSG_ALLOCATOR>* msg;
};

USI_NS_END

#endif

