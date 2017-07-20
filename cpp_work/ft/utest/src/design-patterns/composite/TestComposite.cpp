#include "utest.h"
#include "design-patterns/composite/Circle.h"
#include "design-patterns/composite/Square.h"
#include "design-patterns/composite/CompositeShape.h"

UTESTING_NS_BEGIN

struct TestComposite : testing::Test
{

};

TEST_F(TestComposite, should_test_simple_ok)
{
    Circle circle;
    Square square;
    Circle circle2;
    Square square2;
    CompositeShape compositeShape;
    compositeShape.add(&circle2);
    compositeShape.add(&square2);

    circle.draw();
    square.draw();
    compositeShape.draw();

    ASSERT_TRUE("Circle draw " == circle.draw());
    ASSERT_TRUE("Square draw " == square.draw());
    ASSERT_TRUE("Circle draw Square draw " == compositeShape.draw());
}


UTESTING_NS_END

