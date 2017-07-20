#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/log/log.h"
#include "l0-infra/event/impl/ConsecutiveEventInfo.h"
#include "assert.h"
#include "l0-infra/util/ServiceHelper.h"
#include "l0-infra/base/Status.h"

extern "C" void P_S_Service_Entry(WORD16 state, WORD16 eventId,
                                                                void *msg,  void *data)
{
    USI_SUCCESS == saveMoAccessRsp(ConsecutiveEventInfo(eventId, msg, 0)) ?
            INFO_LOG("saveMoAccessRsp success")
           :INFO_LOG("saveMoAccessRsp failed");
}
