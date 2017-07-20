/*
 * ActionHelper.h
 *
 * Created on: Apr 24, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONHELPER_H_
#define ACTIONHELPER_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"

namespace details
{
   template <typename T_ASYN_ACTION>
   struct ASYN__ : SchedAction
   {
       OVERRIDE(Status exec(TransactionContext& context))
       {
           action.reset();
           return action.exec(context);
       }

       OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
       {
           return action.handleEvent(context, event);
       }

       OVERRIDE(Status stop(TransactionContext& context, const Status cause))
       {
           action.kill(context, cause);

           return cause;
       }

       OVERRIDE(void kill(TransactionContext& context, const Status cause))
       {
           action.kill(context, cause);
       }

   private:
       T_ASYN_ACTION action;
   };

   template <typename T_SYNC_ACTION>
   struct SYNC__ : SchedAction
   {
       OVERRIDE(Status exec(TransactionContext& context))
       {
           return action.exec(context);
       }

       OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
       {
           return USI_UNKNOWN_EVENT;
       }

       OVERRIDE(Status stop(TransactionContext& context, const Status cause))
       {
            return cause;
       }

       OVERRIDE(void kill(TransactionContext& context, const Status cause))
       {
       }

   private:
      T_SYNC_ACTION action;
   };
}

////////////////////////////////////////////////////////////////////////
#define __asyn(action, ...) \
       ::details::ASYN__< action, ##__VA_ARGS__ >

#define __sync(action, ...) \
       ::details::SYNC__< action, ##__VA_ARGS__ >

////////////////////////////////////////////////////////////////////////
#define __ind(...) __sync(__VA_ARGS__)
//#define _call(...) __sync(__VA_ARGS__)
#define __req(...)  __asyn(__VA_ARGS__)
#define __rsp(...)  __sync(__VA_ARGS__)
#define __spy(...)  __asyn(__VA_ARGS__)

#define __onto(actor)    < actor >
////////////////////////////////////////////////////////////////////////

#endif /* ACTIONHELPER_H_ */

