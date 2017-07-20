#include "design-patterns/composite/Square.h"
#include <iostream>

UTESTING_NS_BEGIN

string Square::draw()
{
    std::cout << "Square draw ..." << std::endl;
    return "Square draw ";
}

UTESTING_NS_END


