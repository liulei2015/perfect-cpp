#include "l0-infra/multi-thread/PthreadRwLock.h"
#include "l0-infra/base/Assertions.h"

#ifdef _MSC_VER

PthreadRwLock::PthreadRwLock()
{
}

INT PthreadRwLock::rLock() const
{
	return 0;
}

INT PthreadRwLock::wLock() const
{
	return 0;
}

INT PthreadRwLock::unLock() const
{
	return 0;
}

PthreadRwLock::~PthreadRwLock()
{
}

#else

PthreadRwLock::PthreadRwLock()
{
    pthread_rwlockattr_t attr; 
    USI_PEEK_SUCC_CALL(pthread_rwlockattr_init(&attr));

    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    USI_PEEK_SUCC_CALL(pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE));

    USI_PEEK_SUCC_CALL(pthread_rwlock_init(&rwLock ,&attr));

    USI_PEEK_SUCC_CALL(pthread_rwlockattr_destroy(&attr)); 
}

INT PthreadRwLock::rLock() const
{
    return pthread_rwlock_rdlock(&rwLock);
}

INT PthreadRwLock::wLock() const
{
    return pthread_rwlock_wrlock(&rwLock);
}

INT PthreadRwLock::unLock() const
{
    return pthread_rwlock_unlock(&rwLock);
}

PthreadRwLock::~PthreadRwLock()
{
    pthread_rwlock_destroy(&rwLock);
}

#endif

