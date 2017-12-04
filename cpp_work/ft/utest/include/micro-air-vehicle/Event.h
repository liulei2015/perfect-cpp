#ifndef INCL_UT_H53CE7602_3A43_4092_B85F_DCD565A05164
#define INCL_UT_H53CE7602_3A43_4092_B85F_DCD565A05164

#include "utest.h"
#include <l0-infra/base/BaseTypes.h>

UTESTING_NS_BEGIN

struct Coordinate
{
    U32 x;
    U32 y;
    U32 z;
};

struct MavInfo
{
    U32 id;
    U32 high;
    U32 speed;
    Coordinate coordinate;
    U32 distanceWithCommander;
    U32 distanceWithNearestMav;
    bool isCollided;
    BYTE pad[3];
};

UTESTING_NS_END

#endif
