/*
 * UnsignedTypeTraits.h
 *
 * Created on: Sep 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef UNSIGNEDTYPETRAITS_H_
#define UNSIGNEDTYPETRAITS_H_

#include "l0-infra/codec/asn.1/Asn1Types.h"

template <typename T>
struct UnsignedTypeTraits
{
};

///////////////////////////////////////
template <>
struct UnsignedTypeTraits<S8>
{
   typedef S8 SignedType;
   typedef U8 UnsignedType;
};

template <>
struct UnsignedTypeTraits<U8>
{
   typedef S8 SignedType;
   typedef U8 UnsignedType;
};

///////////////////////////////////////
template <>
struct UnsignedTypeTraits<S16>
{
   typedef S16 SignedType;
   typedef U16 UnsignedType;
};

template <>
struct UnsignedTypeTraits<U16>
{
   typedef S16 SignedType;
   typedef U16 UnsignedType;
};

///////////////////////////////////////
template <>
struct UnsignedTypeTraits<S32>
{
   typedef S32 SignedType;
   typedef U32 UnsignedType;
};

template <>
struct UnsignedTypeTraits<U32>
{
   typedef S32 SignedType;
   typedef U32 UnsignedType;
};

///////////////////////////////////////
template <>
struct UnsignedTypeTraits<S64>
{
   typedef S64 SignedType;
   typedef U64 UnsignedType;
};

template <>
struct UnsignedTypeTraits<U64>
{
   typedef S64 SignedType;
   typedef U64 UnsignedType;
};

#endif /* UNSIGNEDTYPETRAITS_H_ */

