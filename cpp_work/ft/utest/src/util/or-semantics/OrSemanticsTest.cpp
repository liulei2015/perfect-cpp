#include "utest.h"
#include <l0-infra/base/BaseTypes.h>


UTESTING_NS_BEGIN


namespace
{
	#define USI_SUCCESS 0
	#define USI_CONTINUE 1
	#define USI_FAILED   2

    bool needReportPb = true;
    bool needReportTimeout = false;

	U32 reportPb(const U32 event)
	{
		if(needReportPb)
		{
			printf(" %s \n", "report Pb sigTrace");
			return USI_SUCCESS;
		}
		else
		{
			printf(" not %s \n", "report Pb sigTrace");
			return USI_FAILED;
		}
	}

	U32 reportTimeout(const U32 event)
	{
		if(needReportTimeout)
		{
			printf(" %s \n", "report Timeout sigTrace");
			return USI_SUCCESS;
		}
		else
		{
			printf(" not %s \n", "report Timeout sigTrace");
			return USI_FAILED;
		}
	}

    typedef U32 (*reportFunc)(const U32);

    template<reportFunc Func1, reportFunc Func2>
    U32 __or__(const U32 event)
    {
    	if(Func1(event) == USI_SUCCESS)
    	{
    		return 1;
    	}
    	else
    	{
    		Func2(event);
    		return 2;
    	}

    }

    U32 reportSigTrace(const U32 event)
	{
		return __or__<reportPb,
				      reportTimeout>(event);
	}



}

struct OrSemanticsTest : testing::Test
{

};


TEST_F(OrSemanticsTest, should_test_op_ok)
{

    ASSERT_TRUE(1 == reportSigTrace(0));
}


UTESTING_NS_END








