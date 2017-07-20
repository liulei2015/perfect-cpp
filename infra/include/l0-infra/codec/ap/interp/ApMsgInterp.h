
#include "l0-infra/codec/asn.1/interp/Asn1MsgInterp.h"
#include "l0-infra/codec/asn.1/Asn1OptionalIe.h"
#include "l0-infra/codec/ap/interp/ApUndef.h"

/////////////////////////////////////////////////////////////////
/// protocol ie ies
/////////////////////////////////////////////////////////////////
#define __ap_proto_ies_begin(p_name)               \
struct p_name {

#define __ap_proto_m_ie(p_type, p_name, p_criticality) ASN1_NS::Asn1OptionalIe<p_type> p_name;
#define __ap_proto_o_ie(p_type, p_name, p_criticality) ASN1_NS::Asn1OptionalIe<p_type> p_name;

#define __ap_proto_ies_end() };

/////////////////////////////////////////////////////////////////
/// protocol ie container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ie_single_container(p_name, p_ies)    \
    typedef p_ies p_name;

#define __def_ap_proto_ie_container(p_name, p_ies)           \
    typedef p_ies p_name;

/////////////////////////////////////////////////////////////////
/// protocol ext ies
/////////////////////////////////////////////////////////////////
#define __ap_proto_ext_begin(p_name)               \
struct p_name {

#define __ap_proto_ext_end() };

/////////////////////////////////////////////////////////////////
/// protocol ext container
/////////////////////////////////////////////////////////////////
#define __def_ap_proto_ext_container(p_name, p_ies)   \
    typedef p_ies p_name;

/////////////////////////////////////////////////////////////////
/// elementary procedure
/////////////////////////////////////////////////////////////////
#define __ap_elementary_procedure_begin(p_name) \
struct p_name##_ElementaryProcedure              \
{

#define __ep_initiating_msg(p_name)       ____AP_DECL_MSG(p_name, InitiatingMsg)
#define __ep_successful_outcome(p_name)   ____AP_DECL_MSG(p_name, SuccessfulOutcome)
#define __ep_unsuccessful_outcome(p_name) ____AP_DECL_MSG(p_name, UnsuccessfulOutcome)
#define __ep_procedure_code(p_code)       static const AP_ProcedureCode procedureCode = p_code;
#define __ep_criticality(p_criticality)   static const AP_Criticality criticality = p_criticality;

#define __ap_elementary_procedure_end() \
};

