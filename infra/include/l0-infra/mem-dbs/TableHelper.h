#ifndef INCL_USI_TableHelper_H_
#define INCL_USI_TableHelper_H_

#include "l0-infra/mem-dbs/Table.h"
#include "l0-infra/mem-dbs/TriggerMatcher.h"

namespace details
{
    struct VoidTriggerMatcher : TriggerMatcher
    {
        OVERRIDE(bool isMatched(WORD16 triggerId) const)
        {
            return false;
        }
    };

    template<typename T_DBS_ELEM, typename T_TRIGGER_MATCHER = VoidTriggerMatcher>
    struct TABLE__ : Table
    {
    private:
        IMPL_ROLE_WITH_VAR(DbsElem, T_DBS_ELEM);
        IMPL_ROLE_WITH_VAR(TriggerMatcher, T_TRIGGER_MATCHER);
    };

}

//////////////////////////////////////////////////////////////////////////

#define __table(...)    ::details::TABLE__< __VA_ARGS__ >

#endif 

