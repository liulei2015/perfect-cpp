/*
 * RelativeTimer.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RELATIVETIMER_H_
#define RELATIVETIMER_H_

#include "l0-infra/trans-dsl/sched/concept/TimerId.h"
#include <l0-infra/base/Status.h>
#include <l0-infra/base/Keywords.h>
#include <l0-infra/base/BaseTypes.h>
#include "l0-infra/event/concept/Event.h"

struct Event;
struct TimerInfo;

struct RelativeTimer
{
   RelativeTimer(const TimerId timerId, const WORD32 timerParam)
      : timerId(timerId)
      , started(false)
      , timerParam(timerParam)
   {
   }

   Status start(const TimerInfo&);

   void stop()
   {
      if(!started) return;
      actualStopTimer(timerId, timerParam);
   }

   bool matches(const Event& event) const
   {
       return started && isTimerEvent(event, timerId) && paraMatch(event);
   }

   bool paraMatch(const Event& event) const
   {
       return timerParam == USI_INVALID_WORD32 || *(WORD32*)(event.getMsg()) == timerParam;
   }

   virtual ~RelativeTimer() {}

private:
   const TimerId timerId;
   bool started;
   const WORD32  timerParam;

private:
   ABSTRACT(bool isTimerEvent(const Event&, const TimerId) const);
   ABSTRACT(Status actualStartTimer(const TimerId, WORD32 timerLen, WORD32 timerParam));
   ABSTRACT(void actualStopTimer(const TimerId, WORD32 timerParam));
};

#endif /* RELATIVETIMER_H_ */

