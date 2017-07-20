#ifndef INCL_USI_ObjectArray_20130926052003_H__
#define INCL_USI_ObjectArray_20130926052003_H__

#include <l0-infra/base/Status.h>
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/BaseTypes.h"

#include <stddef.h>
#include <string.h>
#include "stdio.h"


USI_NS_BEGIN

template <typename T, WORD32 MAX_NUM>
struct ObjectArray
{
    ObjectArray() : num(0) 
    {
    }

    Status copyFrom(const T* objects, WORD32 numOfObjects)
    {
        USI_ASSERT_TRUE(numOfObjects <= MAX_NUM);

        ::memcpy(values, objects, numOfObjects*sizeof(T));
        num = numOfObjects;

        return USI_SUCCESS;
    }

    T* newElem()
    {
        if(num >= MAX_NUM) return 0;

        return &values[num++];
    }

    WORD32 size() const
    {
        return num;
    }

    const T* operator[](unsigned int index) const
    {
        return getValue(index);
    }

    T* operator[](unsigned int index)
    {
        return getValue(index);
    }

    static size_t getSizeOfPadding()
    {
        typedef ObjectArray<T, MAX_NUM> ThisType;
        return offsetof(ThisType, values) - sizeof(num);
    }

private:
    T* getValue(unsigned int index) const
    {
        return (index < num) ? const_cast<T*>(&values[index]) : 0;
    }

private:
    WORD32 num;
    T      values[MAX_NUM];
};

USI_NS_END

#endif

