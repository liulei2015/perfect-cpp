#include "l0-infra/util/OctStreamConverter.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/util/NetMacro.h"
#include <string.h>

USI_NS_BEGIN

void OctStreamConverter::toAsn1Bits_L(const WORD32 hostLong, BYTE* stream, ASN1UINT& size)
{
    toAsn1OctStr_L(hostLong, stream, size);
    size *= 8;
}

void OctStreamConverter::toAsn1Bits_S(const WORD16 hostShort, BYTE* stream, ASN1UINT& size)
{
    toAsn1OctStr_S(hostShort, stream, size);
    size *= 8;
}

void OctStreamConverter::toAsn1OctStr_L(const WORD32 hostLong, BYTE* stream, ASN1UINT& size)
{
	USI_ASSERT_VALID_PTR_VOID(stream);

	size = sizeof(WORD32);
    WORD32 hl = htonl(hostLong);
	::memcpy(stream, &hl, size);
}

void OctStreamConverter::toAsn1OctStr_S(const WORD16 hostShort, BYTE* stream, ASN1UINT& size)
{
	USI_ASSERT_VALID_PTR_VOID(stream);
    WORD16 hs = htons(hostShort);
	size = sizeof(WORD16);
	::memcpy(stream, &hs, size);
}

WORD32 OctStreamConverter::getHostValue_L(const BYTE* stream, const ASN1UINT& size)
{
	WORD32 netLong = 0;
	::memcpy(&netLong, stream, size);
	return ntohl(netLong);
}

WORD16 OctStreamConverter::getHostValue_S(const BYTE* stream, const ASN1UINT& size)
{
	WORD16 netShort = 0;
	::memcpy(&netShort, stream, size);
	return ntohs(netShort);
}

WORD16 OctStreamConverter::getHostValue_S_Bits(const BYTE* stream, const ASN1UINT& numBits)
{
    return getHostValue_S(stream, (numBits+7)/8);
}

BYTE OctStreamConverter::getBitsMask(BYTE numBits)
{
    return (1 << numBits) - 1;
}

USI_NS_END

