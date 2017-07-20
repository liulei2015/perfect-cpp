#ifndef INCL_USI_PthreadRwLock_20140315111409_H__
#define INCL_USI_PthreadRwLock_20140315111409_H__

#include "l0-infra/multi-thread/RwLock.h"

#ifndef _MSC_VER
#include <pthread.h>
#endif

struct PthreadRwLock : RwLock
{
    PthreadRwLock();
    ~PthreadRwLock();

    OVERRIDE(INT rLock() const);
    OVERRIDE(INT wLock() const);
    OVERRIDE(INT unLock() const);

private:
#ifndef _MSC_VER
    mutable pthread_rwlock_t rwLock;
#endif
};

#endif

