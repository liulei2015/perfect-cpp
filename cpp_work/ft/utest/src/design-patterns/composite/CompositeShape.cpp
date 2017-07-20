#include "design-patterns/composite/CompositeShape.h"

UTESTING_NS_BEGIN

void CompositeShape::add(Shape* shape)
{
    shapeContainer.push_back(shape);
}
string CompositeShape::draw()
{
    string result;
    for(auto &item : shapeContainer)
    {
        result += item->draw();
    }

    return result;
}



UTESTING_NS_END



