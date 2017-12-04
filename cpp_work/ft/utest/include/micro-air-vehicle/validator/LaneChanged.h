#ifndef INCL_UT_HB4A1DDFE_B0A4_4DA8_B09B_C6EEBB1E2033
#define INCL_UT_HB4A1DDFE_B0A4_4DA8_B09B_C6EEBB1E2033

#include "utest.h"
#include <l0-infra/base/BaseTypes.h>
#include <micro-air-vehicle/validator/Validator.h>

UTESTING_NS_BEGIN


struct LaneChanged : Validator
{
private:
    void onEvent(const MavInfo&) override;
    bool hasOccurred() const override;
private:
    U32 currentLaneId;
    bool occurred{false};
};

UTESTING_NS_END

#endif
