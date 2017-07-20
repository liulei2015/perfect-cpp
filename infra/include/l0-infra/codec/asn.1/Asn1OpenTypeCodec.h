#ifndef INCL_USI_Asn1OpenTypeCodec_2013109181207_H__
#define INCL_USI_Asn1OpenTypeCodec_2013109181207_H__

#include "l0-infra/codec/asn.1/asn1.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/codec/asn.1/Asn1OpenType.h"

ASN1_NS_BEGIN

struct Asn1DecodingContext;

struct ASN1_OpenType_Codec
{
    static Status decode(Asn1DecodingContext& context, ASN1_OpenType& value);
};

ASN1_NS_END

#endif

