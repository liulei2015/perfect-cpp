
#include "l0-infra/codec/asn.1/interp/Asn1Undef.h"
#include "l0-infra/codec/asn.1/interp/Asn1DefCommon.h"
#include "l0-infra/base/Status.h"

///////////////////////////////////////////////////////////////////////////////
#define __OOO__

///////////////////////////////////////////////////////////////////////////////
/// alias
///////////////////////////////////////////////////////////////////////////////
#define __def_alias(p_name, p_type) __ASN1_DECODER_DECL(p_name)

///////////////////////////////////////////////////////////////////////////////
/// integer
///////////////////////////////////////////////////////////////////////////////
#define __def_u08_type(p_name, ...) __ASN1_DECODER_DECL(p_name)
#define __def_u16_type(p_name, ...) __ASN1_DECODER_DECL(p_name)
#define __def_u32_type(p_name, ...) __ASN1_DECODER_DECL(p_name)
#define __def_u64_type(p_name, ...) __ASN1_DECODER_DECL(p_name)

///////////////////////////////////////////////////////////////////////////////
/// enum
///////////////////////////////////////////////////////////////////////////////
#define __def_enum_begin(p_name)  __ASN1_DECODER_DECL(p_name)
#define __enum_l(p_name)
#define __def_enum_end()

///////////////////////////////////////////////////////////////////////////////
/// sequence
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_begin(p_name) __ASN1_DECODER_DECL(p_name)
#define __seq_m_ie(p_type, p_name)
#define __seq_o_ie(p_type, p_name)
#define __seq_e_ie(p_type, p_name)
#define __def_sequence_end()

///////////////////////////////////////////////////////////////////////////////
/// choice
///////////////////////////////////////////////////////////////////////////////
#define __def_choice_begin(p_name) __ASN1_DECODER_DECL(p_name)
#define __choice(p_name)
#define __def_choice_end()

///////////////////////////////////////////////////////////////////////////////
/// sequence of
///////////////////////////////////////////////////////////////////////////////
#define __def_sequence_of(p_name, p_type, ...) \
__ASN1_DECODER_DECL(p_name)

///////////////////////////////////////////////////////////////////////////////
/// bit string
///////////////////////////////////////////////////////////////////////////////
#define __def_bit_string(p_name, ...) __ASN1_DECODER_DECL(p_name)

///////////////////////////////////////////////////////////////////////////////
/// oct string
///////////////////////////////////////////////////////////////////////////////
#define __def_oct_string(p_name, ...) __ASN1_DECODER_DECL(p_name)

