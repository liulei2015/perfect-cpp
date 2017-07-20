#include "l0-infra/codec/InjectedCodecBuffer.h"
#include <string.h>

InjectedCodecBuffer::InjectedCodecBuffer(BYTE* buf, size_t& len)
: buf(buf), len(len), bufLen(len), streamLen(0)
{
}

BYTE* InjectedCodecBuffer::getStreamBuff() const
{
    return buf;
}

const size_t InjectedCodecBuffer::getStreamBuffLen() const
{
    return bufLen;
}

void InjectedCodecBuffer::setStreamLen(size_t len)
{
    this->len = len;
    streamLen = len;
}

const size_t InjectedCodecBuffer::getStreamLen() const
{
    return streamLen;
}

void InjectedCodecBuffer::assignBy(const BYTE* msg, size_t length)
{
    if((length > bufLen) || (buf == 0)) return;

    memcpy(buf, msg, length);
    len = length;
    streamLen = length;
}
