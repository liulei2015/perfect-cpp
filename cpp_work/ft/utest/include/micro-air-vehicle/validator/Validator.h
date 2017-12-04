#ifndef INCL_UT_HF78B4C26_E991_40C4_A984_40076F0ED4AB
#define INCL_UT_HF78B4C26_E991_40C4_A984_40076F0ED4AB

#include "utest.h"

UTESTING_NS_BEGIN

struct Validator
{
    virtual void onEvent(const MavInfo&) = 0;
    virtual bool hasOccurred() const = 0;
    virtual ~Validator() {}
};

UTESTING_NS_END

#endif
