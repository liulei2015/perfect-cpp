/*
 * AdaptedTimerInfo.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ADAPTEDTIMERINFO_H_
#define ADAPTEDTIMERINFO_H_

#include "l0-infra/trans-dsl/sched/concept/TimerInfo.h"

struct AdaptedTimerInfo : TimerInfo
{
   AdaptedTimerInfo();

   OVERRIDE(WORD32 getTimerLen(const TimerId, WORD32 para = USI_INVALID_WORD32) const);

   void setTimerInfo(const TimerInfo* timerInfo);

private:
   const TimerInfo* timerInfo;
};

#endif /* ADAPTEDTIMERINFO_H_ */

