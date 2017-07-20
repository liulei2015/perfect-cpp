/*
 * TimerProtHelper.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#ifndef TIMERPROTHELPER_H_
#define TIMERPROTHELPER_H_

#include "l0-infra/trans-dsl/sched/action/SchedTimerProtAction.h"

namespace details
{

   template<TimerId TIMER_ID, typename T_ACTION, Status TIMEOUT_STATUS= USI_TIMEDOUT>
   struct TIMER_PROT__
            : SchedTimerProtAction
   {
      TIMER_PROT__() : SchedTimerProtAction(c_action, TIMER_ID, USI_INVALID_WORD32) {}

   private:
       T_ACTION c_action;
      //IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);

      OVERRIDE(Status getTimeoutStatus() const)
      {
         return TIMEOUT_STATUS;
      }
   };

    template<TimerId TIMER_ID, typename T_ACTION, Status TIMEOUT_STATUS= USI_TIMEDOUT>
    struct TIMER_PROT__1
             : SchedTimerProtAction
    {
       TIMER_PROT__1() : SchedTimerProtAction(c_action, TIMER_ID, 1) {}

    private:
        T_ACTION c_action;
       //IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);

       OVERRIDE(Status getTimeoutStatus() const)
       {
          return TIMEOUT_STATUS;
       }
    };

    template<TimerId TIMER_ID, typename T_ACTION, Status TIMEOUT_STATUS= USI_TIMEDOUT>
    struct TIMER_PROT__2
           : SchedTimerProtAction
    {
     TIMER_PROT__2() : SchedTimerProtAction(c_action, TIMER_ID, 2) {}

    private:
      T_ACTION c_action;
     //IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);

     OVERRIDE(Status getTimeoutStatus() const)
     {
        return TIMEOUT_STATUS;
     }
    };

   #define TIMER_PARA_NO_31  (WORD16)31

   template<WORD32 TIMER_PARA, typename T_ACTION, Status TIMEOUT_STATUS= USI_TIMEDOUT>
   struct TIMER_PROT__PARA
          : SchedTimerProtAction
   {
    TIMER_PROT__PARA() : SchedTimerProtAction(c_action, TIMER_PARA_NO_31, TIMER_PARA) {}

   private:
     T_ACTION c_action;

    OVERRIDE(Status getTimeoutStatus() const)
    {
       return TIMEOUT_STATUS;
    }
   };
}

///////////////////////////////////////////////////////////////////////
#define __timer_prot(...) \
    ::details::TIMER_PROT__< __VA_ARGS__ >

#define __timer_prot_1(...) \
    ::details::TIMER_PROT__1< __VA_ARGS__ >

#define __timer_prot_2(...) \
    ::details::TIMER_PROT__2< __VA_ARGS__ >

#define __timer_para_prot(...) \
    ::details::TIMER_PROT__PARA< __VA_ARGS__ >

///////////////////////////////////////////////////////////////////////
#endif /* TIMERPROTHELPER_H_ */

