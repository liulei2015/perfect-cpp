#ifndef INCL_USI_GlobalSigBroadcastHelper_2013095135832_H__
#define INCL_USI_GlobalSigBroadcastHelper_2013095135832_H__

#include "l0-infra/trans-dsl/ext/signal/action/SchedGlobalBroadcastAction.h"

namespace details
{
    template<TransSignalId V_SIGNAL_ID>
    struct GLOBAL_BROADCAST__: SchedGlobalBroadcastAction
    {
    private:
        OVERRIDE(TransSignalId getGlobalSignalId())
        {
            return V_SIGNAL_ID;
        }
    };
}

/////////////////////////////////////////////////////////
#define __global_broadcast(signal) ::details::GLOBAL_BROADCAST__<signal>
/////////////////////////////////////////////////////////

#endif

