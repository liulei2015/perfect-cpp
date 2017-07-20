#ifndef INCL_USI_HF8B47900_3CB5_415D_9C87_F364623F5F51
#define INCL_USI_HF8B47900_3CB5_415D_9C87_F364623F5F51

#include "l0-infra/base/Status.h"
#include "l0-infra/base/Likely.h"
#include "l0-infra/base/NullPtr.h"
#include "l0-infra/log/UsfLog.h"

#define __ASSERT_LOG__    ERR_LOG
#define __EXPECT_LOG__    WARN_LOG
#define __PEEK_LOG__      WARN_LOG

#define __void__
#define __nothing__

#define __USI_PREDICATE_TRUE(exp, action, log)      \
do{                                                 \
    if(__unlikely(!(exp)))                          \
    {                                               \
        log("assertion failed: " #exp);             \
        action;                                     \
    }                                               \
}while(0)

//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_TRUE_R(exp, result)  __USI_PREDICATE_TRUE(exp, return result, __ASSERT_LOG__)
#define USI_ASSERT_TRUE(exp)            USI_ASSERT_TRUE_R(exp, USI_FAILED)
#define USI_ASSERT_TRUE_VOID(exp)       USI_ASSERT_TRUE_R(exp, __void__)
#define USI_ASSERT_TRUE_NIL(exp)        USI_ASSERT_TRUE_R(exp, __null_ptr__)
#define USI_ASSERT_TRUE_BOOL(exp)       USI_ASSERT_TRUE_R(exp, false)

//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_FALSE_R(exp, result)  USI_ASSERT_TRUE_R(!(exp), result)
#define USI_ASSERT_FALSE(exp)            USI_ASSERT_TRUE(!(exp))
#define USI_ASSERT_FALSE_VOID(exp)       USI_ASSERT_TRUE_VOID(!(exp))
#define USI_ASSERT_FALSE_NIL(exp)        USI_ASSERT_TRUE_NIL(!(exp))
#define USI_ASSERT_FALSE_BOOL(exp)       USI_ASSERT_TRUE_BOOL(!(exp))

//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_VALID_PTR_R(ptr, result)  USI_ASSERT_TRUE_R(__notnull__(ptr), result)
#define USI_ASSERT_VALID_PTR(ptr)            USI_ASSERT_TRUE(__notnull__(ptr))
#define USI_ASSERT_VALID_PTR_VOID(ptr)       USI_ASSERT_TRUE_VOID(__notnull__(ptr))
#define USI_ASSERT_VALID_PTR_NIL(ptr)        USI_ASSERT_TRUE_NIL(__notnull__(ptr))
#define USI_ASSERT_VALID_PTR_BOOL(ptr)       USI_ASSERT_TRUE_BOOL(__notnull__(ptr))

//////////////////////////////////////////////////////////////////////////
#define USI_EXPECT_TRUE_R(exp, result)  __USI_PREDICATE_TRUE(exp, return result, __EXPECT_LOG__)
#define USI_EXPECT_TRUE(exp)            USI_EXPECT_TRUE_R(exp, USI_SUCCESS)
#define USI_EXPECT_TRUE_VOID(exp)       USI_EXPECT_TRUE_R(exp, __void__)
#define USI_EXPECT_TRUE_NIL(exp)        USI_EXPECT_TRUE_R(exp, __null_ptr__)
#define USI_EXPECT_TRUE_BOOL(exp)       USI_EXPECT_TRUE_R(exp, false)

//////////////////////////////////////////////////////////////////////////
#define USI_EXPECT_FALSE_R(exp, result)  USI_EXPECT_TRUE_R(!(exp), result)
#define USI_EXPECT_FALSE(exp)            USI_EXPECT_TRUE(!(exp))
#define USI_EXPECT_FALSE_VOID(exp)       USI_EXPECT_TRUE_VOID(!(exp))
#define USI_EXPECT_FALSE_NIL(exp)        USI_EXPECT_TRUE_NIL(!(exp))
#define USI_EXPECT_FALSE_BOOL(exp)       USI_EXPECT_TRUE_BOOL(!(exp))

//////////////////////////////////////////////////////////////////////////
#define USI_EXPECT_VALID_PTR_R(ptr, result)  USI_EXPECT_TRUE_R(__notnull__(ptr), result)
#define USI_EXPECT_VALID_PTR(ptr)            USI_EXPECT_TRUE(__notnull__(ptr))
#define USI_EXPECT_VALID_PTR_VOID(ptr)       USI_EXPECT_TRUE_VOID(__notnull__(ptr))
#define USI_EXPECT_VALID_PTR_NIL(ptr)        USI_EXPECT_TRUE_NIL(__notnull__(ptr))
#define USI_EXPECT_VALID_PTR_BOOL(ptr)       USI_EXPECT_TRUE_BOOL(__notnull__(ptr))

//////////////////////////////////////////////////////////////////////////
#define USI_PEEK_TRUE(exp)       __USI_PREDICATE_TRUE(exp, __nothing__, __PEEK_LOG__)
#define USI_PEEK_FALSE(exp)      USI_PEEK_TRUE(!(exp))
#define USI_PEEK_VALID_PTR(ptr)  USI_PEEK_TRUE(__notnull__(ptr))

//////////////////////////////////////////////////////////////////////////
#define __USI_PREDICATE_SUCC_CALL(call, action, log) \
do{                                                  \
    Status __status__ = call;                        \
    if(__unlikely(__status__ != USI_SUCCESS))        \
    {                                                \
        log(#call" = [%X]", __status__);             \
        action;                                      \
    }                                                \
}while(0)

//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_SUCC_CALL_R(call, result) __USI_PREDICATE_SUCC_CALL(call, return result, __ASSERT_LOG__)
#define USI_ASSERT_SUCC_CALL(call)           USI_ASSERT_SUCC_CALL_R(call, __status__)
#define USI_ASSERT_SUCC_CALL_VOID(call)      USI_ASSERT_SUCC_CALL_R(call, __void__)
#define USI_ASSERT_SUCC_CALL_NIL(call)       USI_ASSERT_SUCC_CALL_R(call, __null_ptr__)
#define USI_ASSERT_SUCC_CALL_BOOL(call)      USI_ASSERT_SUCC_CALL_R(call, false)

//////////////////////////////////////////////////////////////////////////
#define USI_EXPECT_SUCC_CALL_R(call, result) __USI_PREDICATE_SUCC_CALL(call, return result, __EXPECT_LOG__)
#define USI_EXPECT_SUCC_CALL(call)           USI_EXPECT_SUCC_CALL_R(call, __status__)
#define USI_EXPECT_SUCC_CALL_VOID(call)      USI_EXPECT_SUCC_CALL_R(call, __void__)
#define USI_EXPECT_SUCC_CALL_NIL(call)       USI_EXPECT_SUCC_CALL_R(call, __null_ptr__)
#define USI_EXPECT_SUCC_CALL_BOOL(call)      USI_EXPECT_SUCC_CALL_R(call, false)

//////////////////////////////////////////////////////////////////////////
#define USI_PEEK_SUCC_CALL(call)  __USI_PREDICATE_SUCC_CALL(call, __nothing__, __PEEK_LOG__)

//////////////////////////////////////////////////////////////////////////
// Note: don't add more finally assert macro
//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_TRUE_FINALLY_R(exp, finally, result) __USI_PREDICATE_TRUE(exp, finally; return result, __ASSERT_LOG__)
#define USI_ASSERT_TRUE_FINALLY(exp, finally)      USI_ASSERT_TRUE_FINALLY_R(exp, finally, USI_FAILED)
#define USI_ASSERT_FALSE_FINALLY(exp, finally)     USI_ASSERT_TRUE_FINALLY(!(exp), finally)
#define USI_ASSERT_VALID_PTR_FINALLY(ptr, finally) USI_ASSERT_TRUE_FINALLY((__notnull__(ptr)), finally)
#define USI_ASSERT_VALID_PTR_FINALLY_R(ptr, finally, result) USI_ASSERT_TRUE_FINALLY_R((__notnull__(ptr)), finally, result)

//////////////////////////////////////////////////////////////////////////
#define USI_ASSERT_SUCC_CALL_FINALLY_R(call, finally, result) __USI_PREDICATE_SUCC_CALL(call, finally; return result, __ASSERT_LOG__)
#define USI_ASSERT_SUCC_CALL_FINALLY(call, finally) USI_ASSERT_SUCC_CALL_FINALLY_R(call, finally, __status__)

//////////////////////////////////////////////////////////////////////////
#define __USI_ASSERT_NO_REAL_FAIL(call, action, log)      \
do {                                                      \
    Status __status = call;                               \
    if(__unlikely(__status == USI_NOTHING_CHANGED))       \
    {                                                     \
        return USI_SUCCESS;                               \
    }                                                     \
    else if (__unlikely(__status != USI_SUCCESS))         \
    {                                                     \
        log(#call" = [%X]", __status);                    \
        action;                                           \
    }                                                     \
} while (0)

#define USI_ASSERT_NO_REAL_FAIL(call)       \
    __USI_ASSERT_NO_REAL_FAIL(call, return __status, __ASSERT_LOG__)

#define IS_NIL(ptr) ((ptr) == __null_ptr__)

#endif
