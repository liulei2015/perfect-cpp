#ifndef INCL_USI_SingletonSender_TCC_
#define INCL_USI_SingletonSender_TCC_

#include "l0-infra/sender/ImmutableSender.h"
#include "l0-infra/wrapper/ng_pub_platform.h"
#include "l0-infra/wrapper/ng_pub_oss.h"
#include "l0-infra/oss/OssSender.h"
#include "l0-infra/base/Assertions.h"
#include <l0-infra/oss/OssPid.h>

USI_NS_BEGIN

namespace Sender
{
    struct OssMainCtrlPid : OssPidBase
    {
        OssMainCtrlPid(WORD16 procType):OssPidBase(procType, OSS_ConstructMainCtrlPID)
        {
        }
    };
}

template <WORD16 PROC_TYPE>
Status ImmutableSender<PROC_TYPE>::sendMsg(WORD16 eventId, const void* msg, size_t size)
{
    static OssPid pid(PROC_TYPE);
    return OssSender(*pid).send(eventId, msg, size);
}

template <WORD16 PROC_TYPE>
Status ImmutableMainCtrlSender<PROC_TYPE>::sendMsg(WORD16 eventId, const void* msg, size_t size)
{
    static Sender::OssMainCtrlPid pid(PROC_TYPE);
    return OssSender(*pid).send(eventId, msg, size);
}

//////////////////////////////////////////////////////////////////////////

#define DEF_IMMUTABLE_SENDER(senderClass, procType)                       \
namespace{typedef struct ImmutableSender<procType> senderClass##procType##Sender;} \
Status senderClass::sendMsg(WORD16 eventId, const void* msg, size_t size) \
{ return senderClass##procType##Sender::sendMsg(eventId, msg, size); }


#define DEF_IMMUTABLE_MAIN_CTRL_SENDER(senderClass, procType)                       \
namespace { typedef struct ImmutableMainCtrlSender<procType> senderClass##procType##Sender; }  \
Status senderClass::sendMsg(WORD16 eventId, const void* msg, size_t size) \
{ return senderClass##procType##Sender::sendMsg(eventId, msg, size); }


#define DECL_IMMUTABLE_SENDER(senderClass)                                 \
struct senderClass                                                         \
{                                                                          \
    static Status sendMsg(WORD16 eventId, const void* msg, size_t size);   \
};

USI_NS_END

#endif
