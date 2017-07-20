/*
 * PlatformSpecifiedRelativeTimer.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PLATFORMSPECIFIEDRELATIVETIMER_H_
#define PLATFORMSPECIFIEDRELATIVETIMER_H_

#include "l0-infra/trans-dsl/utils/RelativeTimer.h"

struct PlatformSpecifiedRelativeTimer : RelativeTimer
{
   PlatformSpecifiedRelativeTimer(const TimerId timerId, const WORD32 timerParam);
   PlatformSpecifiedRelativeTimer(const TimerId timerId);

private:
   OVERRIDE(bool isTimerEvent(const Event&, const TimerId) const);
   OVERRIDE(Status actualStartTimer(const TimerId, WORD32 timerLen, WORD32 timerParam));
   OVERRIDE(void actualStopTimer(const TimerId, WORD32 timerParam));
};

#endif /* PLATFORMSPECIFIEDRELATIVETIMER_H_ */

