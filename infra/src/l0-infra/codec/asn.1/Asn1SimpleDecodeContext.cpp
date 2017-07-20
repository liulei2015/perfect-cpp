#include "l0-infra/codec/asn.1/Asn1SimpleDecodeContext.h"

ASN1_NS_BEGIN

namespace
{
    static Asn1DecodeListener nullListener;
}

Asn1SimpleDecodeContext::Asn1SimpleDecodeContext
    ( Asn1Segment& segment
    , Asn1CodecBuf& buf)
    : decoder(&segment, buf)
    , buf(buf)
    , listener(nullListener)
{
}

Asn1SimpleDecodeContext::Asn1SimpleDecodeContext
    ( Asn1Segment& segment
    , Asn1CodecBuf& buf
    , Asn1DecodeListener& listener)
    : decoder(&segment, buf)
    , buf(buf)
    , listener(listener)
{
}

Asn1PerDecoder& Asn1SimpleDecodeContext::getDecoder()
{
    return decoder;
}

Asn1DecodeListener& Asn1SimpleDecodeContext::getListener()
{
    return listener;
}

Asn1CodecBuf& Asn1SimpleDecodeContext::getCodecBuf()
{
    return buf;
}

ASN1_NS_END

