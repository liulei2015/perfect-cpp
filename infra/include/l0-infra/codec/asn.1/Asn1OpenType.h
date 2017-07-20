/*
 * Asn1OpenType.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1OPENTYPE_H_
#define ASN1OPENTYPE_H_

#include "l0-infra/codec/asn.1/Asn1OctString.h"
#include "l0-infra/codec/asn.1/Asn1SimpleDecodeContext.h"

ASN1_NS_BEGIN

struct ASN1_OpenType : Asn1OctString
{
    template <typename T>
    Status decode(ASN1_NS::Asn1DecodingContext& ctxt, Status (*decoder)(ASN1_NS::Asn1DecodingContext&, T&), T& obj) const
    {
        ASN1_NS::Asn1SimpleDecodeContext context(*getSegment(), ctxt.getCodecBuf(), ctxt.getListener());

        return decoder(context, obj);
    }

};

ASN1_NS_END

#endif /* ASN1OPENTYPE_H_ */

