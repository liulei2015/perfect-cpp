#ifndef INCL_USI_Asn1DecodeListener_20130929190152_H__
#define INCL_USI_Asn1DecodeListener_20130929190152_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/Asn1Types.h"

ASN1_NS_BEGIN

DEFINE_ROLE(Asn1DecodeListener)
{
    DEFAULT(void, onTransSyntaxError(const Status cause));
    DEFAULT(void, onAbstractSyntaxError(const U16 ieId, const U8 criticality, const Status cause, bool isExt));
};

ASN1_NS_END

#endif

