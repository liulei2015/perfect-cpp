/*
 * Asn1Component.h
 *
 * Created on: Oct 2, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1COMPONENT_H_
#define ASN1COMPONENT_H_

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/max_min.h"

ASN1_NS_BEGIN

struct Asn1SegmentList;
struct Asn1Segment;

struct Asn1Component
{
    Asn1Component();

    void updateSegment(const Asn1SegmentList& segList);

    Status copyTo(Oct* buf, U32 size) const;
    Asn1Segment* getSegment() const;

private:
    U32 getNumOfBits() const;

protected:
    Asn1Segment* segment;
    U32 numOfBits;
};

template <U8 P_BITS_PER_UNIT>
struct Asn1GenericComponent : Asn1Component
{
    U32 size() const
    {
        return __CELLING(numOfBits, P_BITS_PER_UNIT);
    }

    U8 getBitsPerUnit() const
    {
        return P_BITS_PER_UNIT;
    }

};

ASN1_NS_END


#endif /* ASN1COMPONENT_H_ */

