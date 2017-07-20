/*
 * SchedKillAction.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#ifndef SCHEDKILLACTION_H_
#define SCHEDKILLACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/ext/multi-thread/concept/ActionThreadId.h"

struct SchedKillAction : SchedAction
{
   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void kill(TransactionContext&, const Status));

private:
   Status getFinalCause(TransactionContext& context) const;

private:
   ABSTRACT(ActionThreadId getThreadId() const);
   ABSTRACT(Status getCause() const);
};

#endif /* SCHEDKILLACTION_H_ */

