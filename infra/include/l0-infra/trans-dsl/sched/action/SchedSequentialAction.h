/*
 * SchedSequentialAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSEQUENTIALACTION_H_
#define SCHEDSEQUENTIALACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/sched/action/LinkedSchedAction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include <l0-infra/base/List.h>

struct SchedSequentialAction: SchedAction
{
   SchedSequentialAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

   void pushBackAction(LinkedSchedAction&);

private:
   Status go(TransactionContext&);
   Status forward(TransactionContext&);
   Status doExec(TransactionContext& context);
   Status doHandleEvent(TransactionContext&, const Event&);
   Status getFinalStatus(const ActionStatus);
   Status doStop(TransactionContext& context, const Status cause);

private:
   typedef List<LinkedSchedAction> Actions;
   Actions actions;
   LinkedSchedAction *current;

   Status finalStatus;
};

#endif /* SCHEDSEQUENTIALACTION_H_ */

