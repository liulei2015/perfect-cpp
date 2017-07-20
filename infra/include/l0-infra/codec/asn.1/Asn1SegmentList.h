#ifndef INCL_USI_Asn1SegmentList_2013106175411_H__
#define INCL_USI_Asn1SegmentList_2013106175411_H__

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/base/Status.h"

ASN1_NS_BEGIN

struct Asn1BitPos;
struct Asn1CodecBuf;
struct Asn1Segment;

struct Asn1SegmentList
{
    explicit Asn1SegmentList(Asn1CodecBuf& codecBuf);

    Status pushBack(const Asn1BitPos& start, U32 numOfBits);
    Asn1Segment* getFirstSegment() const;

private:
    Asn1CodecBuf& codecBuf;
    Asn1Segment* firstSegment;
    Asn1Segment* lastSegment;
};

ASN1_NS_END

#endif

