#ifndef INCL_CODEC_FIX_SIZE_BUFF_H
#define INCL_CODEC_FIX_SIZE_BUFF_H

#include "l0-infra/base/BaseTypes.h"
#include <memory.h>

template <size_t SIZE>
struct FixSizeBuff
{
    FixSizeBuff()
    {
    }

    explicit FixSizeBuff(const BYTE* buf)
    {
        memcpy(buff, buf, SIZE);
    }

    FixSizeBuff(const FixSizeBuff& rhs)
    {
        memcpy(buff, rhs.buff, SIZE);
    }

    FixSizeBuff& operator=(const FixSizeBuff& rhs)
    {
        memcpy(buff, rhs.buff, SIZE);
        return *this;
    }

    bool operator==(const FixSizeBuff& rhs) const
    {
        return memcmp(buff, rhs.buff, SIZE) == 0;
    }

    bool operator!=(const FixSizeBuff& rhs) const
    {
        return !(*this == rhs);
    }

    size_t size() const
    {
        return SIZE;
    }

    operator const BYTE*() const
    {
        return buff;
    }

    operator BYTE*()
    {
        return buff;
    }

    void update(const BYTE* buf)
    {
        memcpy(buff, buf, SIZE);
    }

    void copyTo(BYTE* buffDes) const
    {
        ::memcpy(buffDes, buff, SIZE);
    }

    const BYTE* getContent() const
    {
        return buff;
    }

    BYTE* getBuffer() const
    {
        return (BYTE*)buff;
    }

    bool matches(BYTE* content) const
    {
        return ::memcmp(content, buff, SIZE) == 0;
    }

protected:
    BYTE buff[SIZE];
};

#endif

