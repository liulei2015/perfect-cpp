/*
 * Asn1PublicDef.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1PUBLICDEF_H_
#define ASN1PUBLICDEF_H_

#include "l0-infra/codec/asn.1/asn1.h"

#define ASN1_CODEC(p_name) p_name##_Codec

#define __IS_CHOSEN(p_name) is_##p_name##_chosen()
#define __CHOICE(p_name) get##p_name()

#define IS_CHOSEN(p_name) h().__IS_CHOSEN(p_name)
#define CHOICE(p_name) h().__CHOICE(p_name)

enum
{
   ASN1_NO_EXT = 0,
   ASN1_EXT
};

#define __ooo__ true
#define ___(...) __VA_ARGS__
#define __fixed(num, ...) num, num, ##__VA_ARGS__

#endif /* ASN1PUBLICDEF_H_ */

