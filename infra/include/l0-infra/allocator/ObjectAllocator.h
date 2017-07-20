#ifndef _OBJECT_ALLOCATOR_H
#define _OBJECT_ALLOCATOR_H

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/NullPtr.h"
#include "l0-infra/log/UsfLog.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/max_min.h"
#include <string.h>
#include <stdio.h>
#include <new>

namespace
{
    BYTE* Trace_OSS_Malloc(WORD32 size, CHAR *srcFile, INT line)
    {
        return static_cast<BYTE *> (malloc(size));
    }

    U32 Trace_OSS_Free(BYTE *pBuf, CHAR *srcFile, INT line)
    {
        free(pBuf);
    }
}

#define __F_INDEX(index) ((index) >> 3)
#define __F_MASK(index) (unsigned char)(1 << ((index) % 8))

template<typename T, WORD16 MAX_NUM>
struct ObjectAllocator
{
private:
    enum { NUM_OF_BYTE = (MAX_NUM >> 3) + ((MAX_NUM % 8) ? 1 : 0) };

    unsigned int getIndex(void* p) const
    {
        return ((Entity*)p) - entities;
    }

public:
    ObjectAllocator(bool freeCheck = true, WORD16 num = MAX_NUM)
        : needFreeCheck(freeCheck)
        , freeHead(__null_ptr__)
        , freeTail(__null_ptr__)
        , freeCounter(0)
        , num(__USI_MAX(num, MAX_NUM))
        , num_of_byte((num >> 3) + ((num % 8) ? 1 : 0))
    {
        ::memset(flags, 0, num_of_byte);

        entities = (Entity*)Trace_OSS_Malloc(sizeof(Entity) * num, (CHAR*)__SHORT_FILE__, __LINE__);

        for(WORD16 i = 0; i < num; i++)
        {
            new (&entities[i])(Entity);
            freeEntity(entities[i]);
        }

    }

    ~ObjectAllocator()
    {
        Trace_OSS_Free((BYTE*)entities, (CHAR*)__SHORT_FILE__, __LINE__);
    }

    WORD16 getFreeSlotNum() const
    {
        if (freeCounter < 0 || freeCounter > num)
        {
            DBG_LOG("freeCounter Error");
            return USI_INVALID_WORD16;
        }

        return freeCounter;
    }

    bool hasFreeSlot() const
    {
        return freeHead != __null_ptr__;
    }

    void* alloc()
    {
        if(!hasFreeSlot())
        {
  //          DBG_LOG("not free slot");

            return __null_ptr__;
        }
        return doAlloc();
    }

    void free(void* p)
    {
        if(p == __null_ptr__) return;

        if(needFreeCheck)
        {
            USI_EXPECT_TRUE_VOID(within(p));
            USI_EXPECT_TRUE_VOID((((char*)p - (char*)entities) % sizeof(Entity)) == 0);

            const unsigned int index = getIndex(p);
            const unsigned char mask = __F_MASK(index);
            const unsigned int n = __F_INDEX(index);
            INFO_LOG("index:%u", index);
            INFO_LOG("mask:%u", mask);
            INFO_LOG("n:%u", n);
            INFO_LOG("flags[n]:%u", flags[n]);
            INFO_LOG("flags[n] & mask:%u", flags[n] & mask);

            if((flags[n] & mask) == 0)
            {
//      DBG_LOG("block[%d] has been freed(%d:%d)", index, sizeof(T), num);
                return;
            }

            flags[n] &= ~mask;
            INFO_LOG("after flags[n] &= ~mask:%u", flags[n]);
        }

        freeEntity(*(Entity*)p);

    }

    bool within(void* p) const
    {
        return p >= (void*)entities && p < (void*)&(entities[num]);
    }

private:
    union Entity
    {
        char obj[sizeof(T)];
        Entity* next;
    };

private:

    void* doAlloc()
    {
        void* p = (void*)freeHead;

        freeHead = freeHead->next;

        if(freeHead == __null_ptr__)
        {
            freeTail = __null_ptr__;
        }

        freeCounter--;

        if(needFreeCheck)
        {
            const unsigned int index = getIndex(p);

            flags[__F_INDEX(index)] |= __F_MASK(index);
            INFO_LOG("doAlloc, flags[%u]: %u", __F_INDEX(index), flags[__F_INDEX(index)]);
        }

        return p;
    }

    void freeEntity(Entity& entity)
    {
        if(freeHead == 0)
        {
            freeHead = &entity;
        }
        else
        {
            USI_ASSERT_VALID_PTR_VOID(freeTail);
            freeTail->next = &entity;
        }

        freeTail = &entity;
        freeTail->next = __null_ptr__;
        freeCounter++;
    }

private:
    bool needFreeCheck;
    Entity* freeHead;
    Entity* freeTail;
    WORD16  freeCounter;
    WORD16  num;
    WORD16 num_of_byte;
    Entity* entities;
    unsigned char flags[NUM_OF_BYTE];
};

#endif
