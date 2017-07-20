/*
 * UserActionListenerAdapter.h
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef USERACTIONLISTENERADAPTER_H_
#define USERACTIONLISTENERADAPTER_H_

#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"

struct UserActionListener;

struct UserActionListenerAdapter : TransactionListener
{
    OVERRIDE(void onActionStarted(const TransactionInfo&, const ActionId));
    OVERRIDE(void onActionDone(const TransactionInfo&, const ActionId, const Status));

    OVERRIDE(void onActionStartStopping(const TransactionInfo&, const ActionId, const Status));
    OVERRIDE(void onActionStoppingStarted(const TransactionInfo&, const ActionId));
    OVERRIDE(void onStoppingEventConsumed(const TransactionInfo&, const ActionId, const Event&));
    OVERRIDE(void onActionStopped(const TransactionInfo&, const ActionId, const Status));

    OVERRIDE(void onActionKilled(const TransactionInfo&, const ActionId, const Status));

private:
   USE_ROLE(UserActionListener);
};

#endif /* USERACTIONLISTENERADAPTER_H_ */

