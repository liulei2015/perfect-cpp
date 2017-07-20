#include "l0-infra/util/BitRateConverter.h"
#include "l0-infra/util/BitRateUnit.h"

BYTE BitRateConverter::getCeilingBitsToByte(unsigned int len)
{
	return (BYTE)((len + (BITS_PER_BYTE) - 1)/(BITS_PER_BYTE));
}

WORD32 BitRateConverter::getCeilingBitsToKB(WORD64 bitRate)
{
	return (WORD32)((bitRate + (BITE_PER_KBYTE) - 1)/(BITE_PER_KBYTE));
}

WORD64 BitRateConverter::getKBToBits(WORD32 KB)
{
    return ((WORD64)KB) * BITE_PER_KBYTE;
}
