#ifndef INCL_USI_RwLock_H_
#define INCL_USI_RwLock_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/dci/Role.h"

DEFINE_ROLE(RwLock)
{
    ABSTRACT(INT rLock() const);
    ABSTRACT(INT wLock() const);
    ABSTRACT(INT unLock() const);
};

#endif

