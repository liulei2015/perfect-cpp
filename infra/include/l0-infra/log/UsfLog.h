#include "l0-infra/log/log.h"

#ifdef USI_TRACE
#undef USI_TRACE
#endif
                          
#define USI_TRACE(level, format, ...) \
    UNI_LOG(USF_MODULE, level, format, ##__VA_ARGS__)
