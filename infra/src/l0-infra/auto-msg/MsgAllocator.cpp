#include "l0-infra/auto-msg/MsgAllocator.h"
#include "l0-infra/allocator/StaticObjectAllocator.h"

namespace
{
    template<size_t MEM_BLOCK_SIZE, WORD BLOCK_NUM>
    struct BlockAllocator
    {
        BlockAllocator()
        {

        }

        static void* alloc()
        {
            return allocator.alloc();
        }

        static void free(void* p)
        {
            allocator.free(p);
        }

        static bool tryAlloc(size_t size)
        {
            return (size <= MEM_BLOCK_SIZE) && (allocator.hasFreeSlot());
        }

        static bool tryFree(void *p)
        {
            WORD64 lower_bound = (WORD64)(&(allocator));
            WORD64 upper_bound = lower_bound + MEM_BLOCK_SIZE*BLOCK_NUM;
            return (lower_bound <= (WORD64)p) && ((WORD64)p < upper_bound);
        }

    private:
        struct Block
        {
            char mem[MEM_BLOCK_SIZE];
        };

    private:
        typedef StaticObjectAllocator<Block, BLOCK_NUM> InnerBlockAllocator;
        static InnerBlockAllocator allocator;
    };

    template<size_t MEM_BLOCK_SIZE, WORD BLOCK_NUM>
    typename BlockAllocator<MEM_BLOCK_SIZE, BLOCK_NUM>::InnerBlockAllocator BlockAllocator<MEM_BLOCK_SIZE, BLOCK_NUM>::allocator;

#define K(s) s * 1024

    typedef BlockAllocator<K(32),  16> Msg32KAllocator;
    typedef BlockAllocator<K(64),  8> Msg64KAllocator;
    typedef BlockAllocator<K(128), 4> Msg128KAllocator;
    typedef BlockAllocator<K(256), 2> Msg256KAllocator;
    typedef BlockAllocator<K(512), 16> Msg512KAllocator;
}

#define __BLOCK_NAME(n) Msg##n##KAllocator
#define TRY_BLOCK(n) if(__BLOCK_NAME(n)::tryAlloc(size))  return __BLOCK_NAME(n)::alloc()

void* MsgAllocator::alloc(size_t size)
{
    TRY_BLOCK(32);
    TRY_BLOCK(64);
    TRY_BLOCK(128);
    TRY_BLOCK(256);
    TRY_BLOCK(512);
    
    DBG_LOG("The specified size is too big for allocator, size = %d!", size);

    return 0;
}

#define TRY_FREE(n) if(__BLOCK_NAME(n)::tryFree(p))  return __BLOCK_NAME(n)::free(p)

void  MsgAllocator::free(void* p)
{
    TRY_FREE(32);
    TRY_FREE(64);
    TRY_FREE(128);
    TRY_FREE(256);
    TRY_FREE(512);

    DBG_LOG("The freed pointer(%x) is not in any MsgAllocator!", p);

    return;
}

