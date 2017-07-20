/*
 * Asn1PerDecoder.h
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1PERDECODER_H_
#define ASN1PERDECODER_H_

#include "l0-infra/codec/asn.1/Asn1BitStream.h"
#include "l0-infra/codec/asn.1/Asn1Constraint.h"
#include "l0-infra/codec/asn.1/Asn1BitString.h"
#include "l0-infra/codec/asn.1/Asn1OctString.h"
#include "l0-infra/base/Assertions.h"

ASN1_NS_BEGIN

struct Asn1CodecBuf;
struct ASN1_OpenType;

struct Asn1PerDecoder
{
   Asn1PerDecoder
      ( Asn1Segment* segment
      , Asn1CodecBuf& codecBuf);

   /////////////////////////////////////////////////////////////
   /// x.691-11.2: constrained whole number
   /////////////////////////////////////////////////////////////
   Status decodeOpenType(ASN1_OpenType& openType);

   /////////////////////////////////////////////////////////////
   /// x.691-11.5: constrained whole number
   /////////////////////////////////////////////////////////////
   Status decodeConsInt(const Asn1IntConstraint<U64>& cons, U64& value);
   Status decodeConsInt(const Asn1IntConstraint<U32>& cons, U32& value);
   Status decodeConsInt(const Asn1IntConstraint<U16>& cons, U16& value);
   Status decodeConsInt(const Asn1IntConstraint<U8>& cons, U8& value);

   Status decodeConsInt(const Asn1IntConstraint<S64>& cons, S64& value);
   Status decodeConsInt(const Asn1IntConstraint<S32>& cons, S32& value);
   Status decodeConsInt(const Asn1IntConstraint<S16>& cons, S16& value);
   Status decodeConsInt(const Asn1IntConstraint<S8>& cons, S8& value);

   //////////////////////////////////////////////////////////////
   // x.691-11.6: normally small non-negative whole number
   //////////////////////////////////////////////////////////////
   Status decodeSmallUnsignedInt(U32& value);

   //////////////////////////////////////////////////////////////
   // x.691-11.7: semi-constrained whole number
   //////////////////////////////////////////////////////////////
   Status decodeSemiConsInt(U8 lb, U8& value);
   Status decodeSemiConsInt(U16 lb, U16& value);
   Status decodeSemiConsInt(U32 lb, U32& value);
   Status decodeSemiConsIntInt(U64 lb, U64& value);

   Status decodeSemiConsInt(S8 lb, S8& value);
   Status decodeSemiConsInt(S16 lb, S16& value);
   Status decodeSemiConsInt(S32 lb, S32& value);
   Status decodeSemiConsInt(S64 lb, S64& value);

   //////////////////////////////////////////////////////////////
   // x.691-11.8: unconstrained whole number
   //////////////////////////////////////////////////////////////
   Status decodeUnconsInt(U8& value);
   Status decodeUnconsInt(U16& value);
   Status decodeUnconsInt(U32& value);
   Status decodeUnconsInt(U64& value);

   Status decodeUnconsInt(S8& value);
   Status decodeUnconsInt(S16& value);
   Status decodeUnconsInt(S32& value);
   Status decodeUnconsInt(S64& value);

   ///////////////////////////////////////////////////////////////////
   // x.691-11.9   unconstrained length determinant
   ///////////////////////////////////////////////////////////////////
   Status decodeUnconsLength(U32& len);
   Status decodeUnconsLength(U16& len);
   Status decodeUnconsLength(U8& len);

   /////////////////////////////////////////////////////////////
   /// x.691-11.9: constrained length determinant
   /////////////////////////////////////////////////////////////
   Status decodeConsLength(const Asn1IntConstraint<U64>& cons, U64& len);
   Status decodeConsLength(const Asn1IntConstraint<U32>& cons, U32& len);
   Status decodeConsLength(const Asn1IntConstraint<U16>& cons, U16& len);
   Status decodeConsLength(const Asn1IntConstraint<U8>& cons, U8& len);

   /////////////////////////////////////////////////////////////
   /// x.691-11.9: semi-constrained length determinant
   /////////////////////////////////////////////////////////////
   Status decodeSemiConsLength(U32 lb, U32& len);

   /////////////////////////////////////////////////////////////
   /// x.691-11.9: normally small length
   /////////////////////////////////////////////////////////////
   Status decodeSmallLength(U32& len);

   /////////////////////////////////////////////////////////////
   /// x.691-13: integer
   /////////////////////////////////////////////////////////////
   Status decodeInt(const Asn1Constraint<U64>& cons, U64& value);
   Status decodeInt(const Asn1Constraint<U32>& cons, U32& value);
   Status decodeInt(const Asn1Constraint<U16>& cons, U16& value);
   Status decodeInt(const Asn1Constraint<U8>& cons, U8& value);

   Status decodeInt(const Asn1Constraint<S64>& cons, S64& value);
   Status decodeInt(const Asn1Constraint<S32>& cons, S32& value);
   Status decodeInt(const Asn1Constraint<S16>& cons, S16& value);
   Status decodeInt(const Asn1Constraint<S8>& cons,  S8& value);

   /////////////////////////////////////////////////////////////
   /// x.691-14: enumerated type
   /////////////////////////////////////////////////////////////
   template <typename T>
   Status decodeEnum
         ( U32 maxOfLiteral
         , T& value
         , const bool isExt = false
         , U32 maxOfRoot = 0)
   {
      U32 v = 0;
      USI_ASSERT_SUCC_CALL(doDecodeEnum(isExt, maxOfRoot, maxOfLiteral, v));
      value = (T)v;
      return USI_SUCCESS;
   }

   /////////////////////////////////////////////////////////////
   /// x.691-16: bit string
   /////////////////////////////////////////////////////////////
   Status decodeConsBitString(const Asn1Constraint<U32>& cons, Asn1BitString&);
   Status decodeUnconsBitString(Asn1BitString&);

   /////////////////////////////////////////////////////////////
   /// x.691-17: octet string
   /////////////////////////////////////////////////////////////
   Status decodeConsOctString(const Asn1Constraint<U32>& cons, Asn1OctString&);
   Status decodeUnconsOctString(Asn1OctString&);

   /////////////////////////////////////////////////////////////
   /// x.691-19: sequence
   /////////////////////////////////////////////////////////////
   Status decodeSeqPreamble
            ( const U8 numOfRoot
            , Asn1BitString& rootbitmap
            , bool isExt
            , const U8 numOfExt
            , Asn1BitString& extBitmap);

   /////////////////////////////////////////////////////////////
   /// sequence of
   /////////////////////////////////////////////////////////////
   Status decodeSeqOfN
       (const Asn1Constraint<U32>& cons, U32& len);
   Status decodeSeqOfN
       ( const Asn1Constraint<U16>& cons, U16& len);

   ////////////////////////////////////////////////////////////
   Status getUndecodedStream(Asn1BitPos& end);
   Status skipBits(const U32 numOfBits);
   Status gotoUnconsBlockStart(Asn1BitPos& start, U32& size);
   Status decodeBit(bool& bit);

private:
   template <typename T>
   Status doDecodeConsInt(const Asn1Constraint<T>& cons, T& value);

   template <typename T>
   Status doDecodeConsInt(const Asn1IntConstraint<T>& cons, T& finalValue);

   template <typename UT, typename T>
   Status decodeAlignedConsInt(const UT range, T& value);

   ////////////////////////////////////////////////////////////
   template <typename T>
   Status getBytesOfConsInt(const T range, U8& bytes);

   ////////////////////////////////////////////////////////////
   template <typename T>
   Status doDecodeSemiConsInt(const T lb, T& value);

   ////////////////////////////////////////////////////////////
   template <typename T>
   Status doDecodeUnconsInt(T& value);

   ////////////////////////////////////////////////////////////
   template <typename T>
   Status doDecodeSmallUnsignedInt(T& value);

   ////////////////////////////////////////////////////////////
   template <typename T>
   Status doDecodeUnconsLength(T& len);

   template <typename T>
   Status doDecodeConsLength(const Asn1IntConstraint<T>& cons, T& len);

   template <typename T>
   Status doDecodeSmallLength(T& len);

   template <typename T>
   Status decodeConsComponentLen
            (const Asn1Constraint<T>& cons
            , T& length
            , U8 unitsPerOct);

   Status actualDecodeConsComponent
            ( const U32 units
            , const U8 bitsPerUnit
            , Asn1Component& component);

   Status actualDecodeUnconsComponent
            ( const U32 units
            , const U8 bitsPerUnit
            , Asn1Component& comp);

   template <typename T>
   Status doDecodeConsComponent
               ( const Asn1Constraint<T>& cons
               , Asn1Component& comp);

   template <typename T>
   Status decodeConsComponent
               ( const Asn1Constraint<T>& cons
               , const U8 bitsPerUnit
               , Asn1Component& component);

   Status decodeUnconsComponent
               ( const U8 bitsPerUnit
               , Asn1Component& comp);

   Status decodeComponent
               ( const Status status
               , const U32 units
               , const U8 bitsPerUnit
               , Asn1Component& comp);

   template <typename T>
   Status decodeUnconsGenericComponent( T& comp);

   template <typename T>
   Status decodeConsGenericComponent(const Asn1Constraint<U32>& cons, T& comp);

   Status doDecodeEnum
            ( const bool isExt
            , U32 numOfRoot
            , U32 numOfLiteral
            , U32& value);

   template <typename T>
   Status doDecodeSeqOfN
       ( const Asn1Constraint<T>& cons
       , T& len);

private:
   Asn1BitStream stream;
   Asn1CodecBuf& codecBuf;
};

ASN1_NS_END

#endif /* ASN1PERDECODER_H_ */

