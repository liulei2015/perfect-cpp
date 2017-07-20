#include "utest.h"
#include <future>
#include <iostream>
#include <chrono>
#include <thread>

UTESTING_NS_BEGIN

struct FutureTest : testing::Test
{
};

int distance(int from, int to)
{
    return from - to;
}

TEST_F(FutureTest, should_test_future_get_async_result_ok)
{
    std::packaged_task<int(int, int)> task(distance);

    std::future<int> future_result = task.get_future();

    std::thread th(std::move(task), 10, 0);

    int ret = future_result.get();

    th.join();

    ASSERT_TRUE(10 == ret);
}


UTESTING_NS_END


