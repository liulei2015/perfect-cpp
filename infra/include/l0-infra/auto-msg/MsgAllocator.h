#ifndef __MSG_ALLOCATOR_H
#define __MSG_ALLOCATOR_H

#include <stddef.h>

struct MsgAllocator
{
    static void* alloc(size_t size);
    static void  free(void* p);
};

#endif

