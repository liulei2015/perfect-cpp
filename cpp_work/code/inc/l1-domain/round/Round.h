#ifndef INCL_SERVICE_HD08C3CB7_D89D_4E09_9DEB_0A70415102F7
#define INCL_SERVICE_HD08C3CB7_D89D_4E09_9DEB_0A70415102F7

#include "l0-infra/base/Service.h"
#include "l1-domain/round_situation/RoundSituation.h"

SERVICE_NS_BEGIN


struct Round
{
    Round() {}
    Round(const RoundSituation& situation) : situation(situation) {}

    U32 getLiveNum() {return situation.getLiveNum();}
private:
    RoundSituation situation;
};


SERVICE_NS_END

#endif
