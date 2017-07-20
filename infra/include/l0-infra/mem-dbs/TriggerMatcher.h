#ifndef INCL_USI_TriggerMatcher_H_
#define INCL_USI_TriggerMatcher_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/dci/Role.h"

DEFINE_ROLE(TriggerMatcher)
{
    ABSTRACT(bool isMatched(WORD16 triggerId) const);
};

#endif 

