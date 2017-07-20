/*
 * Asn1OctString.h
 *
 * Created on: Oct 2, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1OCTSTRING_H_
#define ASN1OCTSTRING_H_

#include "l0-infra/codec/asn.1/Asn1Component.h"

ASN1_NS_BEGIN

struct Asn1OctString : Asn1GenericComponent<8>
{
    Oct operator[](U32) const;
};

ASN1_NS_END

#endif /* ASN1OCTSTRING_H_ */

