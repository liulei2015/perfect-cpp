#ifndef INCL_USI_TransMsgSender_H_
#define INCL_USI_TransMsgSender_H_

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/event/impl/ConsecutiveEventInfo.h"
#include "l0-infra/event/concept/Event.h"

USI_NS_BEGIN

DEFINE_ROLE(TransMsgSender)
{
    Status send(WORD16 eventId);

    template <typename MSG_TYPE>
    Status send(WORD16 eventId, const MSG_TYPE& msg)
    {
        return doBuffer(ConsecutiveEventInfo(eventId, msg));
    }

    Status send(const Event& event)
    {
        return doBuffer(event);
    }

private:
    ABSTRACT(Status doBuffer(const Event& event));
};

#define  DECL_TRANS_EVNET_INQUEUE()                         \
    private:                                                \
const TransMsgSender* sender;                               \
public:                                                     \
    void setTransMachineSender(const TransMsgSender* sender)\
    {                                                       \
        this->sender = sender;                              \
    }                                                       \
    const TransMsgSender* getTransMachineSender() const     \
    {                                                       \
        return sender;                                      \
    } 


USI_NS_END

#endif 

