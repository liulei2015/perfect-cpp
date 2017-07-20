#ifndef INCL_USI_HB2017D35_6858_491C_853D_CDA93F7B642F
#define INCL_USI_HB2017D35_6858_491C_853D_CDA93F7B642F

#include "l0-infra/base/Status.h"

USI_NS_BEGIN

template<typename T>
struct AllocatorVisitor
{
    virtual Status visit(T&) = 0;
    virtual ~AllocatorVisitor(){}
};

template<typename T>
struct ConstAllocatorVisitor
{
    virtual Status visit(const T&)= 0;
    virtual ~ConstAllocatorVisitor(){}
};

USI_NS_END

#endif

