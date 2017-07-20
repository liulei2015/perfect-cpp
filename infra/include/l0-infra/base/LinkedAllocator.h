#ifndef INCL_USI_LINKED_Allocator_H_
#define INCL_USI_LINKED_Allocator_H_

#include "l0-infra/base/List.h"
#include "l0-infra/base/ListElem.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/max_min.h"
#include "l0-infra/base/PartitionedVisitor.h"

USI_NS_BEGIN

struct LinkNode : ListElem<LinkNode>
{
    LinkNode() : isUsed(false) {}
    bool isUsed;
};

template<typename T, WORD16 MAX_SIZE>
struct LinkedAllocator
{
    LinkedAllocator(T* elements, WORD16 size)
        :elements(elements), maxSize(__USI_MIN(size, MAX_SIZE))
    {
        for(WORD16 loop = 0; loop < maxSize; loop++)
        {
            freeList.pushBack(linkNodes[loop]);
        }
    }

    LinkedAllocator()
            :elements(0), maxSize(0)
    {
    }

    T* alloc()
    {
        USI_ASSERT_TRUE_NIL(getBusyNum() < maxSize);

        LinkNode* freeNode = freeList.popFront();
        USI_ASSERT_VALID_PTR_NIL(freeNode);

        busyList.pushBack(*freeNode);
        freeNode->isUsed = true;

        dump("After alloc");

        return &elements[freeNode - &linkNodes[0]];
    }

    Status dealloc(const T& elem)
    {
        WORD16 index = getIndexByPos(elem);
        return doDelloc(index);
    }

    WORD16 getBusyNum() const
    {
        return busyList.getSize();
    }

    Status visitAllBusyElems(AllocatorVisitor<T>& visitor)
    {
        return access(visitor);
    }

    Status visitAllBusyElems(ConstAllocatorVisitor<T>& visitor) const
    {
        return const_cast<LinkedAllocator&>(*this).access(visitor);
    }

    Status visitAllBusyElems(PartitionedAllocatorVisitor<T>& visitor) const
    {
        return const_cast<LinkedAllocator&>(*this).access(visitor);
    }

    bool contains(const T* elem) const
    {
        if(elem == 0) return false;

        printf("In LinkedAllocator contains out: %d", elem);

        LIST_FOREACH(LinkNode, node, busyList)
        {
            if( elem == &elements[&(*node)-&linkNodes[0]])
            {
                printf("In LinkedAllocator busyList find elemPointer: %d == elements[]%d", elem, &elements[&(*node)-&linkNodes[0]]);
                return true;
            }
        }

        return false;
    }

    T* getValue(WORD16 index) const
    {
        if(index >= maxSize) return NULL;
        if(!linkNodes[index].isUsed) return NULL;
        return &elements[index];
    }

    WORD16 getIndexByPos(const T& elem) const
    {
        return (WORD16)(&elem - elements);
    }

    Status doDelloc(WORD16 index)
    {
        USI_ASSERT_TRUE(index <  maxSize);

        if(!linkNodes[index].isUsed)
        {
            printf("FatalError:State of linkNodes[%d] should be \'isUsed\'\n", index);
            return USI_FATAL_BUG;
        }

        busyList.erase(linkNodes[index]);
        freeList.pushBack(linkNodes[index]);
        linkNodes[index].isUsed = false;

        dump("After doDelloc");

        return USI_SUCCESS;
    }

private:
    template<typename VISITOR> 
    Status access(VISITOR& visitor)
    {
        LIST_FOREACH(LinkNode, node, busyList)
        {
            Status status = visitor.visit(elements[&(*node) - &linkNodes[0]]);
            if(status == USI_STOP)
            {
                return USI_SUCCESS;
            }
            USI_ASSERT_TRUE(status == USI_SUCCESS);
        }
        return USI_SUCCESS;
    }

    Status access(PartitionedAllocatorVisitor<T>& visitor)
    {
        USI_ASSERT_TRUE(visitor.begin() <  maxSize);
        USI_ASSERT_TRUE(visitor.end() <=  maxSize);

        for(WORD16 index = visitor.begin(); index < visitor.end(); ++index)
        {
            if(linkNodes[index].isUsed)
            {
                Status status = visitor.visit(elements[&linkNodes[index] - &linkNodes[0]]);
                if(status == USI_STOP)
                {
                    return USI_SUCCESS;
                }
                USI_ASSERT_TRUE(status == USI_SUCCESS);
            }
        }

        return USI_SUCCESS;
    }

    void dump(const char* str)
    {
        DBG_LOG("=====%s=====\n", str);
        DBG_LOG("maxSize : %u\n", maxSize);
        DBG_LOG("freeList size : %u\n", freeList.getSize());
        DBG_LOG("busyList size : %u\n", busyList.getSize());
    }

private:
    List<LinkNode>  freeList;
    List<LinkNode>  busyList;

    LinkNode linkNodes[MAX_SIZE];
    T*    elements; 
    WORD16 maxSize;
};

USI_NS_END

#endif

