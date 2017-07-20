/*
 * Asn1BitPos.h
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1BITPOS_H_
#define ASN1BITPOS_H_

#include "l0-infra/codec/asn.1/Asn1Types.h"

struct Asn1BitPos
{
   explicit Asn1BitPos
      ( const Oct* oct = 0
      , U8    bitOffset = 0)
      : oct(const_cast<Oct*>(oct))
      , bitOffset(bitOffset)
   {
   }

   bool isValid() const
   {
       return oct != 0;
   }

   bool isPhyOctAligned() const
   {
       return bitOffset == 0;
   }

   bool octLessThan(const Asn1BitPos& rhs) const
   {
       return oct < rhs.oct;
   }

   bool operator<(const Asn1BitPos& rhs) const
   {
       return (oct < rhs.oct) || ((oct == rhs.oct) && (bitOffset < rhs.bitOffset));
   }

   bool operator<=(const Asn1BitPos& rhs) const
   {
       return (oct < rhs.oct) || ((oct == rhs.oct) && (bitOffset <= rhs.bitOffset));
   }

   bool operator>(const Asn1BitPos& rhs) const
   {
       return (oct > rhs.oct) || ((oct == rhs.oct) && (bitOffset > rhs.bitOffset));
   }

   bool operator>=(const Asn1BitPos& rhs) const
   {
       return (oct > rhs.oct) || ((oct == rhs.oct) && (bitOffset >= rhs.bitOffset));
   }

   bool operator==(const Asn1BitPos& rhs) const
   {
       return oct == rhs.oct && bitOffset == rhs.bitOffset;
   }

   bool operator!=(const Asn1BitPos& rhs) const
   {
       return !(*this == rhs);
   }

   const Oct* getOct() const
   {
       return oct;
   }

   U8 getBitOffset() const
   {
       return bitOffset;
   }

   U8 getAvailBits() const
   {
       return 8 - bitOffset;
   }


   bool decodeBit()
   {
       return (*oct & (1 << (7 - bitOffset++))) > 0;
   }

   void operator++()
   {
       oct++;
       bitOffset = 0;
   }

   U8 getAvailBits(const Asn1BitPos& end) const;
   U8 decodeBits(U8 numOfBits);


   U32 operator-(const Asn1BitPos& rhs) const;

   void fastFwd(U32 bits);

   Asn1BitPos alignWith(const U8 offset);
   Asn1BitPos plus(U32 numOfBits) const;

   void copyTo(const Asn1BitPos& to, U32 numOfBits) const;

private:
    U8 decodeBitsEx(U8 numOfBits);
    void noAlignCopy(const Asn1BitPos& to, U32 numOfBits) const;
    void alignCopy(const Asn1BitPos& to, U32 numOfBits) const;
    void encodeBits(U8 numOfBits, U8 value);

public:
   Oct*  oct;
   U8    bitOffset;

};

#endif /* ASN1BITPOS_H_ */
