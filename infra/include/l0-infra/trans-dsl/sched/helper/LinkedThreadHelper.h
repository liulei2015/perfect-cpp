/*
 * LinkedThreadHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDTHREADHELPER_H_
#define LINKEDTHREADHELPER_H_

#include "l0-infra/trans-dsl/sched/action/LinkedActionThread.h"

namespace details
{
   template <typename T_ACTION>
   struct LINKED_THREAD__ : LinkedActionThread
   {
	   LINKED_THREAD__() : LinkedActionThread(c_action) {}

   private:
	   T_ACTION c_action;
   };
}

#endif /* LINKEDTHREADHELPER_H_ */

