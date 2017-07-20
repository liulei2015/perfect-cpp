/*
 * SchedWithIdAction.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDWITHIDACTION_H_
#define SCHEDWITHIDACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/sched/concept/ActionId.h"
#include "l0-infra/trans-dsl/utils/DeclState.h"

struct TransactionListener;

struct SchedWithIdAction : SchedAction
{
    SchedWithIdAction( ActionId actionId);

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   void onActionStarting(TransactionContext& context);
   void onActionStarted(TransactionContext& context);
   void onActionDone(TransactionContext& context, Status status);

   void onActionStoppingStarted(TransactionContext& context);
   void onStoppingEventConsumed(TransactionContext& context, const Event& event);
   void onActionStartStopping(TransactionContext& context, Status cause);
   void onActionStopped(TransactionContext& context, Status status);

   void onActionKilled(TransactionContext& context, Status cause);

private:
   const ActionId actionId;
   enum { S_IDLE, S_WORKING, S_STOPPING} state;
   TransactionListener* listener;

private:
   USE_ROLE(SchedAction);
};

#endif /* SCHEDWITHIDACTION_H_ */

