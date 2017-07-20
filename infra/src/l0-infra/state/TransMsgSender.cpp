#include "l0-infra/state/TransMsgSender.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

USI_NS_BEGIN

Status TransMsgSender::send(WORD16 eventId)
{
    ActionStatus status = doBuffer(ConsecutiveEventInfo(eventId, 0, 0));
    if(status.isWorking())
    {
        return USI_SUCCESS;
    }

    return status;
}

USI_NS_END

