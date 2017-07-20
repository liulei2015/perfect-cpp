/*
 * SchedSafeAction.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDSAFEACTION_H_
#define SCHEDSAFEACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include <l0-infra/dci/Role.h>

struct SchedSafeAction : SchedAction
{
   SchedSafeAction();

   OVERRIDE(Status exec(TransactionContext&));
   OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
   OVERRIDE(Status stop(TransactionContext&, const Status));
   OVERRIDE(void   kill(TransactionContext&, const Status));

private:
   Status final(const Status);

private:
   bool running;

private:
   USE_ROLE(SchedAction);
};

#endif /* SCHEDSAFEACTION_H_ */

