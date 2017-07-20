
#include "l0-infra/codec/asn.1/interp/Asn1Undef.h"
#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/codec/asn.1/Asn1BitString.h"
#include "l0-infra/codec/asn.1/Asn1OctString.h"
#include "l0-infra/codec/asn.1/Asn1OptionalIe.h"
#include "l0-infra/codec/asn.1/Asn1SeqOf.h"
#include "l0-infra/base/Placement.h"


///////////////////////////////////////////////////////////////////////////////
#define __OOO__

///////////////////////////////////////////////////////////////////////////////
/// alias
///////////////////////////////////////////////////////////////////////////////
#define __def_alias(p_name, p_type) typedef p_type p_name;

///////////////////////////////////////////////////////////////////////////////
/// integer
///////////////////////////////////////////////////////////////////////////////
#define __def_u08_type(p_name, ...) typedef ASN1_NS::U8  p_name;
#define __def_u16_type(p_name, ...) typedef ASN1_NS::U16 p_name;
#define __def_u32_type(p_name, ...) typedef ASN1_NS::U32 p_name;
#define __def_u64_type(p_name, ...) typedef ASN1_NS::U64 p_name;

///////////////////////////////////////////////////////////////////////////////
/// enum
///////////////////////////////////////////////////////////////////////////////
#define __def_enum_begin(p_name) enum p_name {
#define __enum_l(p_name)            p_name,
#define __def_enum_end()         };

///////////////////////////////////////////////////////////////////////////////
/// sequence
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_begin(p_name) struct p_name {
#define __seq_m_ie(p_type, p_name)         p_type p_name;
#define __seq_o_ie(p_type, p_name)         Asn1OptionalIe<p_type> p_name;
#define __seq_e_ie(p_type, p_name)         __seq_o_ie(p_type, p_name)
#define __def_sequence_end()         };

///////////////////////////////////////////////////////////////////////////////
/// choice
///////////////////////////////////////////////////////////////////////////////
#define __def_choice_begin(p_name)                   \
struct __ASN1_CHOICE_HELPER_NAME(p_name);            \
struct p_name {                                      \
   typedef __ASN1_CHOICE_HELPER_NAME(p_name) Helper; \
   Helper& h()                                       \
   {                                                 \
      return (Helper&)*this;                         \
   }                                                 \
                                                     \
   ASN1_NS::U16 choice;                              \
   union {

#define __choice(p_name)  Placement<p_name> __ASN1_MEMBER(p_name);

#define __def_choice_end()         \
   } u;                            \
};

///////////////////////////////////////////////////////////////////////////////
/// sequence of
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_of(p_name, p_type, ...) \
    typedef ASN1_NS::Asn1SeqOf<p_type> p_name;

///////////////////////////////////////////////////////////////////////////////
/// bit string
///////////////////////////////////////////////////////////////////////////////
#define __def_bit_string(p_name, ...) typedef ASN1_NS::Asn1BitString  p_name;

///////////////////////////////////////////////////////////////////////////////
/// oct string
///////////////////////////////////////////////////////////////////////////////
#define __def_oct_string(p_name, ...) typedef ASN1_NS::Asn1OctString  p_name;

