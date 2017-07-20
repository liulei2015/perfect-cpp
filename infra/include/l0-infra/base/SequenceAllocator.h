#ifndef INCL_USI_HE78DFB10_17F6_4EAD_960D_13E186B651D4
#define INCL_USI_HE78DFB10_17F6_4EAD_960D_13E186B651D4

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/max_min.h"
#include "l0-infra/base/NullPtr.h"
#include <stdio.h>

template<class T, WORD32 MAX_SIZE>
struct SequenceAllocator
{
    struct Block
    {
        T       elem;
        WORD32  nextIndex;

        Block() : nextIndex(INVALID_INDEX)
        {
        }

        bool isBusy() const
        {
            return nextIndex == INVALID_INDEX;
        }

        bool validateElem(const T* p) const
        {
            return p == &elem;
        }

        void disable()
        {
            nextIndex = INVALID_INDEX;
        }

    private:
        enum { INVALID_INDEX = 0xFFFFFFFF };
    };

    SequenceAllocator(WORD32 size = MAX_SIZE) : maxSize(__USI_MIN(size, MAX_SIZE))
                                              , freeIndex(0)
                                              , freeNum(maxSize)
    {
        memset(blocks, 0, sizeof(blocks));

        for (WORD32 i = 0; i < maxSize; i++)
        {
            blocks[i].nextIndex = i + 1;
        }
        blocks[maxSize-1].disable();
        lastIndex = maxSize-1;
    }

    T *alloc()
    {
        if ((freeNum == 0) || (freeIndex >= maxSize))
        {
            return __null_ptr__;
        }

        WORD32 allocIndex = freeIndex;
        freeIndex     = blocks[allocIndex].nextIndex;
        blocks[allocIndex].disable();
        freeNum--;

        if(freeNum == 0)
        {
            lastIndex = freeIndex;
        }

        return &(blocks[allocIndex].elem);
    }

    void free(T* p)
    {
        Block* beFreedBlock = (Block*)p;

        if ((beFreedBlock == __null_ptr__) || (!beFreedBlock->isBusy()))
        {
            return;
        }

        WORD32 beFreedIndex  = (beFreedBlock - blocks);
        if ((&(blocks[beFreedIndex].elem) != p) || (beFreedIndex == lastIndex) || (beFreedIndex >= maxSize))
        {
            return;
        }

        if(freeNum == 0)
        {
            lastIndex = beFreedIndex;
        }

        beFreedBlock->nextIndex = freeIndex;
        freeIndex = beFreedIndex;
        freeNum++;
    }

    WORD32 getFreeNum() const
    {
    	return freeNum;
    }

    WORD32 size() const
    {
    	return maxSize;
    }

    void dump() const
    {
        printf("\n--------freeIndex: %lu, freeNum: %lu, lastIndex: %lu--------\n", freeIndex, freeNum, lastIndex);
    	for(WORD32 i = 0; i< size(); ++i)
    	{
    		printf("blocks[%lu]: %x, nextIndex: %lu\n", i, &(blocks[i].elem), blocks[i].nextIndex);
    	}
    }

private:
    WORD32 maxSize;
    WORD32 freeIndex;
    WORD32 freeNum;
    WORD32 lastIndex;
    Block  blocks[MAX_SIZE];
};

#endif
