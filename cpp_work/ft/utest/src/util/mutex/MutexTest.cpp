#include "utest.h"
#include <string>
#include <thread>
#include <mutex>

UTESTING_NS_BEGIN

struct MutexTest : testing::Test
{
};

volatile int counter(0);
std::mutex mtx;
const int Compute_Times = 10000;

void attempt_10k_increase()
{
    for(int i = 0; i < Compute_Times; ++i)
    {
        std::lock_guard<std::mutex > lckg(mtx);
        ++counter;
    }
}

TEST_F(MutexTest, should_run_concurrently_ok)
{
    const int Thread_Num = 10;
    std::thread threads[Thread_Num];

    for(int i = 0; i < Thread_Num; ++i)
        threads[i] = std::thread(attempt_10k_increase);

    for(auto& item : threads)
        item.join();

    ASSERT_TRUE( Thread_Num*Compute_Times == counter);
}

UTESTING_NS_END



