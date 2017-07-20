/*
 * Asn1Component.cpp
 *
 * Created on: Oct 2, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/codec/asn.1/Asn1Component.h"
#include "l0-infra/codec/asn.1/Asn1SegmentList.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/codec/asn.1/Asn1Segment.h"
#include "l0-infra/codec/asn.1/Asn1BitPos.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/max_min.h"
#include <memory.h>

ASN1_NS_BEGIN

////////////////////////////////////////////////////////////////////////
Asn1Component::Asn1Component()
   : segment(0)
   , numOfBits(0)
{
}

void Asn1Component::updateSegment(const Asn1SegmentList& segList)
{
    segment = segList.getFirstSegment();

    numOfBits = 0;

    for(Asn1Segment* seg = segment; seg != 0; seg = seg->getNextSegment())
    {
        numOfBits += seg->getNumOfBits();
    }
}

////////////////////////////////////////////////////////////////////////
U32 Asn1Component::getNumOfBits() const
{
    return numOfBits;
}

////////////////////////////////////////////////////////////////////////
Status Asn1Component::copyTo(Oct* buf, U32 sizeOfBuf) const
{
   //U32 bits = getNumOfBits();

   USI_ASSERT_TRUE_R(sizeOfBuf * 8 >= numOfBits, ASN1_E_OVERFLOW);

   U32 copyBits = 0;
   for(Asn1Segment* seg = segment; seg != 0; seg = seg->getNextSegment())
   {
       Asn1BitPos(seg->getStartOct()).copyTo(Asn1BitPos(buf + copyBits/8, (U8)(copyBits % 8)), seg->getNumOfBits());
       copyBits += seg->getNumOfBits();
   }

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////////
Asn1Segment* Asn1Component::getSegment() const
{
    return segment;
}

ASN1_NS_END

