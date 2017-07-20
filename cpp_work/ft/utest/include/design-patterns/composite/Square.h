#ifndef INCL_UT_H4F89A9F6_D2EF_4706_8054_FEBEBB958348
#define INCL_UT_H4F89A9F6_D2EF_4706_8054_FEBEBB958348

#include "utest.h"
#include <design-patterns/composite/Shape.h>

UTESTING_NS_BEGIN

struct Square : Shape
{
    string draw() override;
};

UTESTING_NS_END

#endif
