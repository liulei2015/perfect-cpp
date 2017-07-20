#ifndef INCL_USI_CODEC_GENERIC_ENCODING_BUFFER_H
#define INCL_USI_CODEC_GENERIC_ENCODING_BUFFER_H

#include "l0-infra/codec/CodecBuffer.h"
#include <string.h>

template <size_t SIZE>
struct GenericCodecBuffer : CodecBuffer
{
    GenericCodecBuffer() : len(0) 
    {
    }

    OVERRIDE(BYTE* getStreamBuff() const)
    {
        return (BYTE*)buf;
    }

    OVERRIDE(const size_t getStreamBuffLen() const)
    {
        return SIZE;
    }

    OVERRIDE(void setStreamLen(size_t len))
    {
        this->len = len;
    }

    OVERRIDE(const size_t getStreamLen() const)
    {
        return len;
    }

    OVERRIDE(void assignBy(const BYTE* msg, size_t length))
    {
        if(length > SIZE) return;

        memcpy(buf, msg, length);
        len = length;
    }

private:
    size_t len;
    BYTE buf[SIZE];
};

#endif

