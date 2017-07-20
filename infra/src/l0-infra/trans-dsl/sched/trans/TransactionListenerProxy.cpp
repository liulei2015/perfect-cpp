/*
 * TransactionListenerProxy.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/trans/TransactionListenerProxy.h"

namespace
{
   TransactionListener* getNullListener()
   {
      static TransactionListener nullListener;
      return &nullListener;
   }
}

TransactionListenerProxy::TransactionListenerProxy()
  : listener(getNullListener())
{
}

void TransactionListenerProxy::onActionStarted(const TransactionInfo& trans, const ActionId id)
{
   listener->onActionStarted(trans, id);
}

void TransactionListenerProxy::onActionDone(const TransactionInfo& trans, const ActionId id, const Status result)
{
   listener->onActionDone(trans, id, result);
}

void TransactionListenerProxy::onActionStartStopping(const TransactionInfo& trans, const ActionId id, const Status cause)
{
   listener->onActionStartStopping(trans, id, cause);
}

void TransactionListenerProxy::onActionStoppingStarted(const TransactionInfo& trans, const ActionId id)
{
   listener->onActionStoppingStarted(trans, id);
}

void TransactionListenerProxy::onStoppingEventConsumed(const TransactionInfo& trans, const ActionId id, const Event& event)
{
   listener->onStoppingEventConsumed(trans, id, event);
}

void TransactionListenerProxy::onActionStopped(const TransactionInfo& trans, const ActionId id, const Status result)
{
   listener->onActionStopped(trans, id, result);
}

void TransactionListenerProxy::onActionKilled(const TransactionInfo& trans, const ActionId id, const Status cause)
{
   listener->onActionKilled(trans, id, cause);
}

void TransactionListenerProxy::updateTransactionListener(TransactionListener& listener)
{
   this->listener = &listener;
}

