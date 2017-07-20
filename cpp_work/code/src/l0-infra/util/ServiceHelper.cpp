#include "l0-infra/util/ServiceHelper.h"
#include "l0-infra/base/Status.h"

namespace
{
    Status saveCellsInfo(const ConsecutiveEventInfo &event)
    {
        return USI_SUCCESS;
    }

}

Status saveMoAccessRsp(const ConsecutiveEventInfo& event)
{
    return saveCellsInfo(event);
}


