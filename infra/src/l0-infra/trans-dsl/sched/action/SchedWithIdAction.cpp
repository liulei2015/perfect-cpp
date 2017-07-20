/*
 * SchedWithIdAction.cc
 *
 * Created on: May 28, 2013, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/action/SchedWithIdAction.h"
#include "l0-infra/trans-dsl/utils/GofState.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"
#include "l0-infra/event/concept/Event.h"

///////////////////////////////////////////////////////////////////////
SchedWithIdAction::SchedWithIdAction(ActionId actionId)
  : actionId(actionId)
  , state(S_IDLE)
  , listener(&NilTransactionListener::getInstance())
{
}

inline void SchedWithIdAction::onActionStarted(TransactionContext& context)
{
    listener->onActionStarted(context, actionId);
}

inline void SchedWithIdAction::onActionDone(TransactionContext& context, Status status)
{
    listener->onActionDone(context, actionId, status);
}

inline void SchedWithIdAction::onStoppingEventConsumed(TransactionContext& context, const Event& event)
{
    listener->onStoppingEventConsumed(context, actionId, event);
}

inline void SchedWithIdAction::onActionStoppingStarted(TransactionContext& context)
{
    listener->onActionStoppingStarted(context, actionId);
}

inline void SchedWithIdAction::onActionStartStopping(TransactionContext& context, Status cause)
{
    listener->onActionStartStopping(context, actionId, cause);
}

inline void SchedWithIdAction::onActionStopped(TransactionContext& context, Status status)
{
    listener->onActionStopped(context, actionId, status);
}

inline void SchedWithIdAction::onActionKilled(TransactionContext& context, Status cause)
{

    listener->onActionKilled(context, actionId, cause);
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::exec(TransactionContext& context)
{
    if(context.getListener() != 0) listener = context.getListener();
    state = S_IDLE;

    onActionStarted(context);
    ActionStatus status = ROLE(SchedAction).exec(context);
    if(status.isWorking())
    {
        state = S_WORKING;
        return status;
    }

    onActionDone(context, status);

    return status;
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::handleEvent(TransactionContext& context, const Event& event)
{
    switch(state)
    {
    case S_WORKING:
    {
        ActionStatus status = ROLE(SchedAction).handleEvent(context, event);
        if(status.isWorking())
        {
            return status;
        }

        onActionDone(context, status);

        state = S_IDLE;

        return status;
    }
    case S_STOPPING:
    {
        ActionStatus status = ROLE(SchedAction).handleEvent(context, event);
        if(event.isConsumed())
        {
            onStoppingEventConsumed(context, event);
        }

        if(status.isWorking())
        {
            return status;
        }

        onActionStopped(context, status);

        state = S_IDLE;

        return status;
    }
    default:break;
    }

    return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////
Status SchedWithIdAction::stop(TransactionContext& context, const Status cause)
{
    if(state == S_WORKING)
    {
        onActionStartStopping(context, cause);

        ActionStatus status = ROLE(SchedAction).stop(context, cause);
        if(status.isWorking())
        {
            onActionStoppingStarted(context);
            state = S_STOPPING;
        }
        else
        {
            onActionStopped(context, status);
            state = S_IDLE;
        }

        return status;
    }

    return cause;
}

///////////////////////////////////////////////////////////////////////
void SchedWithIdAction::kill(TransactionContext& context, const Status cause)
{
    if(state == S_IDLE) return;

    ROLE(SchedAction).kill(context, cause);
    onActionKilled(context, cause);

    state = S_IDLE;
}
