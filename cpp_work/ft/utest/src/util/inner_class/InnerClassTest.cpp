#include "util/inner_class/InnerClass.h"
#include "utest.h"

UTESTING_NS_BEGIN

struct InnerClassTest : testing::Test
{
};


TEST_F(InnerClassTest, should_test_interface_ok)
{
    InnerClass innerClass;
    ASSERT_TRUE("rnluUeCtxtSrbCfgFail" == innerClass.getFailCause());
}


UTESTING_NS_END


