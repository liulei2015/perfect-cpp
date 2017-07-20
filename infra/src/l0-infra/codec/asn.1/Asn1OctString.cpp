#include "l0-infra/codec/asn.1/Asn1OctString.h"
#include "l0-infra/codec/asn.1/Asn1Segment.h"

ASN1_NS_BEGIN

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
Oct Asn1OctString::operator[](U32 index) const
{
    if(index >= size())
    {
        return 0xFF;
    }

    U32 numOfOcts = 0;
    for(Asn1Segment* seg = segment; seg != 0; seg = seg->getNextSegment())
    {
        U32 octs = seg->getNumOfBits() / 8;

        if(index < (numOfOcts + octs))
        {
            return *(seg->getStartOct() + (index - numOfOcts));
        }

        numOfOcts += octs;
    }

    return 0xFF;
}

ASN1_NS_END

