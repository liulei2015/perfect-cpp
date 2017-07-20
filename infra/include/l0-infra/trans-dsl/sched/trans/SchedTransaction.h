/*
 * SchedTransaction.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDTRANSACTION_H_
#define SCHEDTRANSACTION_H_

#include "l0-infra/trans-dsl/sched/concept/Transaction.h"
#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>
#include "l0-infra/dci/Unknown.h"

struct TimerInfo;
struct TransactionListener;
struct TransMutexScheduler;
struct TransSignalScheduler;

struct TransactionScheduler;
struct ActionThread;

struct SchedTransaction : Transaction
{
   OVERRIDE(Status start());
   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(Status stop(const StopCause& cause = StopCause()));
   OVERRIDE(void   kill(const StopCause& cause = StopCause()));

   void updateInstanceId(InstanceId iid);
   void updateTimerInfo(const TimerInfo&);
   void updateTransactionListener(TransactionListener*);
   void updateUserContext(dci::Unknown*);
   void updateMutexScheduler(TransMutexScheduler&);
   void updateSignalScheduler(TransSignalScheduler&);

private:
   USE_ROLE(TransactionScheduler);
   USE_ROLE(ActionThread);
};

#endif /* SCHEDTRANSACTION_H_ */

