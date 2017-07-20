/*
 * SimpleTransactionScheduler.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */

#ifndef SIMPLETRANSACTIONSCHEDULER_H_
#define SIMPLETRANSACTIONSCHEDULER_H_

#include "l0-infra/trans-dsl/sched/trans/BaseTransactionScheduler.h"
#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionContext.h"

struct SimpleTransactionScheduler
   : BaseTransactionScheduler
{
   explicit SimpleTransactionScheduler(InstanceId iid = InstanceId());
   explicit SimpleTransactionScheduler(RuntimeContext& runtimeContext, InstanceId iid = InstanceId());

   OVERRIDE(Status start(ActionThread&));
   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(void   kill(const Status));

private:
   OVERRIDE(Status actualStop(const Status));
   OVERRIDE(bool isWorking() const);

private:
   ActionThread* thread;
};

#endif /* SIMPLETRANSACTIONSCHEDULER_H_ */

