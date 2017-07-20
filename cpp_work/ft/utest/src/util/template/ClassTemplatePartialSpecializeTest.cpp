#include "utest.h"
#include "util/template/ClassTemplatePartialSpecialize.h"

UTESTING_NS_BEGIN

struct ClassTemplatePartialSpecializeTest : testing::Test
{
};


TEST_F(ClassTemplatePartialSpecializeTest, should_test_partial_special_ok)
{
    ClassTemplatePartialSpecialize<NormalBb, NormalRnlu> cfgActor;
    ClassTemplatePartialSpecialize<NormalBb, NormalRnlu, false> cfgActor2;
    ASSERT_TRUE(string("Cfg-BB-RNLU-RRU") == cfgActor.cfg());
    ASSERT_TRUE(string("Cfg-BB-RNLU") == cfgActor2.cfg());
}


UTESTING_NS_END





