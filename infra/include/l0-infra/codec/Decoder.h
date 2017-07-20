/*
 * Decoder.h
 *
 *  Created on: 2012-5-25
 *      Author: lte
 */

#ifndef DECODER_H_
#define DECODER_H_

#include "l0-infra/base/StructObject.h"
#include "l0-infra/base/Status.h"
#include "Asn1Context.h"
#include "l0-infra/base/BaseTypes.h"

struct Decoder
{
	Decoder(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned = false);
	Decoder(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned, size_t bitOffset);

    template<typename PROTOCOL_MSG_TYPE>
    Status decode(ASN1STATUS (*decodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE*), PROTOCOL_MSG_TYPE& protocolMsg)
    {
        return (initCtxtStatus == ASN1_OK ? doDecode(decodeFunction, &protocolMsg) : USI_FAILED);
    }

    size_t getUsedBytes() const;

private:
    void init(const void *sBuf, size_t sSize, BYTE* dBuf, size_t dSize, bool aligned);

private:
    template<typename PROTOCOL_MSG_TYPE>
    Status doDecode(ASN1STATUS (*decodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE*), PROTOCOL_MSG_TYPE* msg)
    {
        if (ASN1_OK != decodeFunction(&context, msg))
        {
            Asn1PrintErrorInfoList(context.errorInfo);
            return USI_FAILED;
        }
        return USI_SUCCESS;
    }

private:
	int initCtxtStatus;
	Asn1Ctxt context;
	int decodeBuffLen;
};

#endif /* DECODER_H_ */


