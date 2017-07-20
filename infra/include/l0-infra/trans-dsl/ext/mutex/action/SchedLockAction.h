/*
 * SchedLockAction.h
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDLOCKACTION_H_
#define SCHEDLOCKACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include <l0-infra/trans-dsl/ext/mutex/concept/TransMutextId.h>

struct SchedLockAction : SchedAction
{
   SchedLockAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   Status final(Status, TransactionContext&);
   Status lock(TransactionContext&);
   Status unlock(TransactionContext&);
   Status tryExec(TransactionContext&, const Event&);

private:
   bool waiting;

private:
   USE_ROLE(SchedAction);
   ABSTRACT(TransMutexId getMutexId() const);
};

#endif /* SCHEDLOCKACTION_H_ */

