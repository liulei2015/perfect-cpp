#ifndef INCL_DCM_H8A713E8A_796E_49D7_81F4_C5614AECD8C7
#define INCL_DCM_H8A713E8A_796E_49D7_81F4_C5614AECD8C7

#include "l0-infra/dci/Role.h"
#include "l0-infra/event/concept/EventId.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/event/concept/EventInfo.h"

USI_NS_BEGIN

DEFINE_ROLE(TransMsgSelected)
{
	EventInfo* select(WORD16 eventId)
    {
        return selectMsg(eventId);
    }

private:
    ABSTRACT(EventInfo* selectMsg(EventId eventId));
};

#define  DECL_TRANS_EVNET_SEQUEUE()                             \
    private:                                                    \
const TransMsgSelected* selectMsg;                                 \
public:                                                         \
    void setTransMachineSelected(const TransMsgSelected* selectMsg) \
    {                                                           \
        this->selectMsg = selectMsg;                                \
    }                                                           \
    const TransMsgSelected* getTransMachineSelected() const       \
    {                                                           \
        return selectMsg;                                         \
    }

USI_NS_END

#endif

