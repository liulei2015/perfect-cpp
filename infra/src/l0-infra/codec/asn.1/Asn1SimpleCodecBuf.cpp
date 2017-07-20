#include "l0-infra/codec/asn.1/Asn1SimpleCodecBuf.h"
#include <stdio.h>
#include <memory.h>

ASN1_NS_BEGIN

Asn1SimpleCodecBuf::Asn1SimpleCodecBuf(Oct* buf, U32 size)
    : buf(buf)
    , size(size)
    , cursor(buf)
{
}

U32 Asn1SimpleCodecBuf::getUsedOcts() const
{
    return cursor - buf;
}

U32 Asn1SimpleCodecBuf::getAvailOcts() const
{
    return (U32)(buf + size - cursor);
}

Oct* Asn1SimpleCodecBuf::alloc(U32 octs)
{
    if(octs > getAvailOcts())
    {
        return 0;
    }

    Oct* result = cursor;
    //memset(result, 0, octs);

    cursor += octs;

    return result;
}


ASN1_NS_END

