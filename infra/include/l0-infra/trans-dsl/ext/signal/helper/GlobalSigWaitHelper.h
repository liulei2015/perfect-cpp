#ifndef INCL_USI_GlobalSigWaitHelper_2013095135541_H__
#define INCL_USI_GlobalSigWaitHelper_2013095135541_H__

#include "l0-infra/trans-dsl/ext/signal/action/SchedGlobalSigWaitAction.h"

namespace details
{
    template<TransSignalId V_SIGNAL_ID>
    struct GLOBAL_SIG_WAIT__: SchedGlobalSigWaitAction
    {
    private:
        OVERRIDE(TransSignalId getGlobalSignalId())
        {
            return V_SIGNAL_ID;
        }
    };
}

/////////////////////////////////////////////////////////
#define __global_sig_wait(signal) ::details::GLOBAL_SIG_WAIT__<signal>
/////////////////////////////////////////////////////////

#endif

