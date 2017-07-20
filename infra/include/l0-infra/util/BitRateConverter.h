#ifndef INCL_USI_UTIL_BITRATE_CONVERTER_H
#define INCL_USI_UTIL_BITRATE_CONVERTER_H

#include "l0-infra/base/BaseTypes.h"

struct BitRateConverter
{
	static BYTE getCeilingBitsToByte(unsigned int len);
	static WORD32 getCeilingBitsToKB(WORD64 bitRate);

    static WORD64 getKBToBits(WORD32 KB);

private:
	BitRateConverter();
};

#endif

