#ifndef INCL_USI_H61EE1110_00D2_4B72_9992_E27FDFC7B17E
#define INCL_USI_H61EE1110_00D2_4B72_9992_E27FDFC7B17E

#include "l0-infra/base/BaseTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

bool isTraceMeSwitchOn();
void setTraceMeSwitch(BYTE flag);

bool isDebugTraceSwitchOn();
void setDebugTraceSwitch(BYTE flag);

#ifdef __cplusplus
}
#endif

#ifdef USI_FT
#define CHECK_TRACE_ME_SWITCH()
#else
#define CHECK_TRACE_ME_SWITCH() if(!isTraceMeSwitchOn()) return
#endif


#endif
