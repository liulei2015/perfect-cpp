#ifndef INCL_USI_VerifyAddr_H
#define INCL_USI_VerifyAddr_H

#include "l0-infra/base/BaseTypes.h"

inline bool verifyAddr(const BYTE* addr, const BYTE numocts)
{
    return numocts > 0 && addr != 0;
}

#endif
