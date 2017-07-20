#ifndef INCL_USI_AutoEquals_2013118185236_H__
#define INCL_USI_AutoEquals_2013118185236_H__

#include "l0-infra/base/PlainTransData.h"
#include "l0-infra/dci/InterfaceDef.h"
#include "l0-infra/trans-dsl/utils/ActionMacroHelper.h"

////////////////////////////////////////////////////////////////
#define __SMART_STRUCT_VALUE_ASSIGN(n)  m ## n = v.m ## n;
#define SMART_STRUCT_VALUE_ASSIGN(n) SIMPLE_REPEAT(n, __SMART_STRUCT_VALUE_ASSIGN)

////////////////////////////////////////////////////////////////
#define __SMART_STRUCT_MEMBER_DEF(n)  ACTION ## n  m ## n;
#define DECL_SMART_STRUCT_MEMBERS(n) SIMPLE_REPEAT(n, __SMART_STRUCT_MEMBER_DEF)

//////////////////////////////////////////////////////////////////////////
#define __SMART_STRUCT_EQ(n)       m ## n == rhs.m ## n
#define __SMART_STRUCT_EQS(n)      __SMART_STRUCT_EQ(n) &&

#define DECL_SMART_STRUCT_EQS(n) REPEAT(n, __SMART_STRUCT_EQS, __SMART_STRUCT_EQ)

    ////////////////////////////////////////////////////////////////
#define __SMART_STRUCT_PARTIAL_COLLECTION(n)                           \
    namespace details {                                                \
    template < DECL_TEMPLATE_ARGS(n)>                                  \
    struct SmartStructImpl __PARTIAL_30_##n(ACTION_ARGS, DUMMY_ARGS)   \
    {                                                                  \
       SmartStructImpl(){}                                             \
                                                                       \
       SmartStructImpl& operator=(const SmartStructImpl& v)            \
       {                                                               \
           SMART_STRUCT_VALUE_ASSIGN(n)                                \
           return *this;                                               \
       }                                                               \
                                                                       \
       bool operator==(const SmartStructImpl& rhs) const               \
       {                                                               \
           return DECL_SMART_STRUCT_EQS(n);                            \
       }                                                               \
                                                                       \
    private:                                                           \
       DECL_SMART_STRUCT_MEMBERS(n)                                    \
    };                                                                 \
    }

////////////////////////////////////////////////////////////////
__SMART_STRUCT_PARTIAL_COLLECTION(30)
__SMART_STRUCT_PARTIAL_COLLECTION(29)
__SMART_STRUCT_PARTIAL_COLLECTION(28)
__SMART_STRUCT_PARTIAL_COLLECTION(27)
__SMART_STRUCT_PARTIAL_COLLECTION(26)
__SMART_STRUCT_PARTIAL_COLLECTION(25)
__SMART_STRUCT_PARTIAL_COLLECTION(24)
__SMART_STRUCT_PARTIAL_COLLECTION(23)
__SMART_STRUCT_PARTIAL_COLLECTION(22)
__SMART_STRUCT_PARTIAL_COLLECTION(21)
__SMART_STRUCT_PARTIAL_COLLECTION(20)
__SMART_STRUCT_PARTIAL_COLLECTION(19)
__SMART_STRUCT_PARTIAL_COLLECTION(18)
__SMART_STRUCT_PARTIAL_COLLECTION(17)
__SMART_STRUCT_PARTIAL_COLLECTION(16)
__SMART_STRUCT_PARTIAL_COLLECTION(15)
__SMART_STRUCT_PARTIAL_COLLECTION(14)
__SMART_STRUCT_PARTIAL_COLLECTION(13)
__SMART_STRUCT_PARTIAL_COLLECTION(12)
__SMART_STRUCT_PARTIAL_COLLECTION(11)
__SMART_STRUCT_PARTIAL_COLLECTION(10)
__SMART_STRUCT_PARTIAL_COLLECTION(9)
__SMART_STRUCT_PARTIAL_COLLECTION(8)
__SMART_STRUCT_PARTIAL_COLLECTION(7)
__SMART_STRUCT_PARTIAL_COLLECTION(6)
__SMART_STRUCT_PARTIAL_COLLECTION(5)
__SMART_STRUCT_PARTIAL_COLLECTION(4)
__SMART_STRUCT_PARTIAL_COLLECTION(3)
__SMART_STRUCT_PARTIAL_COLLECTION(2)
__SMART_STRUCT_PARTIAL_COLLECTION(1)

USI_NS_BEGIN

#define __DEF_SMART_STRUCT(n)                              \
template < typename StructType                             \
         , DECL_DUMMY_DEFAULT(n) >                         \
struct SmartStruct                                         \
{                                                          \
    SmartStruct() {}                                       \
    SmartStruct(const StructType& value)                   \
    {                                                      \
       ::memcpy(&data, &value, sizeof(value));             \
    }                                                      \
                                                           \
    SmartStruct& operator=(const SmartStruct& rhs)         \
    {                                                      \
        data = rhs.data;                                   \
        return *this;                                      \
    }                                                      \
                                                           \
    StructType* operator->()                               \
    {                                                      \
        return reinterpret_cast<StructType*>(&data);       \
    }                                                      \
                                                           \
    const StructType* operator->() const                   \
    {                                                      \
        return reinterpret_cast<const StructType*>(&data); \
    }                                                      \
                                                           \
    friend bool operator==(const SmartStruct& lhs, const SmartStruct& rhs);  \
    friend bool operator!=(const SmartStruct& lhs, const SmartStruct& rhs);  \
                                                                             \
    details::SmartStructImpl<DECL_ALL_ARGS(n)> data;                         \
};                                                                           \
template < typename StructType, DECL_TEMPLATE_ARGS(n) >                      \
inline bool operator==                                                       \
    ( const SmartStruct<StructType, DECL_ALL_ARGS(n)>& lhs                   \
    , const SmartStruct<StructType, DECL_ALL_ARGS(n)>& rhs)                  \
{                                                                            \
    return lhs.data == rhs.data;                                             \
}                                                                            \
template < typename StructType, DECL_TEMPLATE_ARGS(n) >                      \
inline bool operator!=                                                       \
       ( const SmartStruct<StructType, DECL_ALL_ARGS(n)>& lhs                \
       , const SmartStruct<StructType, DECL_ALL_ARGS(n)>& rhs)               \
{                                                                            \
    return !(rhs == lhs);                                                    \
}

__DEF_SMART_STRUCT(30)

USI_NS_END

#endif

