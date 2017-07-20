#ifndef _INCL_USI_DcmInstPostProcessHandler_20131108155112_H_
#define _INCL_USI_DcmInstPostProcessHandler_20131108155112_H_

#include "l0-infra/base/usi.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"
#include "l0-infra/event/concept/Event.h"
#include "StateId.h"
#include "l0-infra/dci/Role.h"

USI_NS_BEGIN

DEFINE_ROLE(PostProcessHandler)
{
   DEFAULT(void, onPostProcess(const InstanceId iid, const Event& event, const StateId sid) const);
};

USI_NS_END


#endif

