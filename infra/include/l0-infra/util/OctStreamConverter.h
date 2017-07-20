#ifndef INCL_USI_UTIL_OCTSTREAM_CONVERTER_H
#define INCL_USI_UTIL_OCTSTREAM_CONVERTER_H

#include "l0-infra/base/usi.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/codec/Asn1Typedef.h"

USI_NS_BEGIN

struct OctStreamConverter
{
	static void toAsn1OctStr_L(const WORD32 hostLong, BYTE* stream, ASN1UINT& size);
	static void toAsn1OctStr_S(const WORD16 hostShort, BYTE* stream, ASN1UINT& size);
    static void toAsn1Bits_L(const WORD32 hostShort, BYTE* stream, ASN1UINT& size);
    static void toAsn1Bits_S(const WORD16 hostShort, BYTE* stream, ASN1UINT& size);
	static WORD32 getHostValue_L(const BYTE* stream, const ASN1UINT& size);
	static WORD16 getHostValue_S(const BYTE* stream, const ASN1UINT& size);
    static WORD16 getHostValue_S_Bits(const BYTE* stream, const ASN1UINT& numBits);
    static BYTE getBitsMask(const BYTE numBits);
private:
	OctStreamConverter();
};

USI_NS_END

#endif

