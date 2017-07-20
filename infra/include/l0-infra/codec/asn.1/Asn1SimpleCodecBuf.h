#ifndef INCL_USI_Asn1SimpleCodecBuf_2013105115539_H__
#define INCL_USI_Asn1SimpleCodecBuf_2013105115539_H__

#include "l0-infra/codec/asn.1/Asn1CodecBuf.h"

ASN1_NS_BEGIN

struct Asn1SimpleCodecBuf 
      : Asn1CodecBuf
{
    Asn1SimpleCodecBuf(Oct* buf, U32 size);

    OVERRIDE(Oct* alloc(U32 octs));

    U32 getUsedOcts() const;

private:
    U32 getAvailOcts() const;

private:
    Oct* buf;
    U32 size;
    Oct* cursor;
};

ASN1_NS_END

#endif

