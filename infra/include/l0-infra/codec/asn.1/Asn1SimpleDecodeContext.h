#ifndef INCL_USI_Asn1SimpleDecodeContext_20130929193317_H__
#define INCL_USI_Asn1SimpleDecodeContext_20130929193317_H__

#include "l0-infra/codec/asn.1/Asn1DecodingContext.h"
#include "l0-infra/codec/asn.1/Asn1PerDecoder.h"

ASN1_NS_BEGIN

struct Asn1Segment;
struct Asn1DecodeListener;

struct Asn1SimpleDecodeContext : Asn1DecodingContext
{
    Asn1SimpleDecodeContext
        ( Asn1Segment& segment
        , Asn1CodecBuf& buf);

    Asn1SimpleDecodeContext
        ( Asn1Segment& loader
        , Asn1CodecBuf& buf
        , Asn1DecodeListener& listener);

    OVERRIDE(Asn1PerDecoder& getDecoder());
    OVERRIDE(Asn1DecodeListener& getListener());
    OVERRIDE(Asn1CodecBuf& getCodecBuf());

private:
    Asn1PerDecoder decoder;
    Asn1CodecBuf& buf;
    Asn1DecodeListener& listener;
};

ASN1_NS_END

#endif

