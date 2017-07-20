/*
 * ThreadHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef THREADHELPER_H_
#define THREADHELPER_H_

#include "l0-infra/trans-dsl/sched/action/ActionThread.h"

namespace details
{
   template<typename T_ACTION>
   struct THREAD__: ActionThread
   {
	   THREAD__() : ActionThread(c_action) {}

   private:
	   T_ACTION c_action;
      //IMPL_ROLE_WITH_VAR(SchedAction, T_ACTION);
   };
};

#endif /* THREADHELPER_H_ */

