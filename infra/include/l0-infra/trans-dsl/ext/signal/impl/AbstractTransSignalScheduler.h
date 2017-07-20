#ifndef INCL_USI_AbstractTransSignalScheduler_2013095140216_H__
#define INCL_USI_AbstractTransSignalScheduler_2013095140216_H__

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/trans-dsl/ext/signal/concept/TransSignalScheduler.h"
#include "l0-infra/base/Likely.h"

USI_NS_BEGIN

struct AbstractTransSignalScheduler 
    : TransSignalScheduler
{
    AbstractTransSignalScheduler();

    TransSignalId fetchSignal()
    {
        if(__likely(signalBitmap == 0)) return 0xFF;

        return doFetchSignal();
    }

private:
    OVERRIDE(Status broadcast(const TransSignalId));
    TransSignalId doFetchSignal();

protected:
    WORD32 signalBitmap; 
};

USI_NS_END

#endif

