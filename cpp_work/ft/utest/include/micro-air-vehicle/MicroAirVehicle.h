#ifndef INCL_UT_H335946D6_219A_40B0_AC0F_BFB9F212A8D1
#define INCL_UT_H335946D6_219A_40B0_AC0F_BFB9F212A8D1

#include "utest.h"

UTESTING_NS_BEGIN


struct MicroAirVehicle
{
    void processEvent(const MavInfo&);
    bool hasCollided();
    bool hasLaneChangedWhenLineFlying();
private:
    bool isCollided{false};
    bool isLaneChanged{false};
    Coordinate currentCoordinate{0,0,0};
};

UTESTING_NS_END

#endif
