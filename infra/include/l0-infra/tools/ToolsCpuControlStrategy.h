#ifndef INCL_USI_H135B25BE_3F5A_4DD1_A750_780B719DF5B6
#define INCL_USI_H135B25BE_3F5A_4DD1_A750_780B719DF5B6

#include "l0-infra/base/BaseTypes.h"

struct ToolsCpuControlStrategy
{
    static BYTE getCurrentCpuLevel();

    static bool shouldReportMdt();
    static bool shouldReportCdt();
    static bool shouldReportSignalTraceBy(BYTE direction);
    static bool shouldReportTraceMe();
    static bool shouldReportCt();
    static bool shouldReportImsiTrace();
};

#endif
