#include "l0-infra/base/BaseTypes.h"

struct LogModule
{
	LogModule() :name(NULL),curLogLevel(0){};
    LogModule(const char *module) : name(module), curLogLevel(1){}
    virtual ~LogModule() {}
    bool isLogLevelEnable(BYTE logLevel);
    virtual void setCurLogLevel(BYTE logLevel);
    const char *name;
protected:
    BYTE curLogLevel;
};

