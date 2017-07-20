#include "l0-infra/proc/Process.h"
#include "l0-infra/base/Assertions.h"

USI_NS_BEGIN

Process::Process(WORD32 pno) : pno(pno)
{
}

Status Process::sendMsgToMe(WORD16 eventId, const void* msg, size_t size)
{
    // todo : call interface from paas

    return USI_FAILED;
}

Status Process::sendMsgToMeUrgent(WORD16 eventId, const void* msg, size_t size)
{
    // todo

    return USI_FAILED;
}

USI_NS_END

