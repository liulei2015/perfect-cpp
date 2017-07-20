

#include "l0-infra/codec/asn.1/interp/Asn1Undef.h"
#include "l0-infra/codec/asn.1/Asn1Types.h"


///////////////////////////////////////////////////////////////////////////////
#define __OOO__

///////////////////////////////////////////////////////////////////////////////
/// alias
///////////////////////////////////////////////////////////////////////////////
#define __def_alias(p_name, p_type)

///////////////////////////////////////////////////////////////////////////////
/// integer
///////////////////////////////////////////////////////////////////////////////
#define __def_u08_type(p_name, ...)
#define __def_u16_type(p_name, ...)
#define __def_u32_type(p_name, ...)
#define __def_u64_type(p_name, ...)

///////////////////////////////////////////////////////////////////////////////
/// enum
///////////////////////////////////////////////////////////////////////////////
#define __def_enum_begin(p_name)
#define __enum_l(p_name)
#define __def_enum_end()

///////////////////////////////////////////////////////////////////////////////
/// sequence
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_begin(p_name)
#define __seq_m_ie(p_type, p_name)
#define __seq_o_ie(p_type, p_name)
#define __seq_e_ie(p_type, p_name)
#define __def_sequence_end()

///////////////////////////////////////////////////////////////////////////////
/// choice
///////////////////////////////////////////////////////////////////////////////
#define __def_choice_begin(p_name) \
struct __ASN1_CHOICE_HELPER_NAME(p_name) : p_name {        \
private:                                                   \
   typedef p_name ParentChoice;                            \
   typedef __ASN1_ENUM_HELPER(p_name) EnumHelper;          \
public:

#define __choice(p_name)                                   \
   bool __IS_CHOSEN(p_name) const                          \
   { return choice == EnumHelper::__ENUM_INDEX(p_name) ; } \
   p_name& __CHOICE(p_name)                                \
   { return u.__ASN1_MEMBER(p_name).getRef(); }            \

#define __def_choice_end()         };

///////////////////////////////////////////////////////////////////////////////
/// sequence of
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_of(p_name, p_type, ...)

///////////////////////////////////////////////////////////////////////////////
/// bit string
///////////////////////////////////////////////////////////////////////////////
#define __def_bit_string(p_name, ...) 

///////////////////////////////////////////////////////////////////////////////
/// oct string
///////////////////////////////////////////////////////////////////////////////
#define __def_oct_string(p_name, ...) 
