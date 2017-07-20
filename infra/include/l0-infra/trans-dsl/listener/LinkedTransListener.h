#ifndef _INCL_USI_LISTENER_LINKED_TRANS_LISTENER_H 
#define _INCL_USI_LISTENER_LINKED_TRANS_LISTENER_H

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/ListElem.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

struct LinkedTransListener : ListElem<LinkedTransListener>
{
	LinkedTransListener(TransactionListener& listener) : listener(listener)
	{
	}

	bool shouldReport() const
	{
		return listener.shouldReport();
	}

	TransactionListener* thisListener()
	{
		return &listener;
	}

	void print() const
	{
	    listener.print();
	}

	void onActionStarted(const TransactionInfo& trans, const ActionId actionId)
	{
		listener.onActionStarted(trans, actionId);
	}

	void onActionDone(const TransactionInfo& trans, const ActionId actionId, const Status status)
	{
		listener.onActionDone(trans, actionId, status);
	}

	void onActionStartStopping(const TransactionInfo& trans, const ActionId actionId, const Status status)
	{
		listener.onActionStartStopping(trans, actionId, status);
	}

	void onActionStoppingStarted(const TransactionInfo& trans, const ActionId actionId)
	{
		listener.onActionStoppingStarted(trans, actionId);
	}

	void onStoppingEventConsumed(const TransactionInfo& trans, const ActionId actionId, const Event& event)
	{
		listener.onStoppingEventConsumed(trans, actionId, event);
	}

	void onActionStopped(const TransactionInfo& trans, const ActionId actionId, const Status status)
	{
		listener.onActionStopped(trans,actionId, status);
	}

	void onActionKilled(const TransactionInfo& trans, const ActionId actionId, const Status status)
	{
		listener.onActionKilled(trans, actionId, status);
	}

	ListenerType getType() const
    {
		return listener.getType();
	}

private:
    TransactionListener& listener;
};

#endif

