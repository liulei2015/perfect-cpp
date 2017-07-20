/*
 * ProtoIeItem.cpp
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/codec/ap/ProtoIeItem.h"
#include "l0-infra/codec/asn.1/Asn1OpenType.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/codec/asn.1/Asn1SimpleDecodeContext.h"
#include "l0-infra/codec/asn.1/Asn1PerDecoder.h"
#include "l0-infra/codec/ap/local/ApContainerDefs_L.h"

#include <stdio.h>

////////////////////////////////////////////////
ProtoIeItem::ProtoIeItem()
    : ieDecoder(0)
    , object(0)
    , occurence(0)
	, offsetOfPresent(0)
    , id(0)
    , actualOrder(0xFFFF)
    , criticality(0)
    , mandatory(false)
    , failed(false)
{
}

////////////////////////////////////////////////
bool ProtoIeItem::matches(const ASN1_NS::U16 id) const
{
   return id == this->id;
}

////////////////////////////////////////////////
Status ProtoIeItem::onRecv(ASN1_NS::Asn1DecodingContext& context, ASN1_NS::U16 order, const AP_ProtocolIE_Field& field)
{
   occurence++;

   if(occurence == 1)
   {
      actualOrder = order;
      USI_ASSERT_SUCC_CALL(decode(context, field.value));
   }

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
bool ProtoIeItem::isReceived() const
{
    return occurence > 0;
}

///////////////////////////////////////////////////////////////////////////////
Status ProtoIeItem::doSanityCheck(const ASN1_NS::U16 supposedOrder) const
{
    if(occurence > 1)
    {
        DBG_LOG("id=%d occured too many times: %d\n", id, occurence); 
        return ASN1_E_OCCURENCE;
    }
    else if(occurence == 0)
    {
        if(mandatory)
        {
            DBG_LOG("missing ie: id=%d\n", id); 
        }

        return mandatory ? ASN1_E_MISSING_IE : USI_SUCCESS;
    }

    if(actualOrder < supposedOrder)
    {
        DBG_LOG("id=%d, supposed Order=%d, actual order=%d\n", id, supposedOrder, actualOrder); 
        return ASN1_E_WRONG_ORDER;
    }

    return USI_SUCCESS;
}

////////////////////////////////////////////////
Status ProtoIeItem::sanityCheck(const ASN1_NS::U16 supposedOrder, ASN1_NS::Asn1DecodeListener& listener) const
{
    Status status = doSanityCheck(supposedOrder);
    
    if(status == USI_SUCCESS)
    {
        return status;
    }

    listener.onAbstractSyntaxError(id, criticality, status, false);
    if(status == ASN1_E_OCCURENCE || status == ASN1_E_WRONG_ORDER)
    {
        return status;
    }

    failed = true;

    return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////
Status ProtoIeItem::decode(ASN1_NS::Asn1DecodingContext& ctxt, const ASN1_OpenType& openType)
{
   USI_ASSERT_VALID_PTR(object);
   USI_ASSERT_VALID_PTR(ieDecoder);

   if(occurence > 0)
   {
      // force effective
       *(bool*)(((Oct*)object) + offsetOfPresent) = true;

       USI_ASSERT_SUCC_CALL(openType.decode(ctxt, ieDecoder, *(AnyType*)object));
   }

   return USI_SUCCESS;
}

const ASN1_NS::U16 ProtoIeItem::getActualOrder() const
{
    return actualOrder;
}

////////////////////////////////////////////////////////////////////
bool ProtoIeItem::isMandatory() const
{
    return mandatory;
}
