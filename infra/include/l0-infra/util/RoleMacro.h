#ifndef INCL_USI_COMMON_ROLE_MACRO_H
#define INCL_USI_COMMON_ROLE_MACRO_H

#include "l0-infra/base/Status.h"
#include "l0-infra/dci/Role.h"
#include "l0-infra/dci/Role.h"

#define DEF_CFG_ROLE(LocalSubSysCfgRole, Role, Builder)                      \
DEFINE_ROLE(Role)                                                            \
{                                                                            \
    Status config()                                                          \
    {                                                                        \
        return ROLE(LocalSubSysCfgRole).config(ROLE(Builder));               \
    }                                                                        \
                                                                             \
    AsyncRole& getAsyncRole()                                                \
    {                                                                        \
        return ROLE(LocalSubSysCfgRole).getAsyncRole();                      \
    }                                                                        \
private:                                                                     \
    USE_ROLE(LocalSubSysCfgRole);                                            \
    USE_ROLE(Builder);                                                       \
}

#endif

