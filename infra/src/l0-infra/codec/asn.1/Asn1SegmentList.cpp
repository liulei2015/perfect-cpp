#include "l0-infra/codec/asn.1/Asn1SegmentList.h"
#include "l0-infra/codec/asn.1/Asn1CodecBuf.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/Asn1Segment.h"
#include "l0-infra/codec/asn.1/Asn1BitPos.h"

#include "l0-infra/base/max_min.h"
#include "l0-infra/base/Assertions.h"
#include <new>

ASN1_NS_BEGIN

Asn1SegmentList::Asn1SegmentList(Asn1CodecBuf& codecBuf)
    : codecBuf(codecBuf)
    , firstSegment(0)
    , lastSegment(0)
{
}

Status Asn1SegmentList::pushBack(const Asn1BitPos& startPos, U32 numOfBits)
{
    if(numOfBits == 0) return USI_SUCCESS;

    Oct* oct = 0;
    if(startPos.isPhyOctAligned())
    {
        oct = const_cast<Oct*>(startPos.getOct());
    }
    else
    {
        oct = codecBuf.alloc(__CELLING(numOfBits, 8));
        USI_ASSERT_VALID_PTR_R(oct, ASN1_E_CODEC_BUF);
        
        startPos.copyTo(Asn1BitPos(oct), numOfBits);
    }

    Oct* segMem = codecBuf.alloc(sizeof(Asn1Segment));
    USI_ASSERT_VALID_PTR_R(segMem, ASN1_E_CODEC_BUF);

    Asn1Segment* seg = new (segMem) Asn1Segment(oct, numOfBits);

    if(lastSegment != 0)
    {
        lastSegment->onSegmentAppend(seg);
    }

    if(firstSegment == 0)
    {
        firstSegment = seg;
    }

    lastSegment = seg;

    return USI_SUCCESS;
}

Asn1Segment* Asn1SegmentList::getFirstSegment() const
{
    return firstSegment;
}

ASN1_NS_END

