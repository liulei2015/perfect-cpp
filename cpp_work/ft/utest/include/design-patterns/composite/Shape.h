#ifndef INCL_UT_H30FF7F9A_B947_43FF_913F_2E8CAB5700CC
#define INCL_UT_H30FF7F9A_B947_43FF_913F_2E8CAB5700CC

#include "utest.h"
#include "l0-infra/dci/Role.h"
#include <string>

using std::string;

UTESTING_NS_BEGIN

DEFINE_ROLE(Shape)
{
    virtual string draw() = 0;
};


UTESTING_NS_END

#endif
