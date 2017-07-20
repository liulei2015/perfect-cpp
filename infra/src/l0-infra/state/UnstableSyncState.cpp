#include "l0-infra/state/UnstableSyncState.h"
#include "l0-infra/state/StateId.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/state/StateMachine.h"
#include "l0-infra/event/concept/Event.h"

USI_NS_BEGIN

UnstableSyncState::UnstableSyncState(InstanceId iid, const StateId to)
      : to(to), iid(iid)
{
}

Status UnstableSyncState::doEnter()
{
    return USI_CONTINUE;
}

Status UnstableSyncState::doHandleEvent(const Event& event)
{
    event.consume();

    Status status = actualHandleEvent(event);
    if(status != USI_SUCCESS)
    {
    	DBG_LOG("actualHandleEvent failed [%x]!",(WORD32)status);
    }
    return status;
}

Status UnstableSyncState::doLeave(const Status cause)
{
    return USI_CONTINUE;
}

void UnstableSyncState::doKill(const Status )
{
}

StateId UnstableSyncState::getToState() const
{
    return to;
}

USI_NS_END

