/*
 * ProtoIeItem.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef INCL_USI_ProtoIeItem_20130929093657_H__
#define INCL_USI_ProtoIeItem_20130929093657_H__

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/codec/asn.1/Asn1OpenType.h"
#include "l0-infra/codec/asn.1/Asn1SimpleDecodeContext.h"

struct AP_ProtocolIE_Field;

struct ProtoIeItem
{
private:
   struct AnyType {};
   typedef Status (*IeDecoder)(ASN1_NS::Asn1DecodingContext&, AnyType&);

public:
   ProtoIeItem();

   template <typename T>
   ProtoIeItem
       ( ASN1_NS::U16 id
       , ASN1_NS::U8  criticality
       , bool         mandatory
       , Status       (*ieDecoder)(ASN1_NS::Asn1DecodingContext&, T&)
       , void*        object
       , size_t       offsetOfPresent)
       : ieDecoder(reinterpret_cast<IeDecoder>(ieDecoder))
       , object(reinterpret_cast<AnyType*>(object))
       , occurence(0)
	   , offsetOfPresent(offsetOfPresent)
       , id(id)
       , actualOrder(0xFFFF)
       , criticality(criticality)
       , mandatory(mandatory)
       , failed(false)
   {
   }

   bool matches(const ASN1_NS::U16 id) const;
   Status onRecv(ASN1_NS::Asn1DecodingContext&, ASN1_NS::U16 order, const AP_ProtocolIE_Field& field);
   Status sanityCheck(const ASN1_NS::U16 supposedOrder, ASN1_NS::Asn1DecodeListener&) const;
   bool isReceived() const;

   bool isValid() const;
   bool isMandatory() const;
   const ASN1_NS::U16 getActualOrder() const;

private:
    Status doSanityCheck(const ASN1_NS::U16 supposedOrder) const;
    Status decode(ASN1_NS::Asn1DecodingContext& ctxt, const ASN1_OpenType& openType);

private:
   IeDecoder               ieDecoder;
   AnyType*                object;
   ASN1_NS::U32            occurence;
   const size_t            offsetOfPresent;
   const ASN1_NS::U16      id;
   ASN1_NS::U16            actualOrder;
   const ASN1_NS::U8       criticality;
   const bool              mandatory;
   mutable bool            failed;
};

#endif /* PROTOIEITEM_H_ */

