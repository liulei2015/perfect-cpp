#include "ft/feature/service/FtService.h"
#include "fw/ftest.h"
#include "l0-infra/base/BaseTypes.h"

FTESTING_NS_BEGIN

extern "C" void P_S_Service_Entry(WORD16 state, WORD16 eventId,
        void *msg,  void *data);

//
TEST(FtService, service_startup_ok)
{
    WORD16 state = 0;
    WORD16 eventId = 1;
    U32 msg = 2;
    U32 data = 3;

    P_S_Service_Entry(state, eventId, &msg, &data);
}

FTESTING_NS_END


