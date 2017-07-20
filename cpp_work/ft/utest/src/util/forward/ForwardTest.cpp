#include "util/inner_class/InnerClass.h"
#include "utest.h"
#include <string>

UTESTING_NS_BEGIN

struct ForwardTest : testing::Test
{
};

std::string runCode(int && m) {return "rvalue ref";}
std::string runCode(int & m) {return "lvalue ref";}
std::string runCode(const int && m) {return "const rvalue ref";}
std::string runCode(const int & m) {return "const lvalue ref";}

template<typename T>
std::string perfectForward(T && t)
{
    return runCode(std::forward<T>(t));
}

TEST_F(ForwardTest, should_test_trans_ok)
{
    int a;
    int b;
    const int c = 1;
    const int d = 0;

    ASSERT_TRUE("lvalue ref" == perfectForward(a));
    ASSERT_TRUE("rvalue ref" == perfectForward(std::move(b)));
    ASSERT_TRUE("const lvalue ref" == perfectForward(c));
    ASSERT_TRUE("const rvalue ref" == perfectForward(std::move(d)));
}


UTESTING_NS_END


