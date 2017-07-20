#ifndef INCL_USI_CODEC_INJECTED_ENCODING_BUFFER_H
#define INCL_USI_CODEC_INJECTED_ENCODING_BUFFER_H

#include "l0-infra/codec/CodecBuffer.h"

struct InjectedCodecBuffer : CodecBuffer
{
    InjectedCodecBuffer(BYTE* buf, size_t& len);

    OVERRIDE(BYTE* getStreamBuff() const);
    OVERRIDE(const size_t getStreamBuffLen() const);

    OVERRIDE(void setStreamLen(size_t len));
    OVERRIDE(const size_t getStreamLen() const);

    OVERRIDE(void assignBy(const BYTE* msg, size_t length));

private:
    BYTE* buf;
    size_t& len;

    size_t bufLen;
    size_t streamLen;
};

#endif

