#ifndef INCL_USI_Dbs_AccessorHelper_H_
#define INCL_USI_Dbs_AccessorHelper_H_

#include "l0-infra/mem-dbs/Accessor.h"
#include "l0-infra/mem-dbs/ParamHandler.h"
#include "l0-infra/dci/Role.h"

namespace details
{
    template<WORD16 EVENT_ID, typename REQ, typename ACK, typename PARAM_HANDLER = ParamHandler, bool IS_CONTINUE = true>
    struct ACCESSOR__ : Accessor<REQ, ACK, IS_CONTINUE>
    {
    private:
        WORD16 getEventId() const
        {
            return EVENT_ID;
        }

        IMPL_ROLE_WITH_VAR(ParamHandler, PARAM_HANDLER);
    };
}

//////////////////////////////////////////////////////////////////////////

#define __accessor(...)   ::details::ACCESSOR__< __VA_ARGS__ >

#endif

