#ifndef INCL_USI_STATUS_H
#define INCL_USI_STATUS_H

#include "l0-infra/base/usi.h"

//////////////////////////////////////////////////////////////////////////
typedef unsigned int __uint32__t_;

#ifndef Status
typedef __uint32__t_ Status;
#endif

#define DEF_SIMPLE_STATUS(status, value) \
	const Status status = value

#define DEF_STATUS(status, value) \
	DEF_SIMPLE_STATUS(USI_##status, value);	\
	DEF_SIMPLE_STATUS(DCM_##status, value);	\
	DEF_SIMPLE_STATUS(CCM_##status, value); \
	DEF_SIMPLE_STATUS(CPM_##status, value)

//////////////////////////////////////////////////////////////////////////
#define DEF_SUCC_STATUS(status, value)   DEF_STATUS(status, value)

DEF_SUCC_STATUS(SUCCESS,           0);
DEF_SUCC_STATUS(CONTINUE,          1);
DEF_SUCC_STATUS(UNKNOWN_EVENT,     2);
DEF_SUCC_STATUS(RESTART_REQUIRED,  3);
DEF_SUCC_STATUS(STOP,              4);

//////////////////////////////////////////////////////////////////////////
#define __FAILED_STATUS_VALUE(value) (0x80000000 | (value))
#define DEF_SIMPLE_FAILED_STATUS(status, value)   \
	DEF_SIMPLE_STATUS(status, __FAILED_STATUS_VALUE(value))
#define DEF_FAILED_STATUS(status, value)  \
	DEF_STATUS(status, __FAILED_STATUS_VALUE(value))

DEF_FAILED_STATUS(FAILED,          0);
DEF_FAILED_STATUS(FATAL_BUG,       1);
DEF_FAILED_STATUS(TIMEDOUT,        2);
DEF_FAILED_STATUS(DUPTID,          3);
DEF_FAILED_STATUS(OUT_OF_SCOPE,    4);
DEF_FAILED_STATUS(FORCE_STOPPED,   5);
DEF_FAILED_STATUS(NOTHING_CHANGED, 6);
DEF_FAILED_STATUS(INVALID_DATA,    7);
DEF_FAILED_STATUS(INVALID_PROTOCAL_IE, 11);

DEF_FAILED_STATUS(RESERVED_FAILURE, 0x7FFFFFFF);

//////////////////////////////////////////////////////////////////////////
const Status __MIN_FAILED_STATUS = 0x10;

#define IS_FAILED_STATUS(status) ((status) >= __MIN_FAILED_STATUS)
#define IS_SUCC_STATUS(status) (!IS_FAILED_STATUS(status))

//////////////////////////////////////////////////////////////////////////
#define DEF_INVALID_VALUE(type, name, value)   \
	const type USI_##name=value;   \
	const type DCM_##name=value;   \
	const type CCM_##name=value;   \
	const type CPM_##name=value;

DEF_INVALID_VALUE(__uint32__t_, INVALID_WORD32, 0xFFFFFFFF);
DEF_INVALID_VALUE(unsigned long long, INVALID_WORD64, 0xFFFFFFFFFFFFFFFFLL);
DEF_INVALID_VALUE(unsigned short, INVALID_WORD, 0xFFFF);
DEF_INVALID_VALUE(unsigned short, INVALID_WORD16, USI_INVALID_WORD);
DEF_INVALID_VALUE(unsigned char, INVALID_BYTE, 0xFF);
DEF_INVALID_VALUE(char, INVALID_SCHAR, 0xFF);
DEF_INVALID_VALUE(signed int, INVALID_SWORD32, 0x7FFFFFFF);

#if defined(TRUE)
#undef TRUE
#endif
#define TRUE    1

#if defined(FALSE)
#undef FALSE
#endif
#define FALSE   0

#endif

