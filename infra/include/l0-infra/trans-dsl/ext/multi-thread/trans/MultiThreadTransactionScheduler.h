/*
 * MultiThreadTransactionScheduler.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADTRANSACTIONSCHEDULER_H_
#define MULTITHREADTRANSACTIONSCHEDULER_H_

#include "l0-infra/trans-dsl/ext/multi-thread/trans/MultiThreadScheduler.h"
#include "l0-infra/trans-dsl/sched/trans/BaseTransactionScheduler.h"

struct MultiThreadTransactionScheduler
   : private MultiThreadScheduler
   , BaseTransactionScheduler
{
   explicit MultiThreadTransactionScheduler(const InstanceId iid = InstanceId());

   OVERRIDE(Status start(ActionThread&));
   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(void   kill(const Status));

private:
   OVERRIDE(Status actualStop(const Status));
   OVERRIDE(bool isWorking() const);

private:
   APPEND_INTERFACE_TABLE(BaseTransactionScheduler)
      __HAS_INTERFACE(MultiThreadContext)
   END_INTERFACE_TABLE()

private:
   IMPL_ROLE(TransactionContext);
};

#endif /* MULTITHREADTRANSACTIONSCHEDULER_H_ */

