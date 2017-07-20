#include "utest.h"
#include "gtest/gtest.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/base/Status.h"
#include "cpplinq/cpplinq.hpp"

UTESTING_NS_BEGIN

struct TestCppLinq : testing::Test
{
protected:
    virtual void doSetUp()
    {}

    virtual void doTearDown()
    {}

    OVERRIDE(void SetUp()){doSetUp();}
    OVERRIDE(void TearDown()){doTearDown();}
};

namespace
{
    int computes_sum()
    {
        using namespace cpplinq;
        int numbers[] = {3,1,4,1,5,9,2,6,5,4};

        auto result = from_array(numbers)
                          >>where ([](int i) {return i%2 == 0;})
                          >>sum();

        return result;
    }

    const int EXPECTED_SUM = 16;
}

TEST_F(TestCppLinq, test_cpplinq_base)
{
    ASSERT_TRUE(computes_sum() == EXPECTED_SUM);
}




UTESTING_NS_END



