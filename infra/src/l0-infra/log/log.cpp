#include "l0-infra/log/log.h"
#include "l0-infra/base/stdio_ng.h"
#include <stdarg.h>
#include <string.h>

extern "C" const char* getBaseName(const char* absPath)
{
    if (absPath == 0) return "";

    const char* p = absPath + strlen(absPath);
    while ((p != absPath) && (*(p - 1) != SEPERATOR))
    {
        p--;
    }

    return p;
}


