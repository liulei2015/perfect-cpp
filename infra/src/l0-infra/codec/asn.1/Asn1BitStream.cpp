/*
 * Asn1BitStream.cpp
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 
#include "l0-infra/codec/asn.1/Asn1BitStream.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/UnsignedTypeTraits.h"
#include "l0-infra/codec/asn.1/Asn1Segment.h"

#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/max_min.h"
#include <memory.h>
#include "l0-infra/codec/asn.1/Asn1SegmentList.h"

////////////////////////////////////////////////////////
Asn1BitStream::Asn1BitStream(Asn1Segment* segment)
   : segment(segment)
{
    segment->getScope(cursor, end);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::reload()
{
   segment = segment->getNextSegment();
   USI_ASSERT_VALID_PTR_R(segment, ASN1_E_EOF);
   segment->getScope(cursor, end);

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
inline Status Asn1BitStream::checkEof()
{
   if(cursor.oct < end.oct) return USI_SUCCESS;

   if(cursor.oct == end.oct && cursor.bitOffset < end.bitOffset)
   {
      return USI_SUCCESS;
   }

   return reload();
}

////////////////////////////////////////////////////////
inline Status Asn1BitStream::stepCursor()
{
   ++cursor;

   return checkEof();
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBit(bool& bit)
{
   USI_ASSERT_SUCC_CALL(checkEof());

   if(cursor.getAvailBits(end) == 0)
   {
      USI_ASSERT_SUCC_CALL(stepCursor());
   }

   bit = cursor.decodeBit();

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::skipBits(const U32 numOfBits)
{
    U32 remainBits = numOfBits;
    while(remainBits > 0)
    {
        USI_ASSERT_SUCC_CALL(checkEof());
        U32 availBits = end - cursor;
        U32 consumedBits = __USI_MIN(availBits, remainBits);

        if(availBits == consumedBits)
        {
            cursor = end;
        }
        else
        {
            cursor.fastFwd(consumedBits);
        }

        remainBits -= consumedBits;
    }

    return USI_SUCCESS;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsSegment(const U32 numOfBits, Asn1SegmentList& segList)
{
    U32 remainBits = numOfBits;
    while(remainBits > 0)
    {
        USI_ASSERT_SUCC_CALL(checkEof());
        U32 availBits = end - cursor;
        U32 consumedBits = __USI_MIN(availBits, remainBits);
        
        USI_ASSERT_SUCC_CALL(segList.pushBack(cursor, consumedBits));
        
        if(availBits == consumedBits)
        {
            cursor = end;
        }
        else
        {
            cursor.fastFwd(consumedBits);
        }
        
        remainBits -= consumedBits;
    }

    return USI_SUCCESS;
}

////////////////////////////////////////////////////////
template <typename T>
Status Asn1BitStream::doDecodeBitsAsSignedInt(const U8 numOfBits, T& value)
{
   if(numOfBits == 0)
   {
      value = 0;
      return USI_SUCCESS;
   }

   USI_ASSERT_TRUE_R(numOfBits <= sizeof(T) * 8, ASN1_E_NOT_IMPL);

   typedef typename UnsignedTypeTraits<T>::UnsignedType UnsignedType;

   bool negtive = false;
   USI_ASSERT_SUCC_CALL(decodeBit(negtive));
   USI_ASSERT_SUCC_CALL(doDecodeBitsAsUnsignedInt(numOfBits - 1, (UnsignedType&)value));

   if(negtive)
   {
      value |= (UnsignedType)1 << (numOfBits - 1);
      for(U8 i=numOfBits/8; i<sizeof(T); i++)
      {
         value |= ((UnsignedType)0xFF << (i * 8));
      }
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
template <typename T>
Status Asn1BitStream::doDecodeBitsAsUnsignedInt(const U8 numOfBits, T& value)
{
   USI_ASSERT_TRUE_R(numOfBits <= sizeof(T) * 8, ASN1_E_NOT_IMPL);

   value = 0;

   U8 remainBits = numOfBits;

   while(remainBits > 0)
   {
      USI_ASSERT_SUCC_CALL(checkEof());
      U8 bits = __USI_MIN(remainBits, cursor.getAvailBits(end));
      remainBits -= bits;
      value |= (T)cursor.decodeBits(bits) << remainBits;
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsUnsignedInt(const U8 numOfBits, U64& value)
{
   return doDecodeBitsAsUnsignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsUnsignedInt(const U8 numOfBits, U32& value)
{
   return doDecodeBitsAsUnsignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsUnsignedInt(const U8 numOfBits, U16& value)
{
   return doDecodeBitsAsUnsignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsUnsignedInt(const U8 numOfBits, U8& value)
{
   return doDecodeBitsAsUnsignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsSignedInt(const U8 numOfBits, S64& value)
{
   return doDecodeBitsAsSignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsSignedInt(const U8 numOfBits, S32& value)
{
   return doDecodeBitsAsSignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsSignedInt(const U8 numOfBits, S16& value)
{
   return doDecodeBitsAsSignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsAsSignedInt(const U8 numOfBits, S8& value)
{
   return doDecodeBitsAsSignedInt(numOfBits, value);
}

////////////////////////////////////////////////////////
Status Asn1BitStream::octAlign()
{
   USI_ASSERT_SUCC_CALL(checkEof());

   if(!cursor.isPhyOctAligned())
   {
      if(cursor.octLessThan(end))
      {
          ++cursor;
      }
      else
      {
          USI_ASSERT_SUCC_CALL(reload());
      }
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
U32 Asn1BitStream::getAvailOcts() const
{
    return (end - cursor) / 8;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::decodeBitsToBuf(const U32 numOfBits, Oct* buf, U32 size)
{
   USI_ASSERT_TRUE_R(size * 8 >= numOfBits, ASN1_E_OVERFLOW);
   U32 octs = numOfBits / 8;
   U8 remainBits = (U8)(numOfBits % 8);
   Oct* p = buf;

   while(octs > 0)
   {
       //USI_ASSERT_SUCC_CALL(checkEof());
        U32 numOfOcts = __USI_MIN(getAvailOcts(), octs);
        if(cursor.isPhyOctAligned())
        {
            memcpy(p, cursor.getOct(), numOfOcts);
            octs -= numOfOcts;
            p += numOfOcts;
            cursor = cursor.plus(numOfOcts * 8);
            
        }
        else
        {
            for(U32 i=0; i<numOfOcts; i++)
            {
                USI_ASSERT_SUCC_CALL(decodeBitsAsUnsignedInt(8, *p));
                p++;
            }
        }
   }

   if(remainBits > 0)
   {
      USI_ASSERT_SUCC_CALL(decodeBitsAsUnsignedInt(remainBits, *p));
      *p <<= (8 - remainBits);
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::getCursor(Asn1BitPos& cursor)
{
   USI_ASSERT_SUCC_CALL(checkEof());

   cursor = this->cursor;

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////
Status Asn1BitStream::getEnd(Asn1BitPos& end)
{
   USI_ASSERT_SUCC_CALL(checkEof());

   end = this->end;
   return USI_SUCCESS;
}
