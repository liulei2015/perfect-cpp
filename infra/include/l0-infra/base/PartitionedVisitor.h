#ifndef INCL_USI_H91776D3D_6374_47DC_B981_BBB09161BA71
#define INCL_USI_H91776D3D_6374_47DC_B981_BBB09161BA71

#include "l0-infra/base/max_min.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/AllocatorVisitor.h"

USI_NS_BEGIN

struct PartitionedVisitor
{
    PartitionedVisitor(WORD16 maxNum, WORD16 step)
        : maxNum(maxNum), step(step)
    {
        reset();
    }

    bool hasNext() const
    {
        if(maxNum == 0 || beginIndex >= maxNum) return false;

        return true;
    }

    void next()
    {
        beginIndex += step;
        endIndex += step;

        if(endIndex > maxNum)
        {
            endIndex = maxNum;
        }
    }

    WORD16 begin() const
    {
        return beginIndex;
    }

    WORD16 end() const
    {
        return endIndex;
    }

    void reset()
    {
        beginIndex = 0;
        endIndex = __USI_MIN(step, maxNum);
    }

private:
    WORD16 maxNum;
    WORD16 step;
    WORD16 beginIndex;
    WORD16 endIndex;
};

template<typename T>
struct PartitionedAllocatorVisitor : PartitionedVisitor, ConstAllocatorVisitor<T>
{
    PartitionedAllocatorVisitor(WORD16 maxNum, WORD16 step) : PartitionedVisitor(maxNum, step)
    {
    }

    virtual ~PartitionedAllocatorVisitor() {}
    virtual Status visit(const T&)= 0;
};

USI_NS_END

#endif

