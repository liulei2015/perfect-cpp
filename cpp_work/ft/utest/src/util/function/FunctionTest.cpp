#include "utest.h"
#include <functional>

UTESTING_NS_BEGIN

struct FunctionTest : testing::Test
{
};

std::function<int(int)> Functional;

int whoAmI(int a)
{
    return a;
}

auto lambdaWhoAmI = [](int a) -> int {return a;};

struct Functor
{
    int operator()( int a)
    {
        return a;
    }
};

struct ClassWhoAmI
{
    int whoAmI(int a) {return a;}
    static int staticWhoAmI(int a) {return a;}
};


TEST_F(FunctionTest, should_test_wrapper_function_ok)
{
    int testValue = 20;

    Functional = whoAmI;
    ASSERT_TRUE(testValue == Functional(testValue));

    Functional = lambdaWhoAmI;
    ASSERT_TRUE(testValue == Functional(testValue));

    Functor functor;
    Functional = functor;
    ASSERT_TRUE(testValue == Functional(testValue));

    ClassWhoAmI classWhoAmI;
    Functional = std::bind(&ClassWhoAmI::whoAmI, classWhoAmI, std::placeholders::_1);
    ASSERT_TRUE(testValue == Functional(testValue));

    Functional = ClassWhoAmI::staticWhoAmI;
    ASSERT_TRUE(testValue == Functional(testValue));

}

UTESTING_NS_END






