/*
 * RelativeTimer.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/utils/RelativeTimer.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/sched/concept/TimerInfo.h"
#include "l0-infra/base/Assertions.h"

Status RelativeTimer::start(const TimerInfo& info)
{
   stop();

   WORD32 len = info.getTimerLen(timerId, timerParam);

   USI_ASSERT_SUCC_CALL(actualStartTimer(timerId, len, timerParam));

   started = true;

   return USI_SUCCESS;
}
