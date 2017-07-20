/*
 * Asn1ExtendabilityTraits.h
 *
 * Created on: Sep 27, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1EXTENDABILITYTRAITS_H_
#define ASN1EXTENDABILITYTRAITS_H_

template <typename T>
struct Asn1ExtendabilityTraits
{
private:
   class __true_type  {};
   class __false_type { int a; };

   template <typename U>
   static __true_type helper(typename U::ExtendMarker*);

   template <typename U>
   static __false_type helper(...);

public:
   static const bool extendable = sizeof(helper<T>(0)) == sizeof(__true_type);

};

#endif /* ASN1EXTENDABILITYTRAITS_H_ */

