#ifndef INCL_USI_DbsElem_H_
#define INCL_USI_DbsElem_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/dci/Role.h"

DEFINE_ROLE(DbsElem)
{
    ABSTRACT(Status load(void* param = 0));
    ABSTRACT(bool access(WORD16 eventId, void* req, void* ack) const);
    ABSTRACT(void dump() const);
};

#endif

