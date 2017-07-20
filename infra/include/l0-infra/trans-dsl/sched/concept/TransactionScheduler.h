/*
 * TransactionScheduler.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONSCHEDULER_H_
#define TRANSACTIONSCHEDULER_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include "l0-infra/dci/Unknown.h"

struct ActionThread;
struct Event;
struct TransactionListener;
struct TransSignalScheduler;
struct TransMutexScheduler;
struct TimerInfo;

DEFINE_ROLE(TransactionScheduler)
{
   ABSTRACT(Status start(ActionThread&));
   ABSTRACT(Status handleEvent(const Event&));
   ABSTRACT(Status stop(const Status));
   ABSTRACT(void   kill(const Status));

   ABSTRACT(void updateInstanceId(InstanceId iid));
   ABSTRACT(void updateTimerInfo(const TimerInfo&));
   ABSTRACT(void updateTransactionListener(TransactionListener*));
   ABSTRACT(void updateUserContext(dci::Unknown*));
   ABSTRACT(void updateMutexScheduler(TransMutexScheduler&));
   ABSTRACT(void updateSignalScheduler(TransSignalScheduler&));
};

#endif /* TRANSACTIONSCHEDULER_H_ */

