/*
 * LinkedActionThread.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDACTIONTHREAD_H_
#define LINKEDACTIONTHREAD_H_

#include "l0-infra/trans-dsl/sched/action/ActionThread.h"
#include <l0-infra/base/ListElem.h>

struct LinkedActionThread
         : ListElem<LinkedActionThread>
         , ActionThread
{
   LinkedActionThread(SchedAction& schedAction) : ActionThread(schedAction) {}
};

#endif /* LINKEDACTIONTHREAD_H_ */

