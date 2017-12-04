#include "utest.h"
#include "gtest/gtest.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/base/Status.h"
#include "cpplinq/cpplinq.hpp"

UTESTING_NS_BEGIN

struct TestMicroAirVehicle : testing::Test
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

}

TEST_F(TestMicroAirVehicle, test_cpplinq_base)
{
    ASSERT_TRUE(1 == 1);
}




UTESTING_NS_END



