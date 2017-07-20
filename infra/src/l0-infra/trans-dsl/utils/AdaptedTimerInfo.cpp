/*
 * AdaptedTimerInfo.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include "l0-infra/trans-dsl/utils/AdaptedTimerInfo.h"

AdaptedTimerInfo::AdaptedTimerInfo()
   : timerInfo(0)
{
}

WORD32 AdaptedTimerInfo::getTimerLen(const TimerId id, WORD32 para ) const
{
   return timerInfo == 0 ? 0 : timerInfo->getTimerLen(id, para);
}

void AdaptedTimerInfo::setTimerInfo(const TimerInfo* timerInfo)
{
   this->timerInfo = timerInfo;
}

