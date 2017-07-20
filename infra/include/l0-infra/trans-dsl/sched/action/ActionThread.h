/*
 * ActionThread.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONTHREAD_H_
#define ACTIONTHREAD_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/utils/SimpleRuntimeContext.h"
#include "l0-infra/trans-dsl/utils/DeclState.h"

#include "l0-infra/trans-dsl/utils/ActionStatus.h"

struct ActionThread : private SimpleRuntimeContext, SchedAction
{
   ActionThread(SchedAction& schedAction);

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

   Status getThreadStatus() const
   {
	   return objectStatus;
   }

   bool isWorking() const
   {
	   return state == WORKING_STATE || state == STOPPING_STATE;
   }

private:
   void init();
   Status doHandleEvent(TransactionContext& context, const Event& event);
   Status onDone(const ActionStatus status);

private:
   SchedAction& schedAction;
   enum { IDLE_STATE, WORKING_STATE, STOPPING_STATE } state;

   struct AutoSwitch;

private:
   //USE_ROLE(SchedAction);
};

#endif /* ACTIONTHREAD_H_ */

