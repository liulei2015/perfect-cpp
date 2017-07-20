/*
 * Asn1BitStream.h
 *
 * Created on: Sep 30, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ASN1BITSTREAM_H_
#define ASN1BITSTREAM_H_

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/codec/asn.1/Asn1BitPos.h"
#include "l0-infra/base/Status.h"

struct Asn1BitStreamLoader;
struct Asn1Segment;
struct Asn1SegmentList;

struct Asn1BitStream
{
   explicit Asn1BitStream(Asn1Segment* segment);

   Status decodeBit(bool& bit);
   Status decodeBitsAsSegment(const U32 numOfBits, Asn1SegmentList& segList);

   Status decodeBitsAsUnsignedInt(const U8 numOfBits, U64& value);
   Status decodeBitsAsUnsignedInt(const U8 numOfBits, U32& value);
   Status decodeBitsAsUnsignedInt(const U8 numOfBits, U16& value);
   Status decodeBitsAsUnsignedInt(const U8 numOfBits, U8& value);

   Status decodeBitsAsSignedInt(const U8 numOfBits, S64& value);
   Status decodeBitsAsSignedInt(const U8 numOfBits, S32& value);
   Status decodeBitsAsSignedInt(const U8 numOfBits, S16& value);
   Status decodeBitsAsSignedInt(const U8 numOfBits, S8& value);

   Status decodeBitsToBuf(const U32 numOfBits, Oct* buf, U32 size);

   Status octAlign();
   Status skipBits(const U32 numOfBits);
   Status getCursor(Asn1BitPos& cursor);
   Status getEnd(Asn1BitPos& end);

private:
   Status stepCursor();
   Status checkEof();
   Status load(const Asn1BitPos& from);
   Status reload();

   template <typename T>
   Status doDecodeBitsAsUnsignedInt(const U8 numOfBits, T& value);

   template <typename T>
   Status doDecodeBitsAsSignedInt(const U8 numOfBits, T& value);

   U32 getAvailOcts() const;

private:
   Asn1Segment* segment;
   Asn1BitPos cursor;
   Asn1BitPos end;
};

#endif /* ASN1BITSTREAM_H_ */

