#ifndef INCL_USI_CODEC_ENCODING_BUFFER_H
#define INCL_USI_CODEC_ENCODING_BUFFER_H

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Keywords.h"

DEFINE_ROLE(CodecBuffer)
{
    ABSTRACT(BYTE* getStreamBuff() const);
    ABSTRACT(const size_t getStreamBuffLen() const);
    ABSTRACT(void setStreamLen(size_t));
    ABSTRACT(const size_t getStreamLen() const);
    ABSTRACT(void assignBy(const BYTE* buf, size_t len));
};

#endif

