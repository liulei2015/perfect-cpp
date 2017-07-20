/*
 * SchedExcldcmveAction.h
 *
 * Created on: Apr 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDEXCLUSIVEACTION_H_
#define SCHEDEXCLUSIVEACTION_H_

#include <l0-infra/base/List.h>
#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/sched/action/LinkedSchedAction.h"

struct SchedExcldcmveAction : SchedAction
{
   SchedExcldcmveAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

   void addAction(LinkedSchedAction&);

private:
   Status selectAction(TransactionContext&, const Event&);
   void interruptOthers(TransactionContext&, Status status);
   void init();

private:
   typedef List<LinkedSchedAction> Actions;

   Actions actions;
   Actions doneActions;
   LinkedSchedAction* selectedAction;
};

#endif /* SCHEDEXCLUSIVEACTION_H_ */

