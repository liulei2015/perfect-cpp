/*
 * UserActionListenerAdapter.cc
 *
 * Created on: May 29, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/trans/UserActionListenerAdapter.h"
#include "l0-infra/trans-dsl/sched/concept/UserActionListener.h"

void UserActionListenerAdapter::onActionStarted(const TransactionInfo& trans, const ActionId id)
{
   ROLE(UserActionListener).onActionStarted(id);
}

void UserActionListenerAdapter::onActionDone(const TransactionInfo& trans, const ActionId id, const Status result)
{
   ROLE(UserActionListener).onActionDone(id, result);
}

void UserActionListenerAdapter::onActionStartStopping(const TransactionInfo& trans, const ActionId id, const Status cause)
{
   ROLE(UserActionListener).onActionKilled(id, cause);
}

void UserActionListenerAdapter::onActionStoppingStarted(const TransactionInfo& trans, const ActionId id)
{
}

void UserActionListenerAdapter::onStoppingEventConsumed(const TransactionInfo& trans, const ActionId id, const Event& event)
{
}

void UserActionListenerAdapter::onActionStopped(const TransactionInfo& trans, const ActionId id, const Status result)
{
}

void UserActionListenerAdapter::onActionKilled(const TransactionInfo& trans, const ActionId id, const Status cause)
{
   ROLE(UserActionListener).onActionKilled(id, cause);
}

