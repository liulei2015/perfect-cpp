/*
 * LinkedHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDHELPER_H_
#define LINKEDHELPER_H_

#include "l0-infra/trans-dsl/sched/action/LinkedSchedAction.h"

namespace details
{
   template <typename T_ACTION>
   struct LINKED__ : LinkedSchedAction
   {
	   LINKED__() : LinkedSchedAction(action) {}

   private:
	   T_ACTION action;
   };
}

#endif /* LINKEDHELPER_H_ */

