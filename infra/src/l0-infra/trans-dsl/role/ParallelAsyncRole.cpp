#include "l0-infra/trans-dsl/role/ParallelAsyncRole.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

USI_NS_BEGIN

Status ParallelAsyncRole::handleEvent(const Event& event)
{
    ActionStatus status = doHandleEvent(event);
    if (status.isWorking())
    {
        return status;
    }

    // ignore even if one of the async-role fail.
    return hasWorkingActions() ? USI_CONTINUE : USI_SUCCESS;    
}

USI_NS_END

