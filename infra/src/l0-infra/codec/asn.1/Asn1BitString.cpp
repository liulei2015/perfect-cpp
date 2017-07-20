/*
 * Asn1BitString.cpp
 *
 * Created on: Oct 1, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#include "l0-infra/codec/asn.1/Asn1BitString.h"
#include "l0-infra/codec/asn.1/Asn1Segment.h"
#include "l0-infra/codec/asn.1/Asn1BitPos.h"

ASN1_NS_BEGIN

/////////////////////////////////////////////////////////////////
bool Asn1BitString::isSet(U32 bit) const
{
   if(bit >= numOfBits)
   {
      return false;
   }

   for(Asn1Segment* seg = segment; seg != 0; seg = seg->getNextSegment())
   {
       if(bit < seg->getNumOfBits())
       {
           return Asn1BitPos(seg->getStartOct()).plus(bit).decodeBit();
       }

       bit -= seg->getNumOfBits();
   }

   return false;
}

ASN1_NS_END

