#ifndef INCL_UT_H37F95B6E_5543_47C8_8015_B90B78603036
#define INCL_UT_H37F95B6E_5543_47C8_8015_B90B78603036

#include "utest.h"
#include <design-patterns/composite/Shape.h>
#include <vector>

using std::vector;

UTESTING_NS_BEGIN

struct CompositeShape : Shape
{
    void add(Shape* shape);
    string draw();
private:
    vector<Shape*> shapeContainer;
};


UTESTING_NS_END

#endif
