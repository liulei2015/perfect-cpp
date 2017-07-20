#include "l0-infra/codec/asn.1/Asn1OpenTypeCodec.h"
#include "l0-infra/codec/asn.1/Asn1DecodingContext.h"
#include "l0-infra/codec/asn.1/Asn1OpenType.h"
#include "l0-infra/codec/asn.1/Asn1PerDecoder.h"

ASN1_NS_BEGIN

Status ASN1_OpenType_Codec::decode(Asn1DecodingContext& context, ASN1_OpenType& value)
{
    return context.getDecoder().decodeOpenType(value);
}

ASN1_NS_END

