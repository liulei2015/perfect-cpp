#ifndef INCL_DCM_Table_H_
#define INCL_DCM_Table_H_

#include "l0-infra/mem-dbs/DbsElem.h"

struct TriggerMatcher;

struct Table : DbsElem
{
    OVERRIDE(Status load(void* param = 0));
    OVERRIDE(bool access(WORD16 eventId, void* req, void* ack) const);
    OVERRIDE(void dump() const);

private:
    bool verify(void* param) const;
    bool verifyTrigger(WORD16 triggerId) const;

private:
    USE_ROLE(DbsElem);
    USE_ROLE(TriggerMatcher);
};

#endif 

