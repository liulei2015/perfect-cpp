/*
 * TransactionListenerProxy.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONLISTENERPROXY_H_
#define TRANSACTIONLISTENERPROXY_H_

#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"

struct TransactionListenerProxy : TransactionListener
{
   TransactionListenerProxy();

   OVERRIDE(void onActionStarted(const TransactionInfo&, const ActionId));
   OVERRIDE(void onActionDone(const TransactionInfo&, const ActionId, const Status result));

   OVERRIDE(void onActionStartStopping(const TransactionInfo&, const ActionId, const Status cause));
   OVERRIDE(void onActionStoppingStarted(const TransactionInfo&, const ActionId));
   OVERRIDE(void onStoppingEventConsumed(const TransactionInfo&, const ActionId, const Event&));
   OVERRIDE(void onActionStopped(const TransactionInfo&, const ActionId, const Status result));

   OVERRIDE(void onActionKilled(const TransactionInfo&, const ActionId, const Status cause));

   void updateTransactionListener(TransactionListener& listener);

private:
   TransactionListener* listener;
};

#endif /* TRANSACTIONLISTENERPROXY_H_ */

