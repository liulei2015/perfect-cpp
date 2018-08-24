#include "utest.h"
#include <iostream>

using std::cout;
using std::endl;

UTESTING_NS_BEGIN

namespace
{

}

//template<typename T>
//void f(`参数类型` parm);

//参数类型可以是下面几种情况:
//1. T&
//2. const T&
//3. T&&
//4. T

struct TestEffectiveModernCpp : testing::Test
{
};


TEST_F(TestEffectiveModernCpp, item1_understand_template_type_deduction)
{
    ASSERT_TRUE(1 == 1);
}

UTESTING_NS_END










