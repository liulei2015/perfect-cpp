/*
 * Transaction.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include "l0-infra/trans-dsl/utils/StopCause.h"

struct Event;
struct TransactionListener;
struct InstanceId;

DEFINE_ROLE(Transaction)
{
   ABSTRACT(Status start());
   ABSTRACT(Status handleEvent(const Event&));
   ABSTRACT(Status stop(const StopCause& = StopCause()));
   ABSTRACT(void   kill(const StopCause& = StopCause()));

   Status startWithEvent(const Event&);
};

struct TransMutexScheduler;
struct TransSignalScheduler;

struct LockableTransaction : Transaction
{
    ABSTRACT(void updateMutexScheduler(TransMutexScheduler&));
    ABSTRACT(void updateSignalScheduler(TransSignalScheduler&));

    ABSTRACT(void init(const InstanceId&));
    ABSTRACT(void destroy());
};

#endif /* TRANSACTION_H_ */

