#ifndef INCL_USI_Asn1DecodingContext_20130929191950_H__
#define INCL_USI_Asn1DecodingContext_20130929191950_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/codec/asn.1/asn1.h"
#include "l0-infra/codec/asn.1/Asn1DecodeListener.h"

ASN1_NS_BEGIN

struct Asn1PerDecoder;
struct Asn1CodecBuf;

DEFINE_ROLE(Asn1DecodingContext)
{
    ABSTRACT(Asn1PerDecoder& getDecoder());
    ABSTRACT(Asn1DecodeListener& getListener());
    ABSTRACT(Asn1CodecBuf& getCodecBuf());
};

ASN1_NS_END

#endif

