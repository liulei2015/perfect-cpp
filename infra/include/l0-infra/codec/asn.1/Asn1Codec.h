#ifndef INCL_USI_Asn1Codec_2013109211018_H__
#define INCL_USI_Asn1Codec_2013109211018_H__

#include "l0-infra/codec/asn.1/Asn1DecodingContext.h"
#include "l0-infra/base/Status.h"

ASN1_NS_BEGIN

template <typename T>
Status ASN1_decode(Asn1DecodingContext& context, T& value);

ASN1_NS_END

#endif

