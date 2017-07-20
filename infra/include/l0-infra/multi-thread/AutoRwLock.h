#ifndef INCL_USI_AutoRwLock_H_
#define INCL_USI_AutoRwLock_H_

struct RwLock;

struct AutoLock
{
    ~AutoLock();
    bool isLocked () const;
    void setUnlock();

protected:
    AutoLock(const RwLock& rwLock);

protected:
    const RwLock& lock;

private:
    bool  locked;
};

struct AutoRLock : AutoLock
{
    AutoRLock(const RwLock& rwLock);
};


struct AutoWLock : AutoLock
{
    AutoWLock(const RwLock& rwLock);
};

#endif

