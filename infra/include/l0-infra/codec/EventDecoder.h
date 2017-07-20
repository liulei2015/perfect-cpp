#ifndef INCL_USI_CODEC_EVENT_DECODER_H
#define INCL_USI_CODEC_EVENT_DECODER_H

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/event/concept/EventId.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

struct EventInfo;

USI_NS_BEGIN

DEFINE_ROLE(EventUpdater)
{
    virtual void updateEvent(const EventId&, const void* const msg) = 0;
    virtual void updateEvent(const EventId&, const void* const orignal, const void* const decoded) = 0;
};

DEFINE_ROLE(EventDecoder)
{
    virtual Status decodeTo(const InstanceId iid, const EventInfo& eventInfo, 
                            BYTE* decodeBuff, WORD16 decodeBufSize, EventUpdater& updater) = 0;
};


USI_NS_END

#endif

