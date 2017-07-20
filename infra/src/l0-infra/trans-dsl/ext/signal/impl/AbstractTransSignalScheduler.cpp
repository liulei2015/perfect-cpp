#include "l0-infra/trans-dsl/ext/signal/impl/AbstractTransSignalScheduler.h"
#include "l0-infra/base/Assertions.h"

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
AbstractTransSignalScheduler::AbstractTransSignalScheduler() : signalBitmap(0)
{
}

//////////////////////////////////////////////////////////////////////////
#define BITMASK(signal) (1 << signal)

//////////////////////////////////////////////////////////////////////////
Status AbstractTransSignalScheduler::broadcast(const TransSignalId id)
{
    USI_ASSERT_TRUE(id <= sizeof(signalBitmap) * 8);

    signalBitmap |= BITMASK(id);

    return USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
TransSignalId AbstractTransSignalScheduler::doFetchSignal()
{
    for(BYTE i=0; i < sizeof(TransSignalId) * 8; i++)
    {
        if(signalBitmap & (WORD32)(1<<i))
        {
            signalBitmap &= ~(WORD32)(1<<i);
            return i;
        }
    }

    return 0xFF;
}

USI_NS_END
