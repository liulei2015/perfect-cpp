#include "l0-infra/trans-dsl/sched/trans/TransSignalSchedulerAdapter.h"
#include "l0-infra/base/Assertions.h"

//////////////////////////////////////////////////////////////////////////
TransSignalSchedulerAdapter::TransSignalSchedulerAdapter() : scheduler(0)
{
}

//////////////////////////////////////////////////////////////////////////
Status TransSignalSchedulerAdapter::broadcast(const TransSignalId id)
{
    USI_ASSERT_VALID_PTR(scheduler);

    return scheduler->broadcast(id);
}

//////////////////////////////////////////////////////////////////////////
void TransSignalSchedulerAdapter::updateSignalScheduler(TransSignalScheduler& scheduler)
{
    this->scheduler = &scheduler;
}

