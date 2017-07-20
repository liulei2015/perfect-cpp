#ifndef INCL_USI_BASE_FIX_SIZE_ARRAY_H
#define INCL_USI_BASE_FIX_SIZE_ARRAY_H

#include "l0-infra/base/usi.h"
#include "l0-infra/base/BaseTypes.h"
#include <string.h>

USI_NS_BEGIN

template <typename T, WORD32 MAXSIZE, BYTE DEFAULT_VALUE = 0>
struct FixSizeArray
{
    FixSizeArray(WORD32 size = MAXSIZE) : actualSize(size < MAXSIZE? size : MAXSIZE)
    {
    }

    void reset()
    {
         memset(object, DEFAULT_VALUE, sizeof(object));
    }

    const WORD32 capacity() const
    {
        return actualSize;
    }

    const T& operator[](WORD32 index) const
    {
        return object[index];
    }

    T& operator[](WORD32 index)
    {
        return object[index];
    }

private:
    WORD32 actualSize;
    T object[MAXSIZE];
};

USI_NS_END

#endif

