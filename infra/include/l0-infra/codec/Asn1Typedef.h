#ifndef ASN1_TYPEDEF
#define ASN1_TYPEDEF

//#include "l0-infra/base/pub_devicedef.h"

#ifdef __cplusplus
#define INLINE  inline
#else
#define INLINE
#endif

typedef char                    ASN1SBIT8;
typedef unsigned char           ASN1UBIT8;
typedef short                   ASN1SBIT16;
typedef unsigned short          ASN1UBIT16;
typedef int                     ASN1SBIT32;
typedef unsigned int            ASN1UBIT32;
typedef long long               ASN1SBIT64;
typedef unsigned long long      ASN1UBIT64;


typedef ASN1UBIT8               ASN1OCTET;
typedef ASN1SBIT64              ASN1SNUM;
typedef ASN1UBIT64              ASN1UNUM;

#define ASN1UNUM_MAX            (unsigned long long)0xffffffffffffffffull
#define ASN1SNUM_MAX            (long long)0x7fffffffffffffffll
#define ASN1SNUM_MIN            (long long)0x8000000000000000ll

typedef unsigned char           ASN1BIT;
typedef unsigned char           ASN1BYTE;
typedef char                    ASN1CHAR;
typedef unsigned char           ASN1BOOL;
typedef short                   ASN1SHORT;
typedef unsigned short          ASN1USHORT;
typedef int                     ASN1INT;
typedef unsigned int            ASN1UINT;
typedef void                    ASN1VOID;
typedef void*                   ASN1ANY;
typedef unsigned long long      ASN1ULLONG;
typedef long long               ASN1SLLONG;
typedef double                  ASN1REAL;

#ifdef WIN32  //#ifndef _RELAY_UE_CPS_BASE_TYPE_DEF_
typedef unsigned short      WORD16;
typedef signed short        SWORD16;
typedef unsigned long       WORD32;
typedef signed long         SWORD32;
typedef unsigned long       OSS_STATUS;

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
#endif

//// 区分CCE 和 CC16
//#if (_LOGIC_BOARD ==_LOGIC_CCE||_LOGIC_BOARD ==_LOGIC_CCE1 || _LOGIC_BOARD  == _LOGIC_CBBM_MAIN)
//    // CCE的代码
//    #define MAX_CODEC_THREAD_NUM      6   // 跟业务相关的最大调度线程数目(业务占用的核数目) 【CCE0 功能添加】
//#else
//    // CC16的代码
//    #define MAX_CODEC_THREAD_NUM      1   // 跟业务相关的最大调度线程数目(业务占用的核数目) 【CCE0 功能添加】
//#endif

#define ASN1_BIT0                           (ASN1BIT)0
#define ASN1_BIT1                           (ASN1BIT)1

#define ASN1UINT_MAX                        4294967295U
#define ASN1INT_MAX                         2147483647L
#define ASN1INT_MIN                         (-ASN1INT_MAX-1)


typedef unsigned int            ASN1STATUS;

#define ASN1_OK                             (ASN1UINT)0
#define ASN1_E_NO_USER_MEM                  (ASN1UINT)1
#define ASN1_E_NO_SYS_MEM                   (ASN1UINT)2
#define ASN1_E_END_OF_CODE_BUF              (ASN1UINT)3
#define ASN1_E_CODE_BUFF_OVERFLOW           (ASN1UINT)4
#define ASN1_E_INVALID_RANGE                (ASN1UINT)5
#define ASN1_E_SMALL_LENGTH_TOO_LARGE       (ASN1UINT)6
#define ASN1_E_CONSTRAINT_VIOLATION         (ASN1UINT)7
#define ASN1_E_NO_DECODE_MEM                (ASN1UINT)8
#define ASN1_E_STRING_OVERFLOW              (ASN1UINT)9
#define ASN1_E_INVALID_ENUM                 (ASN1UINT)10
#define ASN1_E_INVALID_OPTIONAL             (ASN1UINT)11
#define ASN1_E_INVALID_OBJECT_IDENTIFIER    (ASN1UINT)12
#define ASN1_E_BAD_VALUE                    (ASN1UINT)13
#define ASN1_E_INVALID_LENGTH               (ASN1UINT)14
#define ASN1_I_UNKNOWN_EXTEND               (ASN1UINT)15
#define ASN1_E_ENC_EMPTY_OBJSET             (ASN1UINT)16
#define ASN1_E_MISS_MANDATORY_IE            (ASN1UINT)17
#define ASN1_E_IE_DUPLICATE                 (ASN1UINT)18 
#define ASN1_E_UNKNOWN                      (ASN1UINT)0xFFFF

#define ASN1_K_EXTENUM   999

typedef const char*             Asn1ConstCharPtr;
typedef const char              Asn1ConstChar;
typedef const int               Asn1ConstInt;
typedef unsigned char*    Asn1ConstOctetPtr;
typedef unsigned char     Asn1ConstOctet;


#define ASN1_NULL                           (ASN1ANY)0
#define ASN1_TRUE                           (ASN1BOOL)1
#define ASN1_FALSE                          (ASN1BOOL)0


#define ASN1_ALIGNED                        (ASN1BOOL)ASN1_TRUE
#define ASN1_UNALIGNED                      (ASN1BOOL)ASN1_FALSE


#define ASN1_MIN(a, b)    (((a) < (b)) ? (a) : (b))

typedef Asn1ConstCharPtr    Asn1PrintableString;

#define ASN1_PRINTABLE_CHAR_ALIGNED_BITS         8
#define ASN1_PRINTABLE_CHAR_UNALIGNED_BITS       7
#define ASN1_PRINTABLE_CHAR_MAX_VALUE_BITS       7
#define ASN1_PRINTABLE_CHAR_SET_SIZE             74
#define ASN1_PRINTABLE_CHAR_SET   \
    " '()+,-./0123456789:=?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

typedef struct tagAsn1RestrictedCharStringInfo
{
    ASN1BYTE            alignedBits;
    ASN1BYTE            unlignedBits;
    ASN1BYTE            maxValueBits;
    ASN1USHORT          permittedAlphabetSize;
    ASN1CHAR*           permittedAlphabet;
}Asn1StringCharSet;

typedef struct tagAsn1OpenType
{
    ASN1UINT            nocts;
    Asn1ConstOctetPtr   data;
}Asn1OpenType;

typedef struct Asn1DynamicBitString
{
	ASN1UINT            nbits;
	Asn1ConstOctetPtr   data;
}Asn1DynamicBitString;

typedef struct Asn1DynamicOctetString
{
    ASN1UINT            nocts;
    Asn1ConstOctetPtr   data;
}Asn1DynamicOctetString;
#endif

