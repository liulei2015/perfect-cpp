
/**************************************************************
--
-- Container for Protocol IEs
--
**************************************************************/
__def_sequence_begin(AP_ProtocolIE_Field)
   __seq_m_ie(AP_ProtocolIE_ID, protocolIE_ID)
   __seq_m_ie(AP_Criticality,   criticality)
   __seq_m_ie(ASN1_OpenType,     value)
__def_sequence_end()

__def_sequence_of(AP_ProtocolIE_Container, AP_ProtocolIE_Field, ___(0, maxProtocolIEs))
__def_alias(AP_ProtocolIE_SingleContainer, AP_ProtocolIE_Field);

