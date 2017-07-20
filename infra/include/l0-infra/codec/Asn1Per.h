#ifndef ASN1_PER
#define ASN1_PER

#include "Asn1Context.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ASN1DLL
#define EXTERN __declspec(dllexport)
#else
#define EXTERN
#endif

#define PER_UNUM_ONE         ((ASN1UNUM)1)

#define PER_MAX_1BYTE       0xff
#define PER_MAX_2BYTE       0xffff
#define PER_MAX_3BYTE       0xffffff
#define PER_MAX_4BYTE       0xffffffff

#define PER_RANGE_1BYTE     0x100
#define PER_RANGE_2BYTE     0x10000
#define PER_RANGE_3BYTE     0x1000000

#define PER_VALUE_16K       (ASN1UINT)0x4000
#define PER_VALUE_64K       (ASN1UINT)0x10000

#define PER_BITS_1BYTE      8
#define PER_BITS_2BYTE      16


ASN1UINT BitsCount(ASN1UNUM value);
#define RangeBits(range) BitsCount((range) - 1)
ASN1STATUS PerEnExpandCodeBuff(Asn1Ctxt *ctxt, ASN1UINT nbytes);

ASN1STATUS PerEnCheckCodeBuffOctets(Asn1Ctxt *ctxt, ASN1UINT nocts);
ASN1STATUS PerDeCheckCodeBuffOctets(Asn1Ctxt *ctxt, ASN1UINT nocts);

ASN1STATUS PerEnCheckCodeBuffBits(Asn1Ctxt *ctxt, ASN1UINT nbits);
ASN1STATUS PerDeCheckCodeBuffBits(Asn1Ctxt *ctxt, ASN1UINT nbits);

ASN1STATUS PerEnByteAlign(Asn1Ctxt* ctxt);
ASN1STATUS PerDeByteAlign(Asn1Ctxt* ctxt);

ASN1STATUS PerEnBit(Asn1Ctxt* ctxt, ASN1BIT value);
ASN1STATUS PerDeBit(Asn1Ctxt* ctxt, ASN1BIT* value);

ASN1STATUS PerEnNumberBits(Asn1Ctxt* ctxt, ASN1UNUM value, ASN1UINT nbits);
ASN1STATUS PerDeNumberBits(Asn1Ctxt* ctxt, ASN1UNUM* value, ASN1UINT nbits);

ASN1STATUS PerEnBits(Asn1Ctxt* ctxt, Asn1ConstOctetPtr value, ASN1UINT nbits);
ASN1STATUS PerDeBits(Asn1Ctxt* ctxt, ASN1OCTET* value, ASN1UINT valueBuffLen, ASN1UINT nbits);


ASN1STATUS PerDeGetLength(Asn1Ctxt* ctxt, ASN1UINT *length, ASN1UINT numValueBits);

ASN1STATUS PerDeForwardBitCursor(Asn1Ctxt* ctxt, ASN1UINT bitOffset);


/* Encoding of a normally small non-negative whole number */
ASN1STATUS PerEnSmallNonNegWholeNumber(Asn1Ctxt* ctxt, ASN1UINT value);
ASN1STATUS PerDeSmallNonNegWholeNumber(Asn1Ctxt* ctxt, ASN1UINT *value);


/* Encoding a length */
ASN1STATUS PerEnConstrainedLength(Asn1Ctxt* ctxt, ASN1UINT relativeValue, ASN1UINT range);
ASN1STATUS PerDeConstrainedLength(Asn1Ctxt* ctxt, ASN1UINT* relativeValue, ASN1UINT range);

ASN1STATUS PerEnUnconstrainedLength(Asn1Ctxt* ctxt, ASN1UINT value, ASN1UINT *encodeValue, ASN1BOOL *fragmentFollowed);
ASN1STATUS PerDeUnconstrainedLength(Asn1Ctxt* ctxt, ASN1UINT* value, ASN1BOOL *fragmentFollowed);

ASN1STATUS PerEnLength(Asn1Ctxt* ctxt, ASN1UINT value, ASN1UINT *encodeValue, ASN1BOOL *fragmentFollowed);
ASN1STATUS PerDeLength(Asn1Ctxt* ctxt, ASN1UINT *value, ASN1BOOL *fragmentFollowed);

ASN1STATUS PerEnSmallLength(Asn1Ctxt* ctxt, ASN1UINT value);
ASN1STATUS PerDeSmallLength(Asn1Ctxt* ctxt, ASN1UINT* value);


/* Encoding as a non-negative-binary-integer */
ASN1STATUS PerEnNonNegBinIntBitField(Asn1Ctxt* ctxt, ASN1UNUM value, ASN1UINT nbits);
ASN1STATUS PerDeNonNegBinIntBitField(Asn1Ctxt* ctxt, ASN1UNUM *value, ASN1UINT nbits);

ASN1STATUS PerEnNonNegBinIntSingleOctet(Asn1Ctxt* ctxt, ASN1UNUM value);
ASN1STATUS PerDeNonNegBinIntSingleOctet(Asn1Ctxt* ctxt, ASN1UNUM *value);

ASN1STATUS PerEnNonNegBinIntDoubleOctet(Asn1Ctxt* ctxt, ASN1UNUM value);
ASN1STATUS PerDeNonNegBinIntDoubleOctet(Asn1Ctxt* ctxt, ASN1UNUM *value);

ASN1STATUS PerEnNonNegBinIntMinOctets(Asn1Ctxt* ctxt, ASN1UNUM value, ASN1UINT nOcts);
ASN1STATUS PerDeNonNegBinIntMinOctets(Asn1Ctxt* ctxt, ASN1UNUM *value, ASN1UINT nOcts);


/* Encoding of a constrained whole number */
ASN1STATUS PerEnConstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1UNUM relativeValue, ASN1UNUM range); 
ASN1STATUS PerDeConstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1UNUM* relativeValue, ASN1UNUM range); 

ASN1STATUS PerEnConstrainedInteger(Asn1Ctxt* ctxt, ASN1INT value, ASN1INT lower, ASN1INT upper);
ASN1STATUS PerDeConstrainedInteger(Asn1Ctxt* ctxt, ASN1INT* value, ASN1INT lower, ASN1INT upper);

ASN1STATUS PerEnConstrainedUnsigned(Asn1Ctxt* ctxt, ASN1UINT value, ASN1UINT lower, ASN1UINT upper);
ASN1STATUS PerDeConstrainedUnsigned(Asn1Ctxt* ctxt, ASN1UINT* value, ASN1UINT lower, ASN1UINT upper);

ASN1STATUS PerEnConstrainedUnsignedLongLong(Asn1Ctxt* ctxt, ASN1ULLONG value, ASN1ULLONG lower, ASN1ULLONG upper);
ASN1STATUS PerDeConstrainedUnsignedLongLong(Asn1Ctxt* ctxt, ASN1ULLONG* value, ASN1ULLONG lower, ASN1ULLONG upper);

ASN1STATUS PerEnConstrainedLongLong(Asn1Ctxt* ctxt, ASN1SLLONG value, ASN1SLLONG lower, ASN1SLLONG upper);
ASN1STATUS PerDeConstrainedLongLong(Asn1Ctxt* ctxt, ASN1SLLONG* value, ASN1SLLONG lower, ASN1SLLONG upper);


/* Encoding of a semi-constrained whole number */
ASN1STATUS PerEnSemiConstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1UNUM relativeValue); 
ASN1STATUS PerDeSemiConstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1UNUM* relativeValue); 

ASN1STATUS PerEnSemiConstrainedInteger(Asn1Ctxt* ctxt, ASN1INT value, ASN1INT lower);
ASN1STATUS PerDeSemiConstrainedInteger(Asn1Ctxt* ctxt, ASN1INT* value, ASN1INT lower);

ASN1STATUS PerEnSemiConstrainedUnsigned(Asn1Ctxt* ctxt, ASN1UINT value, ASN1UINT lower);
ASN1STATUS PerDeSemiConstrainedUnsigned(Asn1Ctxt* ctxt, ASN1UINT* value, ASN1UINT lower);


/* Encoding of a unconstrained whole number */
ASN1STATUS PerEnUnconstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1SNUM value);
ASN1STATUS PerDeUnconstrainedWholeNumber(Asn1Ctxt* ctxt, ASN1SNUM* value);

ASN1STATUS PerEnUnconstrainedInteger(Asn1Ctxt* ctxt, ASN1INT value);
ASN1STATUS PerDeUnconstrainedInteger(Asn1Ctxt* ctxt, ASN1INT* value);


/* Open type fields */
ASN1STATUS PerEnOpenType(Asn1Ctxt* ctxt, ASN1UINT nocts, Asn1ConstOctetPtr data);
ASN1STATUS PerDeOpenType(Asn1Ctxt* ctxt, ASN1UINT *nocts, Asn1ConstOctetPtr *data);


/* Encoding the bitstring type */
ASN1STATUS PerEnBitString(Asn1Ctxt* ctxt, ASN1UINT nbits, Asn1ConstOctetPtr data);
ASN1STATUS PerDeBitString(Asn1Ctxt* ctxt, ASN1UINT* nbits, ASN1OCTET* dataBuffer, ASN1UINT bufferSize);
ASN1STATUS PerDeDynamicBitString(Asn1Ctxt* ctxt, ASN1UINT* nbits, Asn1ConstOctetPtr *data);


/* Encoding the octetstring type */
ASN1STATUS PerEnOctetString(Asn1Ctxt* ctxt, ASN1UINT nocts, Asn1ConstOctetPtr data);
ASN1STATUS PerDeOctetString(Asn1Ctxt* ctxt, ASN1UINT* nocts, ASN1OCTET* dataBuffer, ASN1UINT bufferSize);
ASN1STATUS PerDeDynamicOctetString(Asn1Ctxt* ctxt, ASN1UINT* nocts, Asn1ConstOctetPtr *data);

ASN1STATUS IsDefultBitString(Asn1ConstOctetPtr pValData, ASN1UINT iSrcLen, Asn1ConstOctetPtr pDefData, ASN1UINT iDefLen);
ASN1STATUS SetBitStringDefaultValue(Asn1ConstOctetPtr pValData, Asn1ConstOctetPtr pDefData, ASN1UINT iDefLen);


/* Encoding the restricted character string types */
ASN1STATUS PerEnRestrictedCharacterString(Asn1Ctxt* ctxt, Asn1ConstCharPtr string, Asn1StringCharSet *charSet);
ASN1STATUS PerDeRestrictedCharacterString(Asn1Ctxt* ctxt, Asn1ConstCharPtr *string, Asn1StringCharSet *charSet);

ASN1STATUS PerEnPrintableString(Asn1Ctxt* ctxt, Asn1PrintableString string, Asn1ConstCharPtr permittedAlphabet);
ASN1STATUS PerDePrintableString(Asn1Ctxt* ctxt, Asn1PrintableString *string, Asn1ConstCharPtr permittedAlphabet);

ASN1STATUS PerEnAlignedOctets(Asn1Ctxt* ctxt, ASN1OCTET *pvalue, ASN1UINT nocts);
ASN1STATUS PerDeAlignedOctets(Asn1Ctxt* ctxt, ASN1OCTET* pbuffer, ASN1UINT bufsiz, ASN1UINT nocts);

ASN1UINT OctsCount(ASN1UNUM value);

#ifdef __cplusplus
}
#endif

#endif
