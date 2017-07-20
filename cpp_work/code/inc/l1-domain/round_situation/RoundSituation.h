#ifndef INCL_SERVICE_HA5CD62D1_E97D_49DE_97AA_9827091324C6
#define INCL_SERVICE_HA5CD62D1_E97D_49DE_97AA_9827091324C6

#include "l0-infra/base/Service.h"
#include "l0-infra/base/BaseTypes.h"

SERVICE_NS_BEGIN


struct RoundSituation
{
    RoundSituation() : liveNum(0) {}
    RoundSituation(U32 liveNum)
        : liveNum(liveNum) {}

    U32 getLiveNum() {return liveNum;}
private:
    U32 liveNum;
};


SERVICE_NS_END

#endif
