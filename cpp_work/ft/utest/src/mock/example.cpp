// #include "utest.h"
// #include "gtest/gtest.h"
// #include "l0-infra/base/Keywords.h"
// #include "mockcpp/mockcpp.hpp"
// #include "l0-infra/base/Status.h"
// #include "l0-infra/util/ServiceHelper.h"
// #include "l0-infra/event/impl/ConsecutiveEventInfo.h"


// extern "C" void P_S_Service_Entry(WORD16 state, WORD16 eventId,
//         void *msg,  void *data);

// UTESTING_NS_BEGIN

// struct TestMock : testing::Test
// {
// protected:
//     virtual void doSetUp()
//     {}

//     virtual void doTearDown()
//     {}

//     OVERRIDE(void SetUp()){doSetUp();}
//     OVERRIDE(void TearDown()){doTearDown();}
// };

// namespace
// {
// 	void mockSaveMoDataFail()
// 	{
// 		MOCKER(saveMoAccessRsp)
// 				. expects(once())
// 				. with(any())
// 				. will(returnValue(USI_FAILED));
// 	}
// }

// TEST_F(TestMock, given_gotMoData_when_saveMoDataFail_then_getAgain)
// {
//     mockSaveMoDataFail();

//     WORD16 state = 0;
//     WORD16 eventId = 1;
//     U32 msg = 2;
//     U32 data = 3;

//     P_S_Service_Entry(state, eventId, &msg, &data);
// }




// UTESTING_NS_END



