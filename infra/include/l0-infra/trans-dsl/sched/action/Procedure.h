/*
 * Procedure.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PROCEDURE_H_
#define PROCEDURE_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/utils/SimpleRuntimeContext.h"
#include "l0-infra/trans-dsl/utils/DeclState.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

struct FinalAction;

struct Procedure : private SimpleRuntimeContext, SchedAction
{
    explicit Procedure(SchedAction& schedAction, FinalAction& finalAction, const bool protect);

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   OVERRIDE(bool shouldReportParent() const);

   void init();
   Status gotoFinal(TransactionContext&, const ActionStatus);
   Status gotoDone(TransactionContext&, const ActionStatus result);
   Status stopOnWorking(TransactionContext& context, Status cause);
   Status handleEventOnFinal(TransactionContext& context, const Event& event);
   Status handleEventOnWorking(TransactionContext& context, const Event& event);

private:
   void doKill(FinalAction&, TransactionContext&, Status);
   Status getFinalStatus() const;

private:
   //struct State;
   //State* state;

    SchedAction& schedAction;
    FinalAction& finalAction;
    enum { S_IDLE, S_WORKING, S_STOPPING, S_FINAL} state;
    const bool protect;

   struct AutoSwitch;

private:
   //__DECL_STATE(Idle);
   //__DECL_STATE(Working);
   //__DECL_STATE(Stopping);
   //__DECL_STATE(Final);
   //__DECL_STATE(Done);

   //struct WorkingState;

private:

   //USE_ROLE(SchedAction);
   //USE_ROLE(FinalAction);
   //ABSTRACT(bool isProtected() const);
};

#endif /* PROCEDURE_H_ */

