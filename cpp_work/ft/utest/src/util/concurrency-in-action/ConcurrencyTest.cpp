#include "util/inner_class/InnerClass.h"
#include "utest.h"
#include <string>
#include <iostream>
#include <thread>

UTESTING_NS_BEGIN

namespace
{
    void hello()
    {
        std::cout<<"Hello Concurrent World\n";
    }
}

struct ConcurrencyTest : testing::Test
{
};

TEST_F(ConcurrencyTest, should_test_trans_ok)
{
    std::thread t(hello);
    t.join();

    ASSERT_TRUE(0 == 0);
}


UTESTING_NS_END







