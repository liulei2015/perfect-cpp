#ifndef INCL_USI_TransSignalSchedulerAdapter_2013095143935_H__
#define INCL_USI_TransSignalSchedulerAdapter_2013095143935_H__

#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalScheduler.h"

struct TransSignalSchedulerAdapter : TransSignalScheduler
{
    TransSignalSchedulerAdapter();

    OVERRIDE(Status broadcast(const TransSignalId));

    void updateSignalScheduler(TransSignalScheduler&);

private:
    TransSignalScheduler* scheduler;
};

#endif

