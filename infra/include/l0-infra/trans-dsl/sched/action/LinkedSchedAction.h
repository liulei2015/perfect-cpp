/*
 * LinkedSchedAction.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LINKEDSCHEDACTION_H_
#define LINKEDSCHEDACTION_H_

#include <l0-infra/base/ListElem.h>
#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"

struct LinkedSchedAction : ListElem<LinkedSchedAction>
{
	LinkedSchedAction(SchedAction& schedAction) : schedAction(schedAction) {}

	Status exec(TransactionContext& context)
	{
	   return schedAction.exec(context);
	}

	Status handleEvent(TransactionContext& context, const Event& event)
	{
	   return schedAction.handleEvent(context, event);
	}

	Status stop(TransactionContext& context, const Status cause)
	{
	   return schedAction.stop(context, cause);
	}

	void kill(TransactionContext& context, const Status cause)
	{
		schedAction.kill(context, cause);
	}

private:
   SchedAction& schedAction;
};

#endif /* LINKEDSCHEDACTION_H_ */

