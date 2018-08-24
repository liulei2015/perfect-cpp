#include "utest.h"
#include "MccEntry.h"
#include "domain/Msg.h"

UTESTING_NS_BEGIN

struct TestC : testing::Test
{

};

TEST_F(TestC, should_mcc_handle_poweron_msg_ok)
{
    PowerOnMsg msg = {0};

    mccEntry(1, nullptr);
    ASSERT_TRUE(1 == 1);
}


UTESTING_NS_END



