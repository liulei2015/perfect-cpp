#ifndef INCL_USI_H5F057151_1A7E_4255_8B41_8B4B360A380A
#define INCL_USI_H5F057151_1A7E_4255_8B41_8B4B360A380A

#include "l0-infra/base/usi.h"
#include <chrono>
#include <iostream>

USI_NS_BEGIN

//only for Ft ticker
struct TimeTicker
{
    typedef std::chrono::high_resolution_clock::time_point TimeType;

    void start()
    {
        startTicker = std::chrono::high_resolution_clock::now();
    }

    void stop(const char* positions)
    {
        endTicker = std::chrono::high_resolution_clock::now();
        std::cout << positions << " : " << std::chrono::duration_cast<std::chrono::microseconds>(endTicker - startTicker).count() << std::endl;
    }

private:
    TimeType startTicker;
    TimeType endTicker;
};

#define TICKER_START() \
TimeTicker ticker;        \
ticker.start();

#define TICKER_STOP(msg) ticker.stop(msg)

USI_NS_END

#endif
