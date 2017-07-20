

#include "l0-infra/codec/asn.1/interp/Asn1CodecDeclInterp.h"

#include "l0-infra/codec/ap/interp/ApDefCommon.h"
#include "l0-infra/codec/ap/ProtocolIesDecoder.h"

#include "l0-infra/codec/ap/interp/ApUndef.h"

/////////////////////////////////////////////////////////////////
/// protocol ie container
/////////////////////////////////////////////////////////////////
#define __ap_proto_ies_begin(p_name) __AP_IES_DECODER_DECL(p_name)

#define __ap_proto_m_ie(p_type, p_name, p_criticality)
#define __ap_proto_o_ie(p_type, p_name, p_criticality)

#define __ap_proto_ies_end()

/////////////////////////////////////////////////////////////////
/// protocol ies container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ie_single_container(p_name, p_ies)     \
    __ASN1_DECODER_DECL(p_name)

#define __def_ap_proto_ie_container(p_name, p_ies)     \
    __ASN1_DECODER_DECL(p_name)

/////////////////////////////////////////////////////////////////
/// protocol ext ies
/////////////////////////////////////////////////////////////////
#define __ap_proto_ext_begin(p_name) __AP_IES_DECODER_DECL(p_name)
#define __ap_proto_ext_end()


/////////////////////////////////////////////////////////////////
/// protocol ext container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ext_container(p_name, p_ies) \
    __ASN1_DECODER_DECL(p_name)


