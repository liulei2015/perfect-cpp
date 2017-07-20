/*
 * Asn1ExtRootNumberTraits.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1EXTROOTNUMBERTRAITS_H_
#define ASN1EXTROOTNUMBERTRAITS_H_

template <typename T, bool>
struct Asn1ExtRootNumberTraits
{
};

template <typename T>
struct Asn1ExtRootNumberTraits<T, true>
{
   enum { ext_root_number = T::ext_root_num
        , ext_number = T::__enum_literal_num - T::ext_root_num };
};

template <typename T>
struct Asn1ExtRootNumberTraits<T, false>
{
   enum { ext_root_number = T::__enum_literal_num
        , ext_number      = 0 };
};

#endif /* ASN1EXTROOTNUMBERTRAITS_H_ */

