#include "l0-infra/codec/Decoder.h"
#include "l0-infra/codec/Asn1Memory.h"
#include "l0-infra/codec/Asn1Per.h"
#include "l0-infra/log/UsfLog.h"

Decoder::Decoder(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned)
{
    init(sBuf, sSize, dBuf, dSize, aligned);
}

Decoder::Decoder(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned, size_t bitOffset)
{
    init(sBuf, sSize, dBuf, dSize, aligned);

    Asn1SetBitOffset(&context, bitOffset);
}

void Decoder::init(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned)
{
    initCtxtStatus = Asn1InitDecodeCtxt(&context,
            (BYTE*)sBuf,
            (ASN1UINT)sSize,
             dBuf,
            (int)dSize,
            aligned);

    if(initCtxtStatus != 0)
    {
        DBG_LOG("unexpected sBuff[%x] or sSize[%d]", sBuf, sSize);
    }

    context.pIE_OFFSETs = 0;
    decodeBuffLen = (int)dSize;
}

size_t Decoder::getUsedBytes() const
{
	//upgrade to V3.2 liyongshun
	return decodeBuffLen - context.decodeBuff.buffHandler.freeSize;
}

