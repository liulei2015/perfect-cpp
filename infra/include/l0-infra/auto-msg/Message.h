#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <new>
#include "l0-infra/base/Assertions.h"
#include <string.h>

template<typename MSG_ALLOCATOR>
struct Message
{
    void* operator new(size_t size) throw()
    {
        void* p = MSG_ALLOCATOR::alloc(size);
        USI_ASSERT_VALID_PTR_NIL(p);

#ifdef USI_FT
		::memset(p, 0xff, size);
#endif
        return p;
    }

    void operator delete(void* p)
    {
        MSG_ALLOCATOR::free(p);
    }

    virtual ~Message() {}
};

#endif

