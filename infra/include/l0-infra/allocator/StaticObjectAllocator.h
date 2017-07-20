#ifndef INCL_USI_H07D26725_08BC_46F0_8682_C27529E2AB24
#define INCL_USI_H07D26725_08BC_46F0_8682_C27529E2AB24

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/NullPtr.h"
#include "l0-infra/log/UsfLog.h"
#include "l0-infra/base/Assertions.h"
#include <string.h>
#include <stdio.h>

#define __F_INDEX(index) ((index) >> 3)
#define __F_MASK(index) (unsigned char)(1 << ((index) % 8))

template<typename T, WORD16 MAX_NUM>
struct StaticObjectAllocator
{
private:
    enum { NUM_OF_BYTE = (MAX_NUM >> 3) + ((MAX_NUM % 8) ? 1 : 0) };

    unsigned int getIndex(void* p) const
    {
        return ((Entity*)p) - entities;
    }

public:
    StaticObjectAllocator(bool freeCheck = false)
        : needFreeCheck(freeCheck)
        , freeHead(__null_ptr__)
        , freeTail(__null_ptr__)
        , freeCounter(0)
    {
        ::memset(flags, 0, NUM_OF_BYTE);

        for(WORD16 i = 0; i < MAX_NUM; i++)
        {
            freeEntity(entities[i]);
        }
    }

    WORD16 getFreeSlotNum() const
    {
        if (freeCounter < 0 || freeCounter > MAX_NUM)
        {
//            DBG_LOG("freeCounter Error");
            return USI_INVALID_WORD16;
        }

        return freeCounter;
    }

    WORD16 getBusyNum() const
    {
        return (MAX_NUM - getFreeSlotNum());
    }

    bool hasFreeSlot() const
    {
        return freeHead != __null_ptr__;
    }

    void* alloc()
    {
        if(!hasFreeSlot())
        {
//            DBG_LOG("not free slot");

            return __null_ptr__;
        }
        return doAlloc();
    }

    void free(void* p)
    {
        if(p == __null_ptr__) return;

        if(needFreeCheck)
        {
//            USI_EXPECT_TRUE_VOID(within(p));
//            USI_EXPECT_TRUE_VOID((((char*)p - (char*)entities) % sizeof(Entity)) == 0);

            const unsigned int index = getIndex(p);
            const unsigned char mask = __F_MASK(index);
            const unsigned int n = __F_INDEX(index);
            if((flags[n] & mask) == 0)
            {
//                DBG_LOG("block[%d] has been freed(%d:%d)", index, sizeof(T), MAX_NUM);
                return;
            }

            flags[n] &= ~mask;
        }

        freeEntity(*(Entity*)p);

    }

    bool within(void* p) const
    {
        return p >= (void*)entities && p < (void*)&(entities[MAX_NUM]);
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
//            USI_ASSERT_VALID_PTR_VOID(freeTail);
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
    Entity entities[MAX_NUM];
    unsigned char flags[NUM_OF_BYTE];
};

#endif
