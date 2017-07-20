#ifndef INCL_UE_CAP_UE_CAPABILITY_STREAM_CONTAINER_H
#define INCL_UE_CAP_UE_CAPABILITY_STREAM_CONTAINER_H

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/max_min.h"
#include <memory.h>

template <WORD16 N>
struct StreamBuffer
{
    StreamBuffer() 
        : len(0) 
    {
    }

    StreamBuffer(const BYTE* input, WORD16 length)
        : len(__USI_MIN(N, length))
    {
        ::memcpy(buffer, input, len);
    }

    StreamBuffer(const StreamBuffer& rhs)
        : len(rhs.len)
    {
        ::memcpy(buffer, rhs.buffer, len);
    }

    StreamBuffer& operator=(const StreamBuffer& rhs)
    {
        len = rhs.len;
        ::memcpy(buffer, rhs.buffer, len);
        return *this;
    }

    void updateStream(const BYTE* input, WORD16 length = N)
    {
        len = __USI_MIN(N, length);
        ::memcpy(buffer, input, len);
    }

    void setLength(WORD16 len)
    {
        this->len = len;
    }

    WORD16 getLength() const
    {
        return len;
    }

    void copyTo(BYTE* output) const
    {
        ::memcpy(output, buffer, len);
    }

    void copyTo(BYTE* output, WORD16& len) const
    {
        len = this->len;
        copyTo(output);
    }

    void copyTo(BYTE* output, BYTE& len) const
    {
        len = (BYTE)this->len;
        copyTo(output);
    }

    bool matches(BYTE* content, BYTE len) const
    {
        if((BYTE)this->len != len) return false;

        return ::memcmp(content, buffer, len) == 0;
    }
    //////////////////////////////////////////////////////////////////////////
    operator const BYTE*() const
    {
        return buffer;
    }

    const BYTE* getStreamBuf() const
    {
        return buffer;
    }
	
    BYTE* getStreamBuf()
    {
        return buffer;
    }
	
    WORD16 getBuffSize() const
    {
        return N;
    }

protected:
    WORD16 len;
    BYTE   buffer[N];
};

#endif

