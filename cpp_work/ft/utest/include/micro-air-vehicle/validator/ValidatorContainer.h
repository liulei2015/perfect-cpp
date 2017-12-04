#ifndef INCL_UT_HD012C91A_CE08_4FE4_BE50_8D86E25CF3B7
#define INCL_UT_HD012C91A_CE08_4FE4_BE50_8D86E25CF3B7

#include "utest.h"
#include <micro-air-vehicle/validator/Validator.h>
#include <list>

UTESTING_NS_BEGIN

struct ValidatorContainer : Validator
{
    void addValidator(const Validator&);
private:
    void onEvent(const MavInfo&) override;
    bool hasOccurred() const override;
private:
    std::list<Validator*> validators;
};

UTESTING_NS_END

#endif
