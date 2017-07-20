#ifndef ENCODER_H_
#define ENCODER_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/StructObject.h"
#include "l0-infra/codec/CodecBuffer.h"
#include "Asn1Typedef.h"
#include "l0-infra/base/Assertions.h"
#include "Asn1Context.h"

struct Encoder {
	Encoder(const BYTE * streamBuff, WORD32 buffSize, bool aligned = false);

	template<typename PROTOCOL_MSG_TYPE, typename RETURN_VALUE_TYPE>
	Status encode(const PROTOCOL_MSG_TYPE& msg,
        RETURN_VALUE_TYPE (*encodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE*))
	{
        return (initCtxtStatus == ASN1_OK ? doEncode(const_cast<PROTOCOL_MSG_TYPE*>(&msg), encodeFunction) :
                USI_FAILED);
	}

    template<typename PROTOCOL_MSG_TYPE, typename RETURN_VALUE_TYPE>
    Status encode(const PROTOCOL_MSG_TYPE& msg,
        RETURN_VALUE_TYPE (*encodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE))
    {
        return (initCtxtStatus == ASN1_OK ? doEncode(msg, encodeFunction) : USI_FAILED);
    }

	WORD16 getMsgLen() const;
     Asn1Ctxt& getAsn1Ctxt() const;

private:
    template<typename PROTOCOL_MSG_TYPE, typename RETURN_VALUE_TYPE>
    Status doEncode(PROTOCOL_MSG_TYPE* msg, RETURN_VALUE_TYPE (*encodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE*))
    {
        if (ASN1_OK != encodeFunction(&context, msg))
        {
            Asn1PrintErrorInfoList(context.errorInfo);
            return USI_FAILED;
        }
        return USI_SUCCESS;
    }

    template<typename PROTOCOL_MSG_TYPE, typename RETURN_VALUE_TYPE>
    Status doEncode(const PROTOCOL_MSG_TYPE& msg, RETURN_VALUE_TYPE (*encodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE))
    {
        if (ASN1_OK != encodeFunction(&context, msg))
        {
            Asn1PrintErrorInfoList(context.errorInfo);
            return USI_FAILED;
        }
        return USI_SUCCESS;
    }

private:
	int initCtxtStatus;
	Asn1Ctxt context;
};

template <typename PROTOCOL_MSG_TYPE, typename RETURN_VALUE_TYPE>
Status encodeToBuffer( const PROTOCOL_MSG_TYPE& msg
                     , RETURN_VALUE_TYPE (*encodeFunction)(Asn1Ctxt*, PROTOCOL_MSG_TYPE*)
                     , CodecBuffer& encodeBuffer
                     , bool aligned = false)
{
   Encoder encoder(encodeBuffer.getStreamBuff(), encodeBuffer.getStreamBuffLen(), aligned);
   USI_ASSERT_SUCC_CALL(encoder.encode(msg, encodeFunction));
   encodeBuffer.setStreamLen(encoder.getMsgLen());

   return USI_SUCCESS;
}

#endif /* ENCODER_H_ */

