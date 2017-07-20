#ifndef INCL_USI_H274FA098_9318_4BE0_B7A3_AA7E955FE675
#define INCL_USI_H274FA098_9318_4BE0_B7A3_AA7E955FE675

#include "l0-infra/base/LinkedAllocator.h"
#include "l0-infra/base/mem_zero.h"
#include "l0-infra/log/UsfLog.h"

USI_NS_BEGIN

template <typename T, WORD32 MAX_NUM>
struct SequenceList
{
    SequenceList() : num(0)
    {
    }

    void add(const T& elem)
    {
        USI_ASSERT_TRUE_VOID(size() < MAX_NUM);
        USI_ASSERT_TRUE_VOID(!contains(elem));

        elems[num++] = elem;
    }

    void remove(const T& elem)
    {
        USI_ASSERT_TRUE_VOID(contains(elem));

        WORD32 cursor = 0;

        for(WORD32 index = 0; index < num; ++index)
        {
            if(elem == elems[index])
            {
                cursor = index;
                break;
            }
        }

        for(WORD32 index = cursor; index < num; ++index)
        {
            elems[index] = elems[index + 1];
        }

        num--;
    }

    bool contains(const T& elem) const
    {
        for(WORD32 index = 0; index < num; ++index)
        {
            if(elem == elems[index]) return true;
        }

        return false;
    }

    void reset()
    {
        num = 0;
    }

    WORD16 size() const
    {
        return num;
    }

    Status visitAllBusyElems(AllocatorVisitor<T>& visitor)
    {
        return access(visitor);
    }

    Status visitAllBusyElems(ConstAllocatorVisitor<T>& visitor) const
    {
        return const_cast<SequenceList&>(*this).access(visitor);
    }

private:
    template<typename VISITOR>
    Status access(VISITOR& visitor)
    {
        for(WORD32 index = 0; index < num; ++index)
        {
            USI_ASSERT_SUCC_CALL(visitor.visit(elems[index]));
        }

        return USI_SUCCESS;
    }

private:
    WORD32 num;
    T elems[MAX_NUM];
};

USI_NS_END

#endif

