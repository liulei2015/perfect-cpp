/*
 * Asn1PerDecoder.cpp
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/codec/asn.1/Asn1PerDecoder.h"
#include "l0-infra/codec/asn.1/UnsignedTypeTraits.h"
#include "l0-infra/codec/asn.1/Asn1BitString.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/Asn1OpenType.h"

#include <limits>
#include <stdio.h>
#include "l0-infra/codec/asn.1/Asn1CodecBuf.h"
#include "l0-infra/codec/asn.1/Asn1SegmentList.h"

////////////////////////////////////////////////////////////
Asn1PerDecoder::Asn1PerDecoder
      ( Asn1Segment* segment
      , Asn1CodecBuf& codecBuf)
   : stream(segment)
   , codecBuf(codecBuf)
{
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::getUndecodedStream(Asn1BitPos& end)
{
   return stream.getEnd(end);
}

////////////////////////////////////////////////////////////
namespace
{
   template <typename T>
   inline U8 getRequiredBits(T range)
   {
      if(range == 0) return 0;

      U8 bits = 1;
      while((range >>= 1) > 0)
      {
         bits++;
      }

      return bits;
   }

   template <typename T>
   inline U8 getRequiredBytes(T range)
   {
      return (getRequiredBits(range) - 1)/8 + 1;
   }
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::getBytesOfConsInt(const T range, U8& bytes)
{
   if(range == std::numeric_limits<U8>::max())
   {
      bytes = 1;
   }
   else if(range <= std::numeric_limits<U16>::max())
   {
      bytes = 2;
   }
   else
   {
      const Asn1IntConstraint<U8> cons(1, getRequiredBytes(range));
      USI_ASSERT_SUCC_CALL(doDecodeConsLength(cons, bytes));
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
template <typename UT, typename T>
Status Asn1PerDecoder::decodeAlignedConsInt(const UT range, T& value)
{
   U8 bytes = 0;

   USI_ASSERT_SUCC_CALL(getBytesOfConsInt(range, bytes));
   USI_ASSERT_TRUE_R(bytes <= sizeof(U64), ASN1_E_NOT_IMPL);
   USI_ASSERT_TRUE_R(bytes <= sizeof(T), ASN1_E_INT_CHOICE);
   USI_ASSERT_SUCC_CALL(stream.octAlign());
   USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(bytes * 8, value));

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeConsInt(const Asn1IntConstraint<T>& cons, T& finalValue)
{
   typedef typename UnsignedTypeTraits<T>::UnsignedType UnsignedType;

   UnsignedType value = 0;

   if(cons.range() < std::numeric_limits<U8>::max())
   {
      USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(getRequiredBits(cons.range()), value));
   }
   else
   {
      USI_ASSERT_SUCC_CALL(decodeAlignedConsInt(cons.range(), value));
   }

   USI_ASSERT_TRUE_R(value <= cons.range(), ASN1_E_VALUE_RANGE);

   finalValue = value + cons.lb;

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<U64>& cons, U64& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<U32>& cons, U32& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<U16>& cons, U16& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<U8>& cons, U8& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<S64>& cons, S64& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<S32>& cons, S32& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<S16>& cons, S16& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsInt(const Asn1IntConstraint<S8>& cons, S8& value)
{
   return doDecodeConsInt(cons, value);
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeSemiConsInt(const T lb, T& value)
{
   typedef typename UnsignedTypeTraits<T>::UnsignedType UnsignedType;

   U8 bytes = 0;
   USI_ASSERT_SUCC_CALL(decodeUnconsLength(bytes));

   UnsignedType v = 0;
   USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(bytes * 8, v));

   USI_ASSERT_TRUE_R(v <= (UnsignedType)(std::numeric_limits<T>::max() - lb), ASN1_E_SYNTAX_T);

   value = v + lb;

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(U8 lb, U8& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(U16 lb, U16& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(U32 lb, U32& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsIntInt(U64 lb, U64& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(S8 lb, S8& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(S16 lb, S16& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(S32 lb, S32& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsInt(S64 lb, S64& value)
{
   return doDecodeSemiConsInt(lb, value);
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeSmallUnsignedInt(T& value)
{
   bool smallBit = false;
   USI_ASSERT_SUCC_CALL(stream.decodeBit(smallBit));

   if(!smallBit) // less than 64
   {
      // X.691-11.6.1
      USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(6, value));
   }
   else
   {
      // x.691-11.6.2
      USI_ASSERT_SUCC_CALL(doDecodeSemiConsInt((T)0, value));
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSmallUnsignedInt(U32& value)
{
   return doDecodeSmallUnsignedInt(value);
}

////////////////////////////////////////////////////////////
const U16 __16K__ = 0x4000;

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeUnconsLength(T& len)
{
   USI_ASSERT_SUCC_CALL(stream.octAlign());

   bool bit8 = false;
   USI_ASSERT_SUCC_CALL(stream.decodeBit(bit8));

   if(!bit8) // less than 128
   {
      USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(7, len));
      return USI_SUCCESS;
   }

   bool bit7 = false;
   USI_ASSERT_SUCC_CALL(stream.decodeBit(bit7));

   if(!bit7) // less than 16K
   {
      USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(14, len));
      return USI_SUCCESS;
   }

   // n >= 16K, fragment
   U8 m = 0;
   USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(6, m));
   USI_ASSERT_TRUE_R(m >= 1 && m <= 4, ASN1_E_VALUE_RANGE);
   len = m * __16K__;

   return USI_CONTINUE;
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsLength(U32& len)
{
   return doDecodeUnconsLength(len);
}

Status Asn1PerDecoder::decodeUnconsLength(U16& len)
{
    return doDecodeUnconsLength(len);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsLength(U8& len)
{
    return doDecodeUnconsLength(len);
}

////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSemiConsLength(U32 lb, U32& len)
{
   return doDecodeUnconsLength(len);
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeConsLength(const Asn1IntConstraint<T>& cons, T& len)
{
   if(cons.lessThan64K())
   {
      USI_ASSERT_SUCC_CALL(doDecodeConsInt(cons, len));
   }
   else
   {
      return doDecodeUnconsLength(len);
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsLength(const Asn1IntConstraint<U64>& cons, U64& len)
{
   return doDecodeConsLength(cons, len);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsLength(const Asn1IntConstraint<U32>& cons, U32& len)
{
   return doDecodeConsLength(cons, len);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsLength(const Asn1IntConstraint<U16>& cons, U16& len)
{
   return doDecodeConsLength(cons, len);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsLength(const Asn1IntConstraint<U8>& cons, U8& len)
{
   return doDecodeConsLength(cons, len);
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeSmallLength(T& len)
{
   bool smallBit = false;
   USI_ASSERT_SUCC_CALL(stream.decodeBit(smallBit));

   if(!smallBit) // <= 64
   {
      // X.691-11.9.3.4
      USI_ASSERT_SUCC_CALL(stream.decodeBitsAsUnsignedInt(6, len));
      len += 1;
   }
   else
   {
      // x.691-11.9.3.4
      USI_ASSERT_SUCC_CALL(doDecodeUnconsLength(len));
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSmallLength(U32& len)
{
   return doDecodeSmallLength(len);
}

////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeUnconsInt(T& value)
{
   U8 bytes = 0;
   USI_ASSERT_SUCC_CALL(doDecodeUnconsLength(bytes));
   USI_ASSERT_TRUE_R(bytes <= sizeof(T), ASN1_E_INT_CHOICE);

   typedef typename UnsignedTypeTraits<T>::SignedType SignedType;
   SignedType sv = 0;
   USI_ASSERT_SUCC_CALL(stream.decodeBitsAsSignedInt(bytes * 8, sv));
   value = (T)sv;

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(U8& value)
{
   return doDecodeSemiConsInt((U8)0, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(U16& value)
{
   return doDecodeSemiConsInt((U16)0, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(U32& value)
{
   return doDecodeSemiConsInt((U32)0, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(U64& value)
{
   return doDecodeSemiConsInt((U64)0, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(S8& value)
{
   return doDecodeUnconsInt(value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(S16& value)
{
   return doDecodeUnconsInt(value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(S32& value)
{
   return doDecodeUnconsInt(value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsInt(S64& value)
{
   return doDecodeUnconsInt(value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::actualDecodeUnconsComponent
    ( const U32 units
    , const U8 bitsPerUnit
    , Asn1Component& comp)
{
    Asn1SegmentList segList(codecBuf);
    USI_ASSERT_SUCC_CALL(stream.decodeBitsAsSegment(units * bitsPerUnit, segList));

    U32 totalUnits = units;
    Status status = USI_CONTINUE;
    while(status == USI_CONTINUE)
    {
        U32 lenInUnit = 0;
        status = doDecodeUnconsLength(lenInUnit);
        if(IS_FAILED_STATUS(status))
        {
            return status;
        }

        totalUnits += lenInUnit;
        USI_ASSERT_SUCC_CALL(stream.decodeBitsAsSegment(lenInUnit * bitsPerUnit, segList));
    }

    comp.updateSegment(segList);

    return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::decodeConsComponentLen
         (const Asn1Constraint<T>& cons
         , T& length
         , U8 bitsPerUnit)
{
   bool ext = false;
   if(cons.ext)
   {
      USI_ASSERT_SUCC_CALL(stream.decodeBit(ext));
   }

   length = 0;

   if(!ext)
   {
      if(cons.range() == 0 && cons.lessThan64K())
      {
         length = cons.ub;
      }
      else
      {
         return doDecodeConsLength(cons, length);
      }
   }
   else
   {
      USI_ASSERT_SUCC_CALL(doDecodeUnconsLength(length));
   }

   if(ext || cons.range() > 0 || cons.ub > ((T)16 / bitsPerUnit))
   {
       USI_ASSERT_SUCC_CALL(stream.octAlign());
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::actualDecodeConsComponent
         ( const U32 units
         , const U8 bitsPerUnit
         , Asn1Component& component)
{
   Asn1SegmentList segList(codecBuf);
   USI_ASSERT_SUCC_CALL(stream.decodeBitsAsSegment(units * bitsPerUnit, segList));
   component.updateSegment(segList);

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeComponent
               ( const Status status
               , const U32 units
               , const U8 bitsPerUnit
               , Asn1Component& comp)
{
   if(units == 0) return USI_SUCCESS;

   if(status == USI_SUCCESS)
   {
      return actualDecodeConsComponent(units, bitsPerUnit, comp);
   }
   else if(status == USI_CONTINUE)
   {
      return actualDecodeUnconsComponent(units, bitsPerUnit, comp);
   }

   return status;
}
/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::decodeConsComponent
            ( const Asn1Constraint<T>& cons
            , const U8 bitsPerUnit
            , Asn1Component& component)
{
   T length = 0;
   Status status = decodeConsComponentLen(cons, length, bitsPerUnit);

   return decodeComponent(status, (U32)length, bitsPerUnit, component);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsComponent
            ( const U8 bitsPerUnit
            , Asn1Component& comp)
{
   USI_ASSERT_SUCC_CALL(stream.octAlign());

   U32 length = 0;
   Status status = doDecodeUnconsLength(length);
   return decodeComponent(status, length, bitsPerUnit, comp);
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::decodeUnconsGenericComponent(T& comp)
{
   return decodeUnconsComponent(comp.getBitsPerUnit(), comp);
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::decodeConsGenericComponent(const Asn1Constraint<U32>& cons, T& comp)
{
   return decodeConsComponent(cons, comp.getBitsPerUnit(), comp);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsBitString
    ( const Asn1Constraint<U32>& cons
    , Asn1BitString& bitString)
{
   return decodeConsGenericComponent(cons, bitString);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsBitString(Asn1BitString& bitString)
{
   return decodeUnconsGenericComponent(bitString);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeConsOctString
      ( const Asn1Constraint<U32>& cons
      , Asn1OctString& octString)
{
   return decodeConsGenericComponent(cons, octString);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeUnconsOctString(Asn1OctString& octString)
{
   return decodeUnconsGenericComponent(octString);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::skipBits(const U32 numOfBits)
{
   return stream.skipBits(numOfBits);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::gotoUnconsBlockStart(Asn1BitPos& start, U32& size)
{
   Status status = doDecodeUnconsLength(size);
   if(IS_FAILED_STATUS(status))
   {
      return status;
   }

   USI_ASSERT_SUCC_CALL(stream.getCursor(start));

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeBit(bool& bit)
{
   return stream.decodeBit(bit);
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeConsInt(const Asn1Constraint<T>& cons, T& value)
{
   bool ext = false;
   if(cons.ext)
   {
      USI_ASSERT_SUCC_CALL(decodeBit(ext));
   }

   if(ext)
   {
      USI_ASSERT_SUCC_CALL(decodeUnconsInt(value));
   }
   else
   {
      if(cons.range() == 0)
      {
         value = cons.ub;
      }
      else
      {
         USI_ASSERT_SUCC_CALL(decodeConsInt(cons, value));
      }
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<U64>& cons, U64& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<U32>& cons, U32& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<U16>& cons, U16& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<U8>& cons, U8& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<S64>& cons, S64& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<S32>& cons, S32& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<S16>& cons, S16& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeInt(const Asn1Constraint<S8>& cons,  S8& value)
{
   return doDecodeConsInt(cons, value);
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::doDecodeEnum
         ( const bool isExt
         , U32 numOfRoot
         , U32 numOfLiteral
         , U32& value)
{
   bool ext = false;
   if(isExt)
   {
      USI_ASSERT_SUCC_CALL(decodeBit(ext));
   }

   if(!ext)
   {
      const Asn1IntConstraint<U32> cons(0, numOfRoot - 1);
      USI_ASSERT_SUCC_CALL(decodeConsInt(cons, value));
   }
   else
   {
      U32 extIndex = 0;
      USI_ASSERT_SUCC_CALL(decodeSmallUnsignedInt(extIndex));
      USI_ASSERT_TRUE_R(extIndex < numOfLiteral - numOfRoot, ASN1_E_SYNTAX_T);

      value = extIndex + numOfRoot;
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeSeqPreamble
      ( const U8 numOfRoot
      , Asn1BitString& rootbitmap
      , bool isExt
      , const U8 numOfExt
      , Asn1BitString& extBitmap)
{
   bool ext = false;
   if(isExt)
   {
      USI_ASSERT_SUCC_CALL(decodeBit(ext));
   }

   if(numOfRoot > 0)
   {
      USI_ASSERT_SUCC_CALL(decodeConsBitString(Asn1Constraint<U32>(false, numOfRoot, numOfRoot), rootbitmap));
   }

   if(ext)
   {
      USI_ASSERT_TRUE_R(numOfExt > 0, ASN1_E_SYNTAX_T);

      U32 n = 0;
      USI_ASSERT_SUCC_CALL(decodeSmallLength(n));
      USI_ASSERT_TRUE_R(n == numOfExt, ASN1_E_SYNTAX_T);
      USI_ASSERT_SUCC_CALL(decodeConsBitString(Asn1Constraint<U32>(false, numOfExt, numOfExt), extBitmap));
   }

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
template <typename T>
Status Asn1PerDecoder::doDecodeSeqOfN
        ( const Asn1Constraint<T>& cons
        , T& len)
{
    bool ext = false;
    if(cons.ext)
    {
        USI_ASSERT_SUCC_CALL(stream.decodeBit(ext));
    }

    if(!ext)
    {
        if(cons.range() == 0 && cons.lessThan64K())
        {
            len = cons.ub;
        }
        else
        {
            USI_ASSERT_SUCC_CALL(decodeConsLength(cons, len));
        }
    }
    else
    {
        USI_ASSERT_SUCC_CALL(decodeUnconsLength(len));
        len += cons.lb;
    }

    return USI_SUCCESS;
}

Status Asn1PerDecoder::decodeSeqOfN
    ( const Asn1Constraint<U32>& cons
    , U32& len)
{
    return doDecodeSeqOfN(cons, len);
}

Status Asn1PerDecoder::decodeSeqOfN
    ( const Asn1Constraint<U16>& cons
    , U16& len)
{
    return doDecodeSeqOfN(cons, len);
}
/////////////////////////////////////////////////////////////////////////////////
Status Asn1PerDecoder::decodeOpenType(ASN1_OpenType& openType)
{
    return decodeUnconsOctString(openType);
}

