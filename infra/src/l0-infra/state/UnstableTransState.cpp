#include "l0-infra/state/UnstableTransState.h"
#include "l0-infra/trans-dsl/sched/concept/Transaction.h"

USI_NS_BEGIN

Status UnstableTransState::doEnter()
{
    return ROLE(LockableTransaction).start();
}

Status UnstableTransState::doHandleEvent(const Event& event)
{
    Status status = ROLE(LockableTransaction).handleEvent(event);
    if(status != DCM_UNKNOWN_EVENT)
    {
        return status;
    }

    return postprocess(event);
}

Status UnstableTransState::doLeave(const Status cause)
{
    return ROLE(LockableTransaction).stop(cause);
}

void UnstableTransState::doKill(const Status cause)
{
    ROLE(LockableTransaction).kill(cause);
}

Status UnstableTransState::postprocess(const Event& event)
{
    Status status = postTransaction(event);
    if(IS_FAILED_STATUS(status))
    {
        ROLE(LockableTransaction).kill(status);
    }

    return status == DCM_SUCCESS ? DCM_CONTINUE : status;
}

//////////////////////////////////////////////////////////////////////////
Status UnstableTransState::postTransaction(const Event&)
{
    return DCM_UNKNOWN_EVENT;
}

//////////////////////////////////////////////////////////////////////////
TransStrategy UnstableTransState::getRuntimeStrategy(const InstanceId, const Event&) const
{
    return TS_UNKNOWN;
}

//////////////////////////////////////////////////////////////////////////
void UnstableTransState::updateMutexScheduler(TransMutexScheduler& scheduler)
{
    ROLE(LockableTransaction).updateMutexScheduler(scheduler);
}

//////////////////////////////////////////////////////////////////////////
void UnstableTransState::updateSignalScheduler(TransSignalScheduler& scheduler)
{
    ROLE(LockableTransaction).updateSignalScheduler(scheduler);
}

//////////////////////////////////////////////////////////////////////////
void UnstableTransState::init(const InstanceId& iid)
{
    ROLE(LockableTransaction).init(iid);
}

//////////////////////////////////////////////////////////////////////////
void UnstableTransState::destroy()
{
	ROLE(LockableTransaction).destroy();
}

USI_NS_END

