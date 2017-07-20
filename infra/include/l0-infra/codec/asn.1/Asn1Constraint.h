/*
 * Asn1Constraint.h
 *
 * Created on: Sep 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1CONSTRAINT_H_
#define ASN1CONSTRAINT_H_

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/codec/asn.1/UnsignedTypeTraits.h"

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <limits>

ASN1_NS_BEGIN

template <typename T>
struct Asn1IntConstraint
{
   explicit Asn1IntConstraint
      ( const T lb = 0
      , const T ub = std::numeric_limits<T>::max()
      )
      : lb(lb)
      , ub(ub)
   {
   }

   typedef typename UnsignedTypeTraits<T>::UnsignedType UnsignedType;

   UnsignedType range() const
   {
      return ub - lb;
   }

   bool lessThan64K() const
   {
      return std::numeric_limits<U16>::max() >= ub;
   }

   const T lb;
   const T ub;
};

template <typename T>
struct Asn1Constraint : Asn1IntConstraint<T>
{
   explicit Asn1Constraint
      ( bool dummy
      , const T lb = 0
      , const T ub = std::numeric_limits<T>::max()
      , const bool ext = false)
      : Asn1IntConstraint<T>(lb, ub)
      , ext(ext)
   {
   }

   const bool ext;
};

ASN1_NS_END

#endif /* ASN1CONSTRAINT_H_ */

