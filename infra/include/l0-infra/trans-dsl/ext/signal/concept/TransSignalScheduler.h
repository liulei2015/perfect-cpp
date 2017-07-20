#ifndef INCL_USI_TransSignalScheduler_2013095132627_H__
#define INCL_USI_TransSignalScheduler_2013095132627_H__

#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalId.h"
#include "l0-infra/dci/InterfaceDef.h"
#include "l0-infra/base/Status.h"

DEF_INTERFACE(TransSignalScheduler, 0x09061329)
{
    ABSTRACT(Status broadcast(const TransSignalId));
};

#endif

