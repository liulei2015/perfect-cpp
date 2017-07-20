#ifndef INCL_IgnoreRspHelper_H_
#define INCL_IgnoreRspHelper_H_

#include "l0-infra/trans-dsl/sched/action/SchedIgnoreRspAction.h"

namespace details
{
    template <typename T_ACTION>
    struct IGNORE_RSP__ : SchedIgnoreRspAction
    {
    private:
        IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
    };
}

#define __ignore_rsp(action) ::details::IGNORE_RSP__< action >

#endif 

