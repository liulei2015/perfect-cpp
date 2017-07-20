/*
 * TransactionListener.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONLISTENER_H_
#define TRANSACTIONLISTENER_H_

#include "l0-infra/trans-dsl/sched/concept/ActionId.h"
#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/base/Default.h>
#include "l0-infra/trans-dsl/listener/ListenerType.h"
#include "l0-infra/base/Singleton.h"
#include "l0-infra/base/BaseTypes.h"
#include <stdio.h>

struct Event;
struct TransactionInfo;

DEFINE_ROLE(TransactionListener)
{
    TransactionListener()
    {
    }

    virtual bool shouldOptimize() const
    {
        return false;
    }

    DEFAULT(bool, shouldReport() const);
    DEFAULT(void, onActionStarting(const TransactionInfo&, const ActionId));
    DEFAULT(void, onActionStarted(const TransactionInfo&, const ActionId));
    DEFAULT(void, onActionDone(const TransactionInfo&, const ActionId, const Status));

    DEFAULT(void, onActionStartStopping(const TransactionInfo&, const ActionId, const Status));
    DEFAULT(void, onActionStoppingStarted(const TransactionInfo&, const ActionId));
    DEFAULT(void, onStoppingEventConsumed(const TransactionInfo&, const ActionId, const Event&));
    DEFAULT(void, onActionStopped(const TransactionInfo&, const ActionId, const Status));

    DEFAULT(void, onActionKilled(const TransactionInfo&, const ActionId, const Status));

    DEFAULT(ListenerType, getType() const);
    DEFAULT(void, print() const);

};

DEF_SINGLETON(NilTransactionListener) EXTENDS(TransactionListener)
{
    NilTransactionListener()
    {
        print();
    }
};

#endif /* TRANSACTIONLISTENER_H_ */

