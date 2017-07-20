/*
 * TimerInfo.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TIMERINFO_H_
#define TIMERINFO_H_

#include <l0-infra/dci/InterfaceDef.h>
#include <l0-infra/base/BaseTypes.h>
#include "l0-infra/trans-dsl/sched/concept/TimerId.h"
#include "l0-infra/base/Status.h"

DEF_INTERFACE(TimerInfo, 1304241634)
{
   ABSTRACT(WORD32 getTimerLen(const TimerId, WORD32 para = USI_INVALID_WORD32) const);
};

#endif /* TIMINGINFO_H_ */

