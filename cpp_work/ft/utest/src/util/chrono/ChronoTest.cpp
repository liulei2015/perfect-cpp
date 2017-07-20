#include "utest.h"
#include <ratio>
#include <chrono>
#include <iostream>
#include <ctime>

using namespace std::chrono;

UTESTING_NS_BEGIN

struct ChronoTest : testing::Test
{
};


TEST_F(ChronoTest, should_test_duration_ok)
{
    typedef duration<int> seconds_type;
    typedef duration<int, std::milli> milliseconds_type;
    typedef duration<int, std::ratio<60*60>> hours_type;

    hours_type h_oneday (24);
    seconds_type s_oneday (24*60*60);
    milliseconds_type ms_oneday (s_oneday);

    seconds_type s_onehour (60*60);
    hours_type h_onehour (duration_cast<hours_type>(s_onehour));

    ASSERT_TRUE(86400000 == ms_oneday.count());
    ASSERT_TRUE(1 == h_onehour.count());
}

TEST_F(ChronoTest, should_test_time_point_ok)
{
    time_point<system_clock, duration<int>> tp_seconds (duration<int>(1));

    system_clock::time_point tp (tp_seconds);

    std::time_t tt = system_clock::to_time_t(tp);
    std::cout << "time_point tp is : " << ctime(&tt);

    typedef duration<int, std::ratio<24*60*60>> days_type;

    time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());

    std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
    std::time_t today_time = system_clock::to_time_t(today);
    std::cout << "today_time is : " << ctime(&today_time);

    const int OneBillion = 1000000000;
    ASSERT_TRUE(OneBillion == tp.time_since_epoch().count());
}

TEST_F(ChronoTest, should_test_clock_ok)
{
    typedef duration<int, std::ratio<24*60*60>> days_type;
    days_type one_day(1);

    system_clock::time_point today = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;

    days_type expect = duration_cast<days_type>(tomorrow - today);

    ASSERT_TRUE(1 == expect.count());
}

UTESTING_NS_END





