#ifndef INCL_USI_Asn1EncodedStream_2013106203841_H__
#define INCL_USI_Asn1EncodedStream_2013106203841_H__

#include "l0-infra/codec/asn.1/Asn1Segment.h"

ASN1_NS_BEGIN

struct Asn1EncodedStream : Asn1Segment
{
    Asn1EncodedStream
        ( Oct* startOct
        , U32  numOfOcts)
        : Asn1Segment(startOct, numOfOcts * 8)
    {
    }
};

ASN1_NS_END

#endif

