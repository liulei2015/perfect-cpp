#ifndef INCL_UT_HD3EFB515_E4B6_4469_980B_9FEC15F8164F
#define INCL_UT_HD3EFB515_E4B6_4469_980B_9FEC15F8164F

#include "utest.h"
#include <micro-air-vehicle/validator/Validator.h>

UTESTING_NS_BEGIN


struct Collision : Validator
{
private:
    void onEvent(const MavInfo&) override;
    bool hasOccurred() const override;
private:
    bool occurred{false};
};

UTESTING_NS_END

#endif
