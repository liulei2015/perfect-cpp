/*
 * SimpleTransactionContext.h
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTIONCONTEXT_H_
#define SIMPLETRANSACTIONCONTEXT_H_

#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionInfo.h"
#include "l0-infra/trans-dsl/utils/AdaptedTimerInfo.h"
#include "l0-infra/trans-dsl/sched/trans/TransactionListenerProxy.h"
#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionMode.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/trans/TransMutexSchedulerAdapter.h"
#include "l0-infra/trans-dsl/sched/trans/TransSignalSchedulerAdapter.h"
#include <l0-infra/dci/InterfaceDef.h>
#include "l0-infra/trans-dsl/sched/concept/RuntimeContextInfo.h"

struct SimpleTransactionContext
         : protected RuntimeContextInfo
         , protected AdaptedTimerInfo
         , protected SimpleTransactionMode
         , protected TransMutexSchedulerAdapter
         , protected TransSignalSchedulerAdapter
         , TransactionContext
{
    explicit SimpleTransactionContext(InstanceId iid = InstanceId());
    explicit SimpleTransactionContext(RuntimeContext& runtimeContext, InstanceId iid = InstanceId());

    OVERRIDE(Status getStatus() const);

    void updateUserContext(dci::Unknown*);
    void updateInstanceId(InstanceId iid);

private:
   IMPL_ROLE(TransactionMode);

private:
   IMPL_ROLE(RuntimeContextInfo);

protected:
   BEGIN_INTERFACE_TABLE()
      __HAS_INTERFACE(TimerInfo)
      __HAS_INTERFACE(TransMutexScheduler)
      __HAS_INTERFACE(TransSignalScheduler)
   END_INTERFACE_TABLE()
};

#endif /* SIMPLETRANSACTIONCONTEXT_H_ */

