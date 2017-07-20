#include "l0-infra/log/TraceMeSwitch.h"

namespace
{
    BYTE on = 1;
    BYTE off = 0;
    BYTE traceMeSwitch = on;
    BYTE debugTraceSwitch = off;
}

extern "C" bool isTraceMeSwitchOn()
{
    return traceMeSwitch == on;
}

extern "C" void setTraceMeSwitch(BYTE flag)
{
    traceMeSwitch = flag > 0 ? on : off;
}

extern "C" bool isDebugTraceSwitchOn()
{
    return debugTraceSwitch == on;
}

extern "C" void setDebugTraceSwitch(BYTE flag)
{
    debugTraceSwitch = flag > 0 ? on : off;
}
