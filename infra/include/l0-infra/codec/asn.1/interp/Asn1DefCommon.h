/*
 * Asn1DefCommon.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1DEFCOMMON_H_
#define ASN1DEFCOMMON_H_

#include "l0-infra/codec/asn.1/asn1.h"
#include "l0-infra/codec/asn.1/interp/Asn1PublicDef.h"
#include "l0-infra/codec/asn.1/interp/Asn1ExtendabilityTraits.h"
#include "l0-infra/codec/asn.1/interp/Asn1ExtRootNumberTraits.h"
#include "l0-infra/codec/asn.1/Asn1DecodingContext.h"

ASN1_NS_BEGIN

struct ASN1_OpenType;

struct Asn1Stream
{
    Asn1Stream(ASN1_OpenType& type)
    {

    }
};


///////////////////////////////////////////////////////////////////
#define __ASN1_MEMBER(p_name) m_##p_name

///////////////////////////////////////////////////////////////////
#define __ASN1_EXT_MARKER_NAME(p_name) ____##p_name##_ExtMarker
#define __ASN1_IS_EXT(p_name)  Asn1ExtendabilityTraits<__ASN1_EXT_MARKER_NAME(p_name)>::extendable

#define __DEF_EXT_MARKER_BEGIN(p_name)   \
struct  __ASN1_EXT_MARKER_NAME(p_name)   \
{

#define __DEF_EXT_MARKER_END()           \
};

///////////////////////////////////////////////////////////////////
#define __ASN1_DECODER_DECL(p_name)                               \
struct ASN1_CODEC(p_name)                                         \
{                                                                 \
   static Status decode(ASN1_NS::Asn1DecodingContext&, p_name&);  \
};

#define __ASN1_DECODER_DEF(p_name)                                             \
Status ASN1_CODEC(p_name)::decode(ASN1_NS::Asn1DecodingContext& context, p_name& value)  \


#define __ASN1_STREAM context.getDecoder()
///////////////////////////////////////////////////////////////////
#define __ASN1_INT_DECODER(p_type, p_name, ...)                              \
__ASN1_DECODER_DEF(p_name)                                                   \
{                                                                            \
   ASN1_NS::Asn1Constraint<ASN1_NS::p_type> cons(false, ##__VA_ARGS__);      \
   return __ASN1_STREAM.decodeInt(cons, (p_type&)value);                     \
}

////////////////////////////////////////////////////////////////////
#define __ASN1_ENUM_HELPER(p_name) ____##p_name##_Enum

#define __EXT_ROOT_NUM(p_name) Asn1ExtRootNumberTraits<__ASN1_ENUM_HELPER(p_name), __ASN1_IS_EXT(p_name)>::ext_root_number
#define __LITERAL_NUM(p_name) __ASN1_ENUM_HELPER(p_name)::__enum_literal_num
#define __EXT_LITERAL_NUM(p_name) Asn1ExtRootNumberTraits<__ASN1_ENUM_HELPER(p_name), __ASN1_IS_EXT(p_name)>::ext_number

#define __ENUM_INDEX(p_name) ____##p_name##_index

#define __DEF_ENUM_HELPER_BEGIN(p_name) \
struct __ASN1_ENUM_HELPER(p_name) \
{                                 \
    enum                          \
    {

#define __DEF_ENUM_HELPER_END()   \
       __enum_literal_num         \
    } value;                      \
};

#define __ENUM_DECODER_BODY(p_name)                  \
{                                                    \
   return __ASN1_STREAM.decodeEnum                   \
          ( (const U32) __LITERAL_NUM(p_name)        \
          , value                                    \
          , __ASN1_IS_EXT(p_name)                    \
          , (const U32) __EXT_ROOT_NUM(p_name));     \
}

////////////////////////////////////////////////////////////////////
#define __ASN1_CHOICE_HELPER_NAME(p_name) ____##p_name##_Choice

#define __ASN1_SEQ_PREAMBLE_HELPER(p_name) ____decode_##p_name##_preamble
ASN1_NS_END

#endif /* ASN1DEFCOMMON_H_ */

