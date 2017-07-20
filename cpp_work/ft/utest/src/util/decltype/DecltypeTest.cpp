#include "utest.h"
#include <type_traits>

UTESTING_NS_BEGIN

struct DecltypeTest : testing::Test
{
};

int i = 4;
int arr[5] = {0};
int * ptr = arr;
int && rvalRef();


TEST_F(DecltypeTest, should_test_infer_ok)
{
    ASSERT_TRUE(1 == std::is_rvalue_reference<decltype(rvalRef())>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype(true? i:i)>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype((i))>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype(++i)>::value);
    ASSERT_TRUE(0 == std::is_lvalue_reference<decltype(i++)>::value);
    ASSERT_TRUE(0 == std::is_rvalue_reference<decltype(i++)>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype(arr[0])>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype(*ptr)>::value);
    ASSERT_TRUE(1 == std::is_lvalue_reference<decltype("onlyStr")>::value);
}

UTESTING_NS_END



