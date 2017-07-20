#include <l0-infra/event/concept/Event.h>
#include <l0-infra/base/Assertions.h>
#include "l0-infra/trans-dsl/sched//action/SchedSleepAction.h"
#include "l0-infra/trans-dsl/utils/RelativeTimer.h"
#include "l0-infra/dci/Unknown.h"
#include "l0-infra/trans-dsl/sched/concept/TimerInfo.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"

//////////////////////////////////////////////////////////////////////
Status SchedSleepAction::exec(TransactionContext& context)
{
   TimerInfo* timerInfo = dci::unknown_cast<TimerInfo>(&context);
   USI_ASSERT_VALID_PTR(timerInfo);

   USI_ASSERT_SUCC_CALL(ROLE(RelativeTimer).start(*timerInfo));

   return USI_CONTINUE;
}

//////////////////////////////////////////////////////////////////////
Status SchedSleepAction::handleEvent(TransactionContext&, const Event& event)
{
   if (ROLE(RelativeTimer).matches(event))
   {
      event.consume();
      ROLE(RelativeTimer).stop();
      return USI_SUCCESS;
   }

   return USI_UNKNOWN_EVENT;
}

//////////////////////////////////////////////////////////////////////
Status SchedSleepAction::stop(TransactionContext& context, const Status)
{
   ROLE(RelativeTimer).stop();

   return USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////
void SchedSleepAction::kill(TransactionContext& context, const Status)
{
   ROLE(RelativeTimer).stop();
}

