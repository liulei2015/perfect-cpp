
////////////////////////////////////////////////////////////////////////////
__ap_proto_ext_begin(Ap_NilExtIes)
__ap_proto_ext_end()

//////////////////////////////////////////////////////////////////////////
__def_ap_proto_ext_container(Ap_NilExtContainer, Ap_NilExtIes)

//////////////////////////////////////////////////////////////////////////
__def_u32_type(S1AP_MME_UE_S1AP_ID)
__def_u32_type(S1AP_ENB_UE_S1AP_ID, ___(0, 0xFFFFFF))
__def_u08_type(S1AP_E_RAB_ID,       ___(0, 15, __ooo__))
__def_u08_type(QCI,                 ___(0, 255))
__def_u08_type(PriorityLevel,       ___(0, 15))
__def_u64_type(BitRate,             ___(0, 1000000000))

////////////////////////////////////////////////////////////////////////////
__def_bit_string(CellId, __fixed(28))
__def_bit_string(EncryptionAlgorithms, __fixed(16, __ooo__))
__def_bit_string(IntegrityProtectionAlgorithms, __fixed(16, __ooo__))

__def_bit_string(TransportLayerAddress, ___(1, 160, __ooo__))

__def_bit_string(MacroENB_ID, __fixed(20))
__def_bit_string(HomeENB_ID,  __fixed(28))

////////////////////////////////////////////////////////////////////////////
__def_oct_string(PLMNidentity, __fixed(3))
__def_oct_string(GTP_TEID,     __fixed(4))

////////////////////////////////////////////////////////////////////////////
__def_choice_begin(EnbId)
  __choice(MacroENB_ID)
  __choice(HomeENB_ID)
  __OOO__
__def_choice_end()

////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(Global_ENB_ID)
  __seq_m_ie(PLMNidentity,        plmnId)
  __seq_m_ie(EnbId,               enbId)
  __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
  __OOO__
__def_sequence_end()


////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CauseRadioNetwork)
    __enum_l(S1AP_unspecified_2)                                 // 0             
    __enum_l(S1AP_tx2relocoverall_expiry)                        // 1    
    __enum_l(S1AP_successful_handover)                           // 2
    __enum_l(S1AP_release_due_to_eutran_generated_reason)        // 3
    __enum_l(S1AP_handover_cancelled)                            // 4
    __enum_l(S1AP_partial_handover)                              // 5
    __enum_l(S1AP_ho_failure_in_target_EPC_eNB_or_target_system) // 6
    __enum_l(S1AP_ho_target_not_allowed)                         // 7
    __enum_l(S1AP_tS1relocoverall_expiry)                        // 8
    __enum_l(S1AP_tS1relocprep_expiry)                           // 9
    __enum_l(S1AP_cell_not_available)                            // 10
    __enum_l(S1AP_unknown_targetID)                              // 11 
    __enum_l(S1AP_no_radio_resources_available_in_target_cell)   // 12
    __enum_l(S1AP_unknown_mme_ue_s1ap_id)                        // 13 error ind cause
    __enum_l(S1AP_unknown_enb_ue_s1ap_id)                        // 14 error ind cause
    __enum_l(S1AP_unknown_pair_ue_s1ap_id)                       // 15 error ind cause
    __enum_l(S1AP_handover_desirable_for_radio_reason)           // 16
    __enum_l(S1AP_time_critical_handover)                        // 17
    __enum_l(S1AP_resource_optimisation_handover)                // 18
    __enum_l(S1AP_reduce_load_in_serving_cell)                   // 19
    __enum_l(S1AP_user_inactivity)                               // 20
    __enum_l(S1AP_radio_connection_with_ue_lost)                 // 21
    __enum_l(S1AP_load_balancing_tau_required)                   // 22
    __enum_l(S1AP_cs_fallback_triggered)                         // 23
    __enum_l(S1AP_ue_not_available_for_ps_service)               // 24
    __enum_l(S1AP_radio_resources_not_available)                 // 25
    __enum_l(S1AP_failure_in_radio_interface_procedure)          // 26
    __enum_l(S1AP_invalid_qos_combination)                       // 27
    __enum_l(S1AP_interrat_redirection)                          // 28
    __enum_l(S1AP_interaction_with_other_procedure)              // 29
    __enum_l(S1AP_unknown_E_RAB_ID)                              // 30
    __enum_l(S1AP_multiple_E_RAB_ID_instances)                   // 31
    __enum_l(S1AP_encryption_and_or_integrity_protection_algorithms_not_supported)  // 32
    __enum_l(S1AP_s1_intra_system_handover_triggered)            // 33
    __enum_l(S1AP_s1_inter_system_handover_triggered)            // 34
    __enum_l(S1AP_x2_handover_triggered)                         // 35
    
    __OOO__

    __enum_l(S1AP_redirection_towards_1xRTT)                     // 36
    __enum_l(S1AP_not_supported_QCI_value)                       // 37
    __enum_l(S1AP_invalid_CSG_Id)                                // 38
__def_enum_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CauseTransport)
    __enum_l(S1AP_transport_resource_unavailable)
    __enum_l(S1AP_unspecified_3)
    __OOO__
__def_enum_end()
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CauseNas)
    __enum_l(S1AP_normal_release)
    __enum_l(S1AP_authentication_failure)
    __enum_l(S1AP_detach)
    __enum_l(S1AP_unspecified_4)
    __OOO__
    __enum_l(S1AP_csg_subscription_expiry)
__def_enum_end()
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CauseProtocol)
    __enum_l(S1AP_transfer_syntax_error)                              // 0 error ind cause
    __enum_l(S1AP_abstract_syntax_error_reject)                       // 1 error ind cause
    __enum_l(S1AP_abstract_syntax_error_ignore_and_notify)            // 2 error ind cause
    __enum_l(S1AP_message_not_compatible_with_receiver_state)         // 3 error ind cause
    __enum_l(S1AP_semantic_error)                                     // 4 error ind cause
    __enum_l(S1AP_abstract_syntax_error_falsely_constructed_message)  // 5 error ind cause
    __enum_l(S1AP_unspecified_1)
    __OOO__
__def_enum_end()
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CauseMisc)
    __enum_l(S1AP_control_processing_overload)
    __enum_l(S1AP_not_enough_user_plane_processing_resources)
    __enum_l(S1AP_hardware_failure)
    __enum_l(S1AP_om_intervention)
    __enum_l(S1AP_unspecified)
    __enum_l(S1AP_unknown_PLMN)
    __OOO__
__def_enum_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_choice_begin(S1AP_Cause)
  __choice(S1AP_CauseRadioNetwork)
  __choice(S1AP_CauseTransport)
  __choice(S1AP_CauseNas)
  __choice(S1AP_CauseProtocol)
  __choice(S1AP_CauseMisc)
  __OOO__
__def_choice_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_DL_Forwarding)
    __enum_l(S1AP_dL_Forwarding_proposed)
    __OOO__
__def_enum_end()
////////////////////////////////////////////////////////////////////////////

__def_sequence_begin(S1AP_E_RABInformationListItem)
    __seq_m_ie(S1AP_E_RAB_ID,      erabId)
    __seq_o_ie(S1AP_DL_Forwarding, dlForwarding)
    __seq_o_ie(S1AP_Cause,         cause)
    __OOO__
__def_sequence_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_CriticalityDiagnostics)
    __seq_o_ie(AP_ProcedureCode,      procedureCode)
    __seq_o_ie(AP_TriggeringMessage,  triggeringMessage)
    __seq_o_ie(AP_Criticality,        procedureCriticality)
    __seq_o_ie(Ap_NilExtContainer,    iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_oct_string(S1AP_NASSecurityParametersfromE_UTRAN)
__def_oct_string(S1AP_Target_ToSource_TransparentContainer)
__def_oct_string(NAS_PDU)

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_InitialContextSetupFailureMsg)
    __ap_proto_m_ie(S1AP_MME_UE_S1AP_ID,         mME_UE_S1AP_ID,         AP_ignore)
    __ap_proto_m_ie(S1AP_ENB_UE_S1AP_ID,         eNB_UE_S1AP_ID,         AP_ignore)
    __ap_proto_m_ie(S1AP_Cause,                  cause,                  AP_ignore)
    __ap_proto_o_ie(S1AP_CriticalityDiagnostics, criticalityDiagnostics, AP_ignore)
__ap_proto_ies_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_E_RABDataForwardingItem)
    __seq_m_ie(S1AP_E_RAB_ID,           erabId)
    __seq_o_ie(TransportLayerAddress,   dlTransportLayerAddress)
    __seq_o_ie(GTP_TEID,                dlGtpTeid)
    __seq_o_ie(TransportLayerAddress,   ulTransportLayerAddress)
    __seq_o_ie(GTP_TEID,                ulGtpTeid)
    __seq_o_ie(Ap_NilExtContainer,      iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_E_RABDataForwardingItemIes)
    __ap_proto_m_ie(S1AP_E_RABDataForwardingItem,    e_RABDataForwardingItem,         AP_ignore)
__ap_proto_ies_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_ap_proto_ie_single_container(S1AP_E_RABDataForwardingItemContainer, S1AP_E_RABDataForwardingItemIes)

__def_sequence_of( S1AP_E_RABSubjecttoDataForwardingList \
                 , S1AP_E_RABDataForwardingItemContainer \
                 , ___(1, maxNrOfE_RABs))

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_E_RABItem)
    __seq_m_ie(S1AP_E_RAB_ID,       erabId)
    __seq_o_ie(S1AP_Cause,          cause)
    __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_E_RABItemIes)
    __ap_proto_m_ie(S1AP_E_RABItem,    e_RABItem,         AP_ignore)
__ap_proto_ies_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_ap_proto_ie_single_container(S1AP_E_RABItemContainer, S1AP_E_RABItemIes)

__def_sequence_of( S1AP_E_RABList \
                 , S1AP_E_RABItemContainer \
                 , ___(1, maxNrOfE_RABs))

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_PreemptionCapability)
    __enum_l(s1ap_shall_not_trigger_preemption)
    __enum_l(s1ap_may_trigger_preemption)
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_PreemptionVulnerability)
    __enum_l(s1ap_not_preemptable)
    __enum_l(s1ap_preemptable)
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_AllocationAndRetentionPriority)
    __seq_m_ie(PriorityLevel,                      priorityLevel)
    __seq_m_ie(S1AP_PreemptionCapability,          preemptionCapability)
    __seq_m_ie(S1AP_PreemptionVulnerability,       preemptionVulnerability)
    __seq_o_ie(Ap_NilExtContainer,                 iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_GBR_QosInformation)
    __seq_m_ie(BitRate,             e_RAB_MaximumBitrateDL)
    __seq_m_ie(BitRate,             e_RAB_MaximumBitrateUL)
    __seq_m_ie(BitRate,             e_RAB_GuaranteedBitrateDL)
    __seq_m_ie(BitRate,             e_RAB_GuaranteedBitrateUL)
    __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_E_RABLevelQoSParameters)
    __seq_m_ie(QCI,                                   qci)
    __seq_m_ie(S1AP_AllocationAndRetentionPriority,   priority)
    __seq_o_ie(S1AP_GBR_QosInformation,               gbr)
    __seq_o_ie(Ap_NilExtContainer,                    iE_Extensions)
    __OOO__
__def_sequence_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_E_RABToBeSetupItemCtxtSUReq)
    __seq_m_ie(S1AP_E_RAB_ID,                      erabId)
    __seq_m_ie(S1AP_E_RABLevelQoSParameters,       qos)
    __seq_m_ie(TransportLayerAddress,              transportLayerAddress)
    __seq_m_ie(GTP_TEID,                           gtpTeid)
    __seq_o_ie(NAS_PDU,                            nasPdu)
    __seq_o_ie(Ap_NilExtContainer,                 iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_E_RABToBeSetupItemCtxtSUReqIEs)
    __ap_proto_m_ie(S1AP_E_RABToBeSetupItemCtxtSUReq,    e_RABToBeSetupItemCtxtSUReq,         AP_reject)
__ap_proto_ies_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_ap_proto_ie_single_container(S1AP_E_RABToBeSetupItemCtxtSUReqContainer, S1AP_E_RABToBeSetupItemCtxtSUReqIEs)

__def_sequence_of( S1AP_E_RABToBeSetupListCtxtSUReq \
                 , S1AP_E_RABToBeSetupItemCtxtSUReqContainer \
                 , ___(1, maxNrOfE_RABs))

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_HandoverType)
    __enum_l(intralte)
    __enum_l(ltetoutran)
    __enum_l(ltetogeran)
    __enum_l(utrantolte)
    __enum_l(gerantolte)
    __OOO__
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_HandoverCommandMsgIes)
    __ap_proto_m_ie(S1AP_MME_UE_S1AP_ID,                         mME_UE_S1AP_ID,                                   AP_reject)
    __ap_proto_m_ie(S1AP_ENB_UE_S1AP_ID,                         eNB_UE_S1AP_ID,                                   AP_reject)
    __ap_proto_m_ie(S1AP_HandoverType,                           handoverType,                                     AP_reject)
    __ap_proto_o_ie(S1AP_NASSecurityParametersfromE_UTRAN,       nASSecurityParametersfromE_UTRAN,                 AP_reject)
    __ap_proto_o_ie(S1AP_E_RABSubjecttoDataForwardingList,       e_RABSubjecttoDataForwardingList,                 AP_ignore)
    __ap_proto_o_ie(S1AP_E_RABList,                              e_RABtoReleaseListHOCmd,                          AP_ignore)
    __ap_proto_m_ie(S1AP_Target_ToSource_TransparentContainer,   target_ToSource_TransparentContainer,             AP_reject)
    __ap_proto_o_ie(S1AP_Target_ToSource_TransparentContainer,   target_ToSource_TransparentContainer_Secondary,   AP_reject)
    __ap_proto_o_ie(S1AP_CriticalityDiagnostics,                 criticalityDiagnostics,                           AP_ignore)
__ap_proto_ies_end()

__def_ap_proto_ie_container(S1AP_HandoverCommandMsgContainer, S1AP_HandoverCommandMsgIes)
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_HandoverCommandMsg)
  __seq_m_ie(S1AP_HandoverCommandMsgContainer, ies)
  __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_UEAggregateMaximumBitrate)
    __seq_m_ie(BitRate,             uEAggregateMaximumBitRateDL)
    __seq_m_ie(BitRate,             uEAggregateMaximumBitRateUL)
    __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_oct_string(S1AP_E_UTRAN_Trace_ID,  __fixed(8))
__def_bit_string(S1AP_InterfacesToTrace, __fixed(8))

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_TraceDepth)
    __enum_l(minimum)
    __enum_l(medium)
    __enum_l(maximum)
    __enum_l(minimumWithoutVendorSpecificExtension)
    __enum_l(mediumWithoutVendorSpecificExtension)
    __enum_l(maximumWithoutVendorSpecificExtension)
    __OOO__
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_TraceActivation)
    __seq_m_ie(S1AP_E_UTRAN_Trace_ID,     e_UTRAN_Trace_ID)
    __seq_m_ie(S1AP_InterfacesToTrace,    interfacesToTrace)
    __seq_m_ie(S1AP_TraceDepth,           traceDepth)
    __seq_m_ie(TransportLayerAddress,     traceCollectionEntityIPAddress)
    __seq_o_ie(Ap_NilExtContainer,        iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_UESecurityCapabilities)
    __seq_m_ie(EncryptionAlgorithms,               encryptionAlgorithms)
    __seq_m_ie(IntegrityProtectionAlgorithms,      integrityProtectionAlgorithms)
    __seq_o_ie(Ap_NilExtContainer,                 iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_bit_string(S1AP_SecurityKey, __fixed(256))
__def_oct_string(LAC, __fixed(2))
__def_oct_string(TAC, __fixed(2))

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_of(ForbiddenTACs, TAC, ___(1, 4096));
__def_sequence_of(ForbiddenLACs, LAC, ___(1, 4096));
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_ForbiddenTAs_Item)
    __seq_m_ie(PLMNidentity,        plmnId)
    __seq_m_ie(ForbiddenTACs,       forbiddenTACs)
    __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_ForbiddenLAs_Item)
    __seq_m_ie(PLMNidentity,         plmnId)
    __seq_m_ie(ForbiddenLACs,        forbiddenLACs)
    __seq_o_ie(Ap_NilExtContainer,   iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_of(S1AP_EPLMNs,             PLMNidentity,           ___(1, 15));
__def_sequence_of(S1AP_ForbiddenTAs,       S1AP_ForbiddenTAs_Item, ___(1, 16));
__def_sequence_of(S1AP_ForbiddenLAs,       S1AP_ForbiddenLAs_Item, ___(1, 16));

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_ForbiddenInterRATs)
    __enum_l(all)
    __enum_l(geran)
    __enum_l(utran)
    __enum_l(cdma2000)
    
    __OOO__

    __enum_l(geranandutran)
    __enum_l(cdma2000andutran)
__def_enum_end()
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_HandoverRestrictionList)
    __seq_m_ie(PLMNidentity,                servingPLMN)
    __seq_o_ie(S1AP_EPLMNs,                 equivalentPLMNs)
    __seq_o_ie(S1AP_ForbiddenTAs,           forbiddenTAs)
    __seq_o_ie(S1AP_ForbiddenLAs,           forbiddenLAs)
    __seq_o_ie(S1AP_ForbiddenInterRATs,     forbiddenInterRATs)
    __seq_o_ie(Ap_NilExtContainer,          iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_oct_string(S1AP_UERadioCapability);
__def_u16_type(S1AP_SubscriberProfileIDforRFP, ___(1, 256));

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CSFallbackIndicator)
    __enum_l(cs_fallback_required)
    __OOO__
    __enum_l(cs_fallback_high_priority)
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_SRVCCOperationPossible)
    __enum_l(possible)
    __OOO__
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_enum_begin(S1AP_CSGMembershipStatus)
    __enum_l(member)
    __enum_l(not_member)
__def_enum_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_LAI)
    __seq_m_ie(PLMNidentity,        plmnId)
    __seq_m_ie(LAC,                 lac)
    __seq_o_ie(Ap_NilExtContainer,  iE_Extensions)
    __OOO__
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__ap_proto_ies_begin(S1AP_InitialContextSetupRequestIes)
    __ap_proto_m_ie(S1AP_MME_UE_S1AP_ID,                         mME_UE_S1AP_ID,                                   AP_reject)
    __ap_proto_m_ie(S1AP_ENB_UE_S1AP_ID,                         eNB_UE_S1AP_ID,                                   AP_reject)
    __ap_proto_m_ie(S1AP_UEAggregateMaximumBitrate,              uEAggregateMaximumBitrate,                        AP_reject)
    __ap_proto_m_ie(S1AP_E_RABToBeSetupListCtxtSUReq,            e_RABToBeSetupListCtxtSUReq,                      AP_reject)
    __ap_proto_m_ie(S1AP_UESecurityCapabilities,                 uESecurityCapabilities,                           AP_reject)
    __ap_proto_m_ie(S1AP_SecurityKey,                            securityKey,                                      AP_reject)
    __ap_proto_o_ie(S1AP_TraceActivation,                        traceActivation,                                  AP_ignore)
    __ap_proto_o_ie(S1AP_HandoverRestrictionList,                handoverRestrictionList,                          AP_ignore)
    __ap_proto_o_ie(S1AP_UERadioCapability,                      uERadioCapability,                                AP_ignore)
    __ap_proto_o_ie(S1AP_SubscriberProfileIDforRFP,              subscriberProfileIDforRFP,                        AP_ignore)
    __ap_proto_o_ie(S1AP_CSFallbackIndicator,                    cSFallbackIndicator,                              AP_reject)
    __ap_proto_o_ie(S1AP_SRVCCOperationPossible,                 sRVCCOperationPossible,                           AP_ignore)
    __ap_proto_o_ie(S1AP_CSGMembershipStatus,                    cSGMembershipStatus,                              AP_ignore)
    __ap_proto_o_ie(S1AP_LAI,                                    registeredLAI,                                    AP_ignore)
__ap_proto_ies_end()

__def_ap_proto_ie_container(S1AP_InitialContextSetupRequestContainer, S1AP_InitialContextSetupRequestIes)
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_InitialContextSetupRequest)
    __seq_m_ie(S1AP_InitialContextSetupRequestContainer, ies)
    __OOO__
__def_sequence_end()


////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////
__def_sequence_begin(S1AP_InitiatingMessage)
    __seq_m_ie(AP_ProcedureCode, procedureCode)
    __seq_m_ie(AP_Criticality,   criticality)
    __seq_m_ie(ASN1_OpenType,     value)
__def_sequence_end()

__def_sequence_begin(S1AP_SuccessfulOutcome)
    __seq_m_ie(AP_ProcedureCode, procedureCode)
    __seq_m_ie(AP_Criticality,   criticality)
    __seq_m_ie(ASN1_OpenType,     value)
__def_sequence_end()

__def_sequence_begin(S1AP_UnsuccessfulOutcome)
    __seq_m_ie(AP_ProcedureCode, procedureCode)
    __seq_m_ie(AP_Criticality,   criticality)
    __seq_m_ie(ASN1_OpenType,     value)
__def_sequence_end()

////////////////////////////////////////////////////////////////////////////
// S1AP PDU
////////////////////////////////////////////////////////////////////////////
__def_choice_begin(S1AP_PDU)
   __choice(S1AP_InitiatingMessage)
   __choice(S1AP_SuccessfulOutcome)
   __choice(S1AP_UnsuccessfulOutcome)
   __OOO__
__def_choice_end()
