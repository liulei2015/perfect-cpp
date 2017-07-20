#include "utest.h"

UTESTING_NS_BEGIN

struct TestStrategy : testing::Test
{

};

TEST_F(TestStrategy, should_test_simple_ok)
{

    ASSERT_TRUE(1 == 1);
}


UTESTING_NS_END



