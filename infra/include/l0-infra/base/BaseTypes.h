#ifndef INCL_USI_BASE_BASE_TYPES_H
#define INCL_USI_BASE_BASE_TYPES_H

#include <stddef.h>
#include "l0-infra/base/usi.h"

typedef unsigned char  BYTE;
typedef unsigned char  UCHAR;
typedef char CHAR;
typedef int  INT;
typedef short SHORT;
typedef int LONG;

typedef float               FLOAT;
typedef double            DOUBLE;


typedef unsigned short WORD;
typedef unsigned short WORD16;
typedef signed short   SWORD16;

typedef unsigned int  DWORD;
typedef DWORD          WORD32;
typedef signed int    SWORD32;

typedef int BOOL;

#ifdef WIN32
typedef __int64          SWORD64;
typedef unsigned __int64 WORD64;
#else
typedef unsigned long long WORD64;
#endif

typedef unsigned char   BOOLEAN;

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef unsigned long  U64;

typedef signed char  S8;
typedef signed short S16;
typedef signed int   S32;
typedef signed long  S64;
typedef unsigned char       Oct;

#define USI_PRESENT (BYTE)1
#define USI_ABSENT  (BYTE)0

#define CCM_PRESENT (BYTE)1
#define CCM_ABSENT  (BYTE)0

#define DCM_PRESENT (BYTE)1
#define DCM_ABSENT  (BYTE)0

#ifndef Status
typedef unsigned int   Status;
#endif

#ifndef VOID
#define VOID void
#endif

#endif

