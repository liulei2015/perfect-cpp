/*
 * Asn1BitString.h
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1BITSTRING_H_
#define ASN1BITSTRING_H_

#include "l0-infra/codec/asn.1/Asn1Component.h"

ASN1_NS_BEGIN

struct Asn1BitString : Asn1GenericComponent<1>
{
   bool isSet(U32 bit) const;
};

ASN1_NS_END

#endif /* ASN1BITSTRING_H_ */

