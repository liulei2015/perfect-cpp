#ifndef INCL_UT_H4EC65DF4_4AE1_48F3_8DF4_E9689C8F0C33
#define INCL_UT_H4EC65DF4_4AE1_48F3_8DF4_E9689C8F0C33

#include "utest.h"
#include <design-patterns/composite/Shape.h>

UTESTING_NS_BEGIN

struct Circle : Shape
{
    string draw() override;
};

UTESTING_NS_END

#endif
