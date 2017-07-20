#include "l0-infra/codec/Encoder.h"
#include "l0-infra/codec/Asn1Memory.h"

Encoder::Encoder(const BYTE* streamBuff, WORD32 buffSize, bool aligned)
    : initCtxtStatus(false)
{
    Asn1InitUserMemory();
	initCtxtStatus = Asn1InitEncodeCtxt(&context, const_cast<BYTE*>(streamBuff), buffSize, aligned);
	context.pIE_OFFSETs = 0;
	memset(&context.decodeBuff, 0,sizeof(context.decodeBuff));
}

WORD16 Encoder::getMsgLen() const
{
    Asn1Ctxt* mctxt =  const_cast<Asn1Ctxt*>(&context);
	return (WORD16) Asn1GetCodeLength(mctxt);
}

Asn1Ctxt& Encoder::getAsn1Ctxt() const 
{
    return const_cast<Asn1Ctxt&>(context);
}
