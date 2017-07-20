#include "utest.h"
#include "l0-infra/base/BaseTypes.h"

#include <iostream>

UTESTING_NS_BEGIN

struct OperatorTest : testing::Test
{
};

namespace
{
    const U32 INVALID_U32 = 0xffffffff;
    struct A
    {
        A() : value(INVALID_U32) {}
        U32 operator () (){return value;}
        explicit operator U32() {return value;}
    private:
        U32 value;
    };
}


TEST_F(OperatorTest, should_test_bracket_ok)
{
    A testA;
    ASSERT_TRUE(INVALID_U32 == testA());
    ASSERT_TRUE(INVALID_U32 == static_cast<U32>(testA));
}


UTESTING_NS_END





