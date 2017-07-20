#ifndef INCL_USI_Asn1Segment_2013106174319_H__
#define INCL_USI_Asn1Segment_2013106174319_H__

#include "l0-infra/codec/asn.1/Asn1Types.h"

ASN1_NS_BEGIN

struct Asn1BitPos;

struct Asn1Segment
{
    Asn1Segment
        ( Oct* startOct
        , U32  numOfBits);

    void getScope(Asn1BitPos& start, Asn1BitPos& end) const;

    Asn1Segment* getNextSegment() const;
    void onSegmentAppend(Asn1Segment* nextSegment);
    Oct* getStartOct() const;
    U32 getNumOfBits() const;
    
private:
    Oct* startOct;
    U32  numOfBits;
    Asn1Segment* nextSegment;
};

ASN1_NS_END

#endif

