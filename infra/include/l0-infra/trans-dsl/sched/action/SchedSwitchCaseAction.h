/*
 * SchedSwitchCaseAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSWITCHCASEACTION_H_
#define SCHEDSWITCHCASEACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/sched/action/ActionPath.h"
#include "l0-infra/base/List.h"

struct SchedSwitchCaseAction : SchedAction
{
   SchedSwitchCaseAction();

   OVERRIDE(Status exec(TransactionContext& context));
   OVERRIDE(Status handleEvent(TransactionContext& context, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

   void pushBackActionPath(ActionPath& listener);

private:
   SchedAction* findMatchedAction(TransactionContext&);

private:
   typedef List<ActionPath> Paths;

   Paths          paths;
   SchedAction*   selectedAction;
};

#endif /* SCHEDSWITCHCASEACTION_H_ */

