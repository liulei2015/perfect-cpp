#ifndef INCL_USI_Asn1CodecBuf_2013105101142_H__
#define INCL_USI_Asn1CodecBuf_2013105101142_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/codec/asn.1/Asn1Types.h"

ASN1_NS_BEGIN

DEFINE_ROLE(Asn1CodecBuf)
{
    ABSTRACT(Oct* alloc(U32 octs));
};

ASN1_NS_END

#endif

