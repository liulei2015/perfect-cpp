#ifndef INCL_USI_H8A713E8A_796E_49D7_81F4_C4614BECD9C7
#define INCL_USI_H8A713E8A_796E_49D7_81F4_C4614BECD9C7

#include "l0-infra/dci/Role.h"
#include "l0-infra/event/concept/EventId.h"
#include "l0-infra/base/BaseTypes.h"

USI_NS_BEGIN

DEFINE_ROLE(TransMsgDiscard)
{
    void discard(WORD16 eventId)
    {
        doDiscard(eventId);
    }

private:
    ABSTRACT(void doDiscard(EventId eventId));
};

#define  DECL_TRANS_EVNET_DEQUEUE()                             \
    private:                                                    \
const TransMsgDiscard* discard;                                 \
public:                                                         \
    void setTransMachineDiscard(const TransMsgDiscard* discard) \
    {                                                           \
        this->discard = discard;                                \
    }                                                           \
    const TransMsgDiscard* getTransMachineDiscard() const       \
    {                                                           \
        return discard;                                         \
    }

USI_NS_END

#endif
