/*
 * Asn1DecodeSeqOf.h
 *
 * Created on: Sep 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1DECODESEQOF_H_
#define ASN1DECODESEQOF_H_

#include "l0-infra/codec/asn.1/Asn1Constraint.h"
#include "l0-infra/codec/asn.1/Asn1SeqOf.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/max_min.h"
#include "Asn1DefCommon.h"
#include "l0-infra/codec/asn.1/Asn1SimpleDecodeContext.h"

ASN1_NS_BEGIN

template <typename T, typename SINGLE_IE_CODEC>
struct Asn1DecodeSeqOf
{
    typedef Asn1SeqOf<T> ValueType;

   static Status decode(Asn1DecodingContext& context, const Asn1Constraint<U32>& cons, ValueType& value)
   {
      U32 n = 0;
      USI_ASSERT_SUCC_CALL(__ASN1_STREAM.decodeSeqOfN(cons, n));
      USI_ASSERT_SUCC_CALL(value.alloc(n, context.getCodecBuf()));

      for(U32 i=0; i<n; i++)
      {
         T* elem = value[i];
         USI_ASSERT_VALID_PTR(elem);
         USI_ASSERT_SUCC_CALL(SINGLE_IE_CODEC::decode(context, *elem));
      }

      return USI_SUCCESS;
   }
};

ASN1_NS_END

#endif /* ASN1DECODESEQOF_H_ */

