/*
 * S1ApPublicDef.h
 *
 * Created on: Sep 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef S1APPUBLICDEF_H_
#define S1APPUBLICDEF_H_

#include "l0-infra/codec/asn.1/interp/Asn1PublicDef.h"
#include "l0-infra/codec/asn.1/Asn1Types.h"

#define S1AP_CODEC(p_name) ASN1_CODEC(p_name)
#define S1AP_IE_ID(p_name) id_##p_name

#define DEF_S1AP_IE_ID(p_name, value) \
   const ASN1_NS::U16 S1AP_IE_ID(p_name) = value;

#endif /* S1APPUBLICDEF_H_ */

