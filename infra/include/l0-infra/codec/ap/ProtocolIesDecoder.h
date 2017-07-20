#ifndef INCL_USI_ProtocolIesDecoder_2013109205757_H__
#define INCL_USI_ProtocolIesDecoder_2013109205757_H__

#include "l0-infra/base/Status.h"
#include "l0-infra/codec/asn.1/Asn1DecodingContext.h"
#include "l0-infra/codec/ap/ProtoIeItem.h"

typedef Status (*AP_IES_DECODER)(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num);

Status AP_ext_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num);
Status AP_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num);
Status AP_single_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num);

#endif

