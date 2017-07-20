#include "l0-infra/codec/asn.1/Asn1Segment.h"
#include "l0-infra/codec/asn.1/Asn1BitPos.h"

ASN1_NS_BEGIN

Asn1Segment::Asn1Segment
    ( Oct* startOct
    , U32  numOfBits)
    : startOct(startOct)
    , numOfBits(numOfBits)
    , nextSegment(0)
{
}

void Asn1Segment::getScope(Asn1BitPos& start, Asn1BitPos& end) const
{
    start = Asn1BitPos(startOct, 0);
    end   = Asn1BitPos(startOct + numOfBits/8, (U8)(numOfBits % 8));
}

Asn1Segment* Asn1Segment::getNextSegment() const
{
    return nextSegment;
}

U32 Asn1Segment::getNumOfBits() const
{
    return numOfBits;
}

Oct* Asn1Segment::getStartOct() const
{
    return startOct;
}

void Asn1Segment::onSegmentAppend(Asn1Segment* nextSegment)
{
    this->nextSegment = nextSegment;
}

ASN1_NS_END

