#include "l0-infra/codec/asn.1/interp/Asn1Undef.h"
#include "l0-infra/codec/asn.1/interp/Asn1DefCommon.h"
#include "l0-infra/codec/asn.1/interp/Asn1DecodeSeqOf.h"
#include "l0-infra/codec/asn.1/interp/Asn1DecodeByOpenType.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/Asn1Constraint.h"

#include "l0-infra/base/Assertions.h"

///////////////////////////////////////////////////////////////////////////////
#define __OOO__

///////////////////////////////////////////////////////////////////////////////
/// alias
///////////////////////////////////////////////////////////////////////////////
#define __def_alias(p_name, p_type)                     \
__ASN1_DECODER_DEF(p_name)                              \
{                                                       \
    return ASN1_CODEC(p_type)::decode(context, value);  \
}

///////////////////////////////////////////////////////////////////////////////
/// integer
///////////////////////////////////////////////////////////////////////////////
#define __def_u08_type(p_name, ...)             \
__ASN1_INT_DECODER(U8, p_name, ##__VA_ARGS__)

#define __def_u16_type(p_name, ...)             \
__ASN1_INT_DECODER(U16, p_name, ##__VA_ARGS__)

#define __def_u32_type(p_name, ...)             \
__ASN1_INT_DECODER(U32, p_name, ##__VA_ARGS__)

#define __def_u64_type(p_name, ...)             \
__ASN1_INT_DECODER(U64, p_name, ##__VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////
/// enum
///////////////////////////////////////////////////////////////////////////////
#define __def_enum_begin(p_name)                     \
__ASN1_DECODER_DEF(p_name)                           \
__ENUM_DECODER_BODY(p_name)

#define __enum_l(p_name)
#define __def_enum_end()

///////////////////////////////////////////////////////////////////////////////
/// sequence
///////////////////////////////////////////////////////////////////////////////
#if 0
#define __def_sequence_begin(p_name)                        \
    __ASN1_DECODER_DEF(p_name)                              \
{                                                           \
    USI_ASSERT_SUCC_CALL(__ASN1_SEQ_PREAMBLE_HELPER(p_name)(context, value)); 

#define __seq_m_ie(p_type, p_name)                          \
    USI_ASSERT_SUCC_CALL(ASN1_CODEC(p_type)::decode         \
    (context, value.p_name));

#define __seq_o_ie(p_type, p_name)                          \
    if(value.p_name.isPresent())                            \
    {                                                       \
       USI_ASSERT_SUCC_CALL(ASN1_CODEC(p_type)::decode      \
            (context, value.p_name.getRef()));              \
    }

#define __seq_e_ie(p_type, p_name)                          \
    if(value.p_name.isPresent())                            \
    {                                                       \
        typedef Asn1DecodeByOpenType< p_type, ASN1_CODEC(p_type)> ExtDecoder;     \
        USI_ASSERT_SUCC_CALL(ExtDecoder::decode             \
            (context, value.p_name.getRef()));              \
    }

#define __def_sequence_end()                                \
    return USI_SUCCESS;                                     \
}

#else
#define __def_sequence_begin(p_name)                        \
__ASN1_DECODER_DEF(p_name)                                  \
{                                                           \
   typedef __ASN1_ENUM_HELPER(p_name) EnumHelper;           \
   const ASN1_NS::U8 numOfOpt = __EXT_ROOT_NUM(p_name);     \
   const ASN1_NS::U8 numOfExt = __EXT_LITERAL_NUM(p_name);  \
   const bool isExt = __ASN1_IS_EXT(p_name);                \
   ASN1_NS::Asn1BitString rootBitmap;                       \
   ASN1_NS::Asn1BitString extBitmap;                        \
   USI_ASSERT_SUCC_CALL(__ASN1_STREAM.decodeSeqPreamble     \
               ( numOfOpt                                   \
               , rootBitmap                                 \
               , isExt                                      \
               , numOfExt                                   \
               , extBitmap));                               \

#define __seq_m_ie(p_type, p_name)                          \
   USI_ASSERT_SUCC_CALL(ASN1_CODEC(p_type)::decode          \
                 (context, value.p_name));

#define __seq_o_ie(p_type, p_name)                          \
   if(rootBitmap.isSet(EnumHelper::__ENUM_INDEX(p_name)))   \
   {                                                        \
      value.p_name.forceEffective();                        \
      USI_ASSERT_SUCC_CALL(ASN1_CODEC(p_type)::decode       \
          (context, value.p_name.getRef()));                \
   }

#define __seq_e_ie(p_type, p_name)                          \
   if(extBitmap.isSet(EnumHelper::__ENUM_INDEX(p_name)))    \
   {                                                        \
      value.p_name.forceEffective();                        \
      typedef Asn1DecodeByOpenType< p_type, ASN1_CODEC(p_type)> ExtDecoder;     \
      USI_ASSERT_SUCC_CALL(ExtDecoder::decode               \
            (context, value.p_name.getRef()));              \
   }

#define __def_sequence_end()                                \
   return USI_SUCCESS;                                      \
}

#endif

///////////////////////////////////////////////////////////////////////////////
/// choice
///////////////////////////////////////////////////////////////////////////////
#define __def_choice_begin(p_name)                                   \
namespace {                                                          \
   Status p_name##getChoice(ASN1_NS::Asn1DecodingContext& context, U16& value) \
   __ENUM_DECODER_BODY(p_name)                                       \
}                                                                    \
__ASN1_DECODER_DEF(p_name)                                           \
{                                                                    \
   typedef __ASN1_ENUM_HELPER(p_name) EnumHelper;                    \
   USI_ASSERT_SUCC_CALL(p_name##getChoice(context, value.choice));   \
   switch(value.choice) {

#define __choice(p_name)                                             \
      case EnumHelper::__ENUM_INDEX(p_name) :                        \
          new (value.u.__ASN1_MEMBER(p_name).alloc()) p_name;        \
          USI_ASSERT_SUCC_CALL(ASN1_CODEC(p_name)::decode            \
               (context, value.u.__ASN1_MEMBER(p_name).getRef()));   \
          break;

#define __def_choice_end()                                           \
      default: return ASN1_E_SYNTAX_T;                               \
   }                                                                 \
   return USI_SUCCESS;                                               \
}

///////////////////////////////////////////////////////////////////////////////
/// sequence of
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_of(p_name, p_type, ...)                              \
__ASN1_DECODER_DEF(p_name)                                                  \
{                                                                           \
   ASN1_NS::Asn1Constraint<ASN1_NS::U32> cons(false, ##__VA_ARGS__);        \
   typedef Asn1DecodeSeqOf<p_type, ASN1_CODEC(p_type)> Codec;               \
   USI_ASSERT_SUCC_CALL(Codec::decode(context, cons, value));               \
   return USI_SUCCESS;                                                      \
}

///////////////////////////////////////////////////////////////////////////////
/// bit string
///////////////////////////////////////////////////////////////////////////////
#define __def_bit_string(p_name, ...)                                       \
__ASN1_DECODER_DEF(p_name)                                                  \
{                                                                           \
    ASN1_NS::Asn1Constraint<ASN1_NS::U32> cons(false, ##__VA_ARGS__);       \
    return __ASN1_STREAM.decodeConsBitString(cons, value);                  \
}

///////////////////////////////////////////////////////////////////////////////
/// oct string
///////////////////////////////////////////////////////////////////////////////
#define __def_oct_string(p_name, ...)                                       \
__ASN1_DECODER_DEF(p_name)                                                  \
{                                                                           \
    ASN1_NS::Asn1Constraint<ASN1_NS::U32> cons(false, ##__VA_ARGS__);       \
    return __ASN1_STREAM.decodeConsOctString(cons, value);                  \
}

