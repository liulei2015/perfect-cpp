#include "l0-infra/multi-thread/AutoRwLock.h"
#include "l0-infra/multi-thread/RwLock.h"
#include "l0-infra/base/Assertions.h"

AutoLock::AutoLock(const RwLock& rwLock) 
: lock(rwLock) ,locked(true)
{
}

bool AutoLock::isLocked () const
{
    return locked;
}

void AutoLock::setUnlock()
{
    locked = false;
}

AutoLock::~AutoLock()
{
    USI_ASSERT_TRUE_VOID(lock.unLock() == 0);
}

AutoRLock::AutoRLock(const RwLock& rwLock) 
: AutoLock(rwLock)
{
	USI_ASSERT_TRUE_VOID(lock.rLock() == 0);
}

AutoWLock::AutoWLock(const RwLock& rwLock) 
: AutoLock(rwLock)
{
	USI_ASSERT_TRUE_VOID(lock.wLock() == 0);
}

