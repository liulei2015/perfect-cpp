/*
 * S1ApDefCommon.h
 *
 * Created on: Sep 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef S1APDEFCOMMON_H_
#define S1APDEFCOMMON_H_

#include "l0-infra/codec/ap/interp/ApPublicDef.h"
#include "l0-infra/codec/asn.1/interp/Asn1DefCommon.h"

#define S1AP_IE_ORDER(p_name) ____order_##p_name

#define __AP_CONTAINER_IE(p_type, p_name, p_criticality, p_mandatory)   \
    ProtoIeItem( S1AP_IE_ID(p_name)        \
    , (U8)p_criticality                    \
    , p_mandatory                          \
    , S1AP_CODEC(p_type)::decode           \
    , (void*)&(value.p_name)               \
    , value.p_name.getOffsetOfPresent()),

#define __AP_IES_DECODER_DECL(p_name)               \
struct ASN1_CODEC(p_name)                           \
{                                                   \
    static Status decode                            \
        ( ASN1_NS::Asn1DecodingContext& context     \
        , p_name& value                             \
        , AP_IES_DECODER decoder);                  \
};

#define ____AP_DECL_MSG(p_name, p_suffix)            \
    enum { sizeof_##p_suffix = sizeof(p_name) };     \
    static void* cons_####p_suffix(void* p)          \
    { return (void*) new(p) p_name; }                \
    typedef ASN1_CODEC(p_name) Codec##p_suffix;

#endif /* S1APDEFCOMMON_H_ */

