#ifndef INCL_USI_DummyRwLock_H_
#define INCL_USI_DummyRwLock_H_

#include "l0-infra/multi-thread/RwLock.h"

struct DummyRwLock : RwLock
{
    OVERRIDE(INT rLock() const)
    {
        return 0;
    }

    OVERRIDE(INT wLock() const)
    {
        return 0;
    }

    OVERRIDE(INT unLock() const)
    {
        return 0;
    }
};

#endif

