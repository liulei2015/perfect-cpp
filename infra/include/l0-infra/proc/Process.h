#ifndef INCL_COMMOM_PROCESS_ID_H
#define INCL_COMMOM_PROCESS_ID_H

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"

USI_NS_BEGIN

struct Process
{
    explicit Process(WORD32 pno);
    Status sendMsgToMe(WORD16 eventId, const void* msg, size_t size);
    Status sendMsgToMeUrgent(WORD16 eventId, const void* msg, size_t size);
private:
    WORD32 pno;
};

USI_NS_END

#endif

