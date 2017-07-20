/*
 * TransactionContext.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONCONTEXT_H_
#define TRANSACTIONCONTEXT_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/dci/Unknown.h>
#include <l0-infra/trans-dsl/sched/concept/TransactionInfo.h>

struct TransactionInfo;
struct TransactionListener;
struct TransactionMode;
struct RuntimeContextInfo;

struct TransactionContext 
    : TransactionInfo
    , dci::Unknown
{
   TransactionContext() : listener(0) {}
   
    USE_ROLE(TransactionMode);
    USE_ROLE(RuntimeContextInfo);

    void updateTransactionListener(TransactionListener* listener)
    {
        this->listener = listener;
    }

    TransactionListener* getListener()
    {
        return listener;
    }

private:
    TransactionListener* listener;
};

#endif /* TRANSACTIONCONTEXT_H_ */

