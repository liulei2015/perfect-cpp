#ifndef INCL_USI_S1ApConst_20130926060843_H__
#define INCL_USI_S1ApConst_20130926060843_H__

#include "l0-infra/codec/ap/interp/ApPublicDef.h"
#include "l0-infra/codec/ap/local/ApCommonDataTypes_L.h"

DEF_S1AP_IE_ID(mME_UE_S1AP_ID,                                 0);
DEF_S1AP_IE_ID(handoverType,                                   1);
DEF_S1AP_IE_ID(cause,                                          2);
DEF_S1AP_IE_ID(eNB_UE_S1AP_ID,                                 8);
DEF_S1AP_IE_ID(e_RABSubjecttoDataForwardingList,               12);
DEF_S1AP_IE_ID(e_RABtoReleaseListHOCmd,                        13);
DEF_S1AP_IE_ID(e_RABDataForwardingItem,                        14);
DEF_S1AP_IE_ID(e_RABToBeSetupListCtxtSUReq,                    24);
DEF_S1AP_IE_ID(traceActivation,                                25);
DEF_S1AP_IE_ID(e_RABItem,                                      35);
DEF_S1AP_IE_ID(handoverRestrictionList,                        41);
DEF_S1AP_IE_ID(e_RABToBeSetupItemCtxtSUReq,                    52);
DEF_S1AP_IE_ID(criticalityDiagnostics,                         58);
DEF_S1AP_IE_ID(uEAggregateMaximumBitrate,                      66);
DEF_S1AP_IE_ID(securityKey,                                    73);
DEF_S1AP_IE_ID(uERadioCapability,                              74);
DEF_S1AP_IE_ID(subscriberProfileIDforRFP,                      106);
DEF_S1AP_IE_ID(uESecurityCapabilities,                         107);
DEF_S1AP_IE_ID(cSFallbackIndicator,                            108);
DEF_S1AP_IE_ID(target_ToSource_TransparentContainer,           123);
DEF_S1AP_IE_ID(sRVCCOperationPossible,                         124);
DEF_S1AP_IE_ID(nASSecurityParametersfromE_UTRAN,               135);
DEF_S1AP_IE_ID(target_ToSource_TransparentContainer_Secondary, 139);
DEF_S1AP_IE_ID(cSGMembershipStatus,                            146);
DEF_S1AP_IE_ID(registeredLAI,                                  159);

const ASN1_NS::U16 maxNrOfE_RABs = 256;
const ASN1_NS::U16 s1ap_maxProtocolExtensions = 0xFF;

#define S1AP_PROC_CODE(p_proc) id_##p_proc

#define DEF_S1AP_PROC_CODE(p_proc, value) \
    const AP_ProcedureCode S1AP_PROC_CODE(p_proc) = value


DEF_S1AP_PROC_CODE(InitContextSetup,             9);

#endif

