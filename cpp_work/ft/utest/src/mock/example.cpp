//#include "utest.h"
//#include "gtest/gtest.h"
//#include "l0-infra/base/Keywords.h"
//#include "mockcpp/mockcpp.hpp"
//#include "l0-infra/base/Status.h"
//#include "l0-infra/util/ServiceHelper.h"
//#include <l0-infra/base/BaseTypes.h>
//#include "l0-infra/event/impl/ConsecutiveEventInfo.h"
//
//
//extern "C" void P_S_Service_Entry(WORD16 state, WORD16 eventId,
//     void *msg,  void *data);
//
//UTESTING_NS_BEGIN
//
//struct TestMock : testing::Test
//{
//    protected:
//    virtual void doSetUp()
//    {}
//
//    virtual void doTearDown()
//    {
//        GlobalMockObject::verify();
//    }
//
//    OVERRIDE(void SetUp()){doSetUp();}
//    OVERRIDE(void TearDown()){doTearDown();}
//};
//
//namespace
//{
//    typedef struct
//    {
//        int a;
//        int b;
//    }STRUCT_T;
//
////    struct Interface
////    {
////        static U32 method(STRUCT_T *p)
////        {
////            return 0;
////        }
////    };
//
//    U32 invoke()
//    {
//        return 0;
//    }
//
//    bool is_the_second_member_2(STRUCT_T *p)
//    {
//        if (p->b == 2)
//        {
//            return true;
//        }
//        return false;
//    }
//
//    STRUCT_T input{1,2};
//
//    void mockFunc()
//    {
//        MOCKER(invoke)
//              .stubs()
//              .will(returnValue((U32)0));
//    }
//}
//
//TEST_F(TestMock, given_gotMoData_when_saveMoDataFail_then_getAgain)
//{
////    mockFunc();
////    invoke();
//}
//
//UTESTING_NS_END
//
//
//
