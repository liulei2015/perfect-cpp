#include "utest.h"

UTESTING_NS_BEGIN

struct TestAdapter : testing::Test
{

};

TEST_F(TestAdapter, should_test_simple_ok)
{

    ASSERT_TRUE(1 == 1);

}


UTESTING_NS_END



