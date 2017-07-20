#include "l0-infra/codec/asn.1/Asn1BitPos.h"
#include "l0-infra/base/max_min.h"
#include <memory.h>
#include <stdio.h>

ASN1_NS_BEGIN

U8 Asn1BitPos::getAvailBits(const Asn1BitPos& end) const
{
    if(oct < end.oct)
    {
        return getAvailBits();
    }
    else if(oct == end.oct)
    {
        return end.bitOffset - __USI_MIN(bitOffset, end.bitOffset);
    }
    else
    {
        return 0;
    }
}

U8 Asn1BitPos::decodeBits(U8 numOfBits)
{
    bitOffset += numOfBits;
    U8 bits = (*oct >> (8 - bitOffset)) & (U8)__BIT_MASK(numOfBits);

    if(bitOffset == 8)
    {
        ++(*this);
    }

    return bits;
}

U32 Asn1BitPos::operator-(const Asn1BitPos& rhs) const
{
    if(*this <= rhs) return 0;

    U32 result = 0;
    if(oct >= rhs.oct + 1)
    {
        result = (U32)(oct - rhs.oct - 1) * 8;
        result += bitOffset + rhs.getAvailBits();
    }
    else
    {
        result = bitOffset - rhs.bitOffset;
    }

    return result;
}

void Asn1BitPos::fastFwd(U32 bits)
{
    oct += bits / 8;
    U8 remain = (U8)(bits % 8);
    if(remain < getAvailBits())
    {
        bitOffset += remain;
    }
    else
    {
        ++oct;
        bitOffset = remain - getAvailBits();
    }
}

Asn1BitPos Asn1BitPos::alignWith(const U8 offset)
{
    if(bitOffset <= offset)
    {
        return Asn1BitPos(oct, bitOffset);
    }
    else
    {
        return Asn1BitPos(oct+1, offset);
    }
}

Asn1BitPos Asn1BitPos::plus(U32 numOfBits) const
{
    Oct* end = oct + numOfBits / 8;
    U32 nOffset = bitOffset + numOfBits % 8;
    end += nOffset / 8;
    nOffset %= 8;

    return Asn1BitPos(end, (U8)nOffset);
}

U8 Asn1BitPos::decodeBitsEx(U8 numOfBits)
{
    U8 remainBits = numOfBits;
    U8 result = 0;
    while(remainBits > 0)
    {
        U8 bits = __USI_MIN(getAvailBits(), remainBits);
        result |= decodeBits(bits) << (remainBits - bits); 
        remainBits -= bits;
    }

    return result;
}

void Asn1BitPos::noAlignCopy(const Asn1BitPos& to, U32 numOfBits) const
{
    Oct* pfrom = const_cast<Oct*>(getOct());
    Oct* pto = const_cast<Oct*>(to.getOct());

    U8 fromAvailBits = getAvailBits();
    U8 toAvailBits = to.getAvailBits();

    if(fromAvailBits > toAvailBits)
    {
        *pto |= ((*pfrom >> (fromAvailBits - toAvailBits)) & __BIT_MASK(toAvailBits));

        Asn1BitPos(pfrom, getBitOffset() + toAvailBits).copyTo(Asn1BitPos(pto + 1), numOfBits - toAvailBits);
    }
    else if(fromAvailBits < toAvailBits)
    {
        *pto |= (*pfrom & __BIT_MASK(fromAvailBits)) << (toAvailBits - fromAvailBits);

        Asn1BitPos(pfrom + 1).copyTo(Asn1BitPos(pto, to.getBitOffset() + fromAvailBits), numOfBits - fromAvailBits);
    }
    else
    {
        *pto |= (*pfrom & __BIT_MASK(fromAvailBits));

        Asn1BitPos(pfrom + 1).copyTo(Asn1BitPos(pto + 1), numOfBits - toAvailBits);
    }
}

void Asn1BitPos::encodeBits(U8 numOfBits, U8 value)
{
    U8 remainBits = numOfBits;
    while(remainBits > 0)
    {
        U8 availBits = 8 - bitOffset;
        U8 bits = __USI_MIN(remainBits, availBits);
        U8 v    = value >> (remainBits - bits);

        *oct |= (v & __BIT_MASK(bits)) << (availBits - bits);

        remainBits -= bits;
        bitOffset += bits;
        if(bitOffset == 8)
        {
            oct++;
        }
    }
}


void Asn1BitPos::alignCopy(const Asn1BitPos& to, U32 numOfBits) const
{
    U32 numOfOcts = numOfBits / 8;
    U8 remainBits = (U8)(numOfBits % 8);

    Oct* pfrom = const_cast<Oct*>(getOct());
    Oct* pto = const_cast<Oct*>(to.getOct());
    bool isFromAligned = isPhyOctAligned();
    bool isToAligned   = to.isPhyOctAligned();

    if(isToAligned && isFromAligned)
    {
        memcpy(pto, pfrom, numOfOcts);
        pfrom += numOfOcts;
        pto   += numOfOcts;
    }
    else if(isFromAligned)
    {
        U8 usedBits = to.getBitOffset();

        for(U32 i=0; i<numOfOcts; i++)
        {
            *pto++ |= (*pfrom >> usedBits);
            *pto   = (*pfrom++ << (8 - usedBits));
        }
    }
    else
    {
        U8 usedBits = getBitOffset();

        for(U32 i=0; i<numOfOcts; i++)
        {
            *pto   = (*pfrom++ << usedBits);
            *pto++ |= (*pfrom >> (8 - usedBits));
        }
    }

    if(remainBits > 0)
    {
        U8 value = Asn1BitPos(pfrom, getBitOffset()).decodeBitsEx(remainBits);
        if(isToAligned) *pto = 0;
        Asn1BitPos(pto, to.getBitOffset()).encodeBits(remainBits, value);
    }
}

void Asn1BitPos::copyTo(const Asn1BitPos& to, U32 numOfBits) const
{
    if(to.isPhyOctAligned() || isPhyOctAligned())
    {
        alignCopy(to, numOfBits);
    }
    else 
    {
        noAlignCopy(to, numOfBits);
    }
}


ASN1_NS_END
