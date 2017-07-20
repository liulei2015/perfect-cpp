/*
 * SimpleTransactionContext.cc
 *
 * Created on: Jun 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/RuntimeContext.h"

SimpleTransactionContext::SimpleTransactionContext(InstanceId iid)
{
    updateInstanceId(iid);
}

SimpleTransactionContext::SimpleTransactionContext(RuntimeContext& runtimeContext, InstanceId iid )
  : RuntimeContextInfo(runtimeContext)
{
    updateInstanceId(iid);
}

void SimpleTransactionContext::updateInstanceId(InstanceId iid)
{
    TransactionInfo::iid = iid;
}

/////////////////////////////////////////////////////////////////
Status SimpleTransactionContext::getStatus() const
{
    RuntimeContext* context = RuntimeContextInfo::getRuntimeContext();
    if(__unlikely(context == 0))
    {
        return USI_SUCCESS;
    }

    Status status = context->getStatus();
    return IS_FAILED_STATUS(status) ? status : USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////
void SimpleTransactionContext::updateUserContext(dci::Unknown* userContext)
{
    TransactionInfo::userContext = userContext;
}
