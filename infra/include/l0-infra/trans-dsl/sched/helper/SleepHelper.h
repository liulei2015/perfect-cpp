/*
 * SleepHelper.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SLEEPHELPER_H_
#define SLEEPHELPER_H_

#include "l0-infra/trans-dsl/sched/action/SchedSleepAction.h"
#include "l0-infra/trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h"

namespace details
{
   template<TimerId TIMER_ID>
   struct SLEEP__: SchedSleepAction
   {
      SLEEP__() : timer(TIMER_ID)
      {
      }

   private:
      mutable PlatformSpecifiedRelativeTimer timer;
      ROLE_PROTO_TYPE(RelativeTimer)
      {
         return timer;
      }
   };

    #define TIMER_PARA_NO_31  (WORD16)31

   template<WORD32 TIMER_PARA>
   struct SLEEP__PARA: SchedSleepAction
   {
       SLEEP__PARA() : timer(TIMER_PARA_NO_31, TIMER_PARA)
       {
       }

   private:
       mutable PlatformSpecifiedRelativeTimer timer;
       ROLE_PROTO_TYPE(RelativeTimer)
       {
           return timer;
       }
   };
}

///////////////////////////////////////////////////////////////////
#define __sleep(tid) \
    ::details::SLEEP__<tid>

#define __sleep_para(para) \
    ::details::SLEEP__PARA<para>

///////////////////////////////////////////////////////////////////

#endif /* SLEEPHELPER_H_ */

