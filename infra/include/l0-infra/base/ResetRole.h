#ifndef INCL_USI_ResetRole_H__
#define INCL_USI_ResetRole_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/Status.h"

USI_NS_BEGIN

DEFINE_ROLE(ResetRole)
{
    virtual Status reset() = 0;
};

USI_NS_END

#endif

