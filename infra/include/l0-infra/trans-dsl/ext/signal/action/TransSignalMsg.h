#ifndef INCL_USI_TransSignalMsg_2013095134742_H__
#define INCL_USI_TransSignalMsg_2013095134742_H__

#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalId.h"
#include "l0-infra/event/concept/EventId.h"


const EventId EV_GLOBAL_TRANS_SIGNAL = 0xFFFC;

struct TransSignalMsg
{
    TransSignalMsg(const TransSignalId& signal) 
        : signal(signal) 
    {}
    
    TransSignalId signal;
};

#endif

