#include "design-patterns/composite/Circle.h"
#include <iostream>

UTESTING_NS_BEGIN


string Circle::draw()
{
    std::cout << "Circle draw ..." << std::endl;
    return "Circle draw ";
}


UTESTING_NS_END

