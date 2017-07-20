
#include "l0-infra/codec/asn.1/interp/Asn1CodecDefInterp.h"

#include "l0-infra/codec/ap/interp/ApUndef.h"
#include "l0-infra/codec/ap/ProtoIeItem.h"
#include "l0-infra/codec/ap/ProtocolIesDecoder.h"

/////////////////////////////////////////////////////////////////
/// protocol ies
/////////////////////////////////////////////////////////////////
#define __ap_proto_ies_begin(p_name)                             \
Status ASN1_CODEC(p_name)::decode                                \
    ( ASN1_NS::Asn1DecodingContext& context                      \
    , p_name& value                                              \
    , AP_IES_DECODER decoder)                                    \
{                                                                \
   ProtoIeItem ies[] = {

#define __ap_proto_m_ie(p_type, p_name, p_criticality)           \
    __AP_CONTAINER_IE(p_type, p_name, p_criticality, true) 

#define __ap_proto_o_ie(p_type, p_name, p_criticality)           \
    __AP_CONTAINER_IE(p_type, p_name, p_criticality, false) 

//
// placing a null object here, only for eliminating the compiling
// error in case of null container. it's not counted in num_of_root_ies.
#define __ap_proto_ies_end()                                      \
            ProtoIeItem()                                         \
   };                                                             \
                                                                  \
   return decoder(context, ies, sizeof(ies)/sizeof(ies[0]) - 1);  \
}

/////////////////////////////////////////////////////////////////
/// protocol ie container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ie_single_container(p_name, p_ies)   \
__ASN1_DECODER_DEF(p_name)                                  \
{                                                           \
    return ASN1_CODEC(p_ies)::decode                        \
                  ( context                                 \
                  , value                                   \
                  , AP_single_container_decode);            \
}

#define __def_ap_proto_ie_container(p_name, p_ies)          \
__ASN1_DECODER_DEF(p_name)                                  \
{                                                           \
    return ASN1_CODEC(p_ies)::decode                        \
                ( context                                   \
                , value                                     \
                , AP_container_decode);                     \
}

/////////////////////////////////////////////////////////////////
/// protocol ext ies
/////////////////////////////////////////////////////////////////
#define __ap_proto_ext_begin(p_name) __ap_proto_ies_begin(p_name)
#define __ap_proto_ext_end() __ap_proto_ies_end()

/////////////////////////////////////////////////////////////////
/// protocol ext container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ext_container(p_name, p_ies)         \
__ASN1_DECODER_DEF(p_name)                                  \
{                                                           \
    return ASN1_CODEC(p_ies)::decode                        \
                ( context                                   \
                , value                                     \
                , AP_ext_container_decode);                 \
}

