#ifndef INCL_ParallelAsyncRole_20131121152111_H_
#define INCL_ParallelAsyncRole_20131121152111_H_

#include "l0-infra/trans-dsl/role/ConcurrentAsyncRole.h"

USI_NS_BEGIN

struct ParallelAsyncRole : ConcurrentAsyncRole
{
    OVERRIDE(Status handleEvent(const Event&));
};

USI_NS_END

#endif

