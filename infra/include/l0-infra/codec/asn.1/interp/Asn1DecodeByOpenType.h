/*
 * Asn1DecodeByOpenType.h
 *
 * Created on: Sep 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1DECODEBYOPENTYPE_H_
#define ASN1DECODEBYOPENTYPE_H_

#include "l0-infra/codec/asn.1/Asn1OpenType.h"
#include "l0-infra/codec/asn.1/Asn1PerDecoder.h"
#include "l0-infra/base/Assertions.h"

ASN1_NS_BEGIN

template <typename T, typename CODEC>
struct Asn1DecodeByOpenType
{
   static Status decode(Asn1DecodingContext& context, T& value)
   {
      ASN1_OpenType openType;
      USI_ASSERT_SUCC_CALL(context.getDecoder().decodeOpenType(openType));

      Asn1Stream localStream(openType);
      return CODEC::decode(localStream, value);
   }
};

ASN1_NS_END

#endif /* ASN1DECODEBYOPENTYPE_H_ */

