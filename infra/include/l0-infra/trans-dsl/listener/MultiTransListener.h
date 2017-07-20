#ifndef _INCL_USI_LISTENER_MUTI_LISTENER_H
#define _INCL_USI_LISTENER_MUTI_LISTENER_H

#include "l0-infra/base/List.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"
#include "l0-infra/trans-dsl/listener/LinkedTransListener.h"
#include "l0-infra/trans-dsl/listener/ListenerType.h"

extern BYTE isMultiListenerPrintSwitchOn;

#define NOTIFY_ALL(ACTION)                      \
LIST_FOREACH(LinkedTransListener, i, listeners) \
{                                               \
    i->ACTION;                                  \
}

struct MultiTransListener : TransactionListener
{
    void addListener(LinkedTransListener& listener)
    {
        listeners.pushBack(listener);
    }

    void resetListeners()
    {
        listeners.clear();
    }

    OVERRIDE(bool shouldReport() const)
    {
        if (listeners.isEmpty()) return false;
        return true;
    }

    OVERRIDE(void print() const)
    {
        if( ! isMultiListenerPrintSwitchOn) return;

        printf("MultiTransListener printAllListeners(shouldOptimize( %d )): \n", shouldOptimize());

        List<LinkedTransListener>::Iterator iter;
        for(iter = listeners.begin(); iter != listeners.end(); ++iter)
        {
            iter->print();
        }
    }

    OVERRIDE(void onActionStarted(const TransactionInfo& trans, const ActionId actionId))
    {
        struct MultiListenerVistior :List<LinkedTransListener>::Visitor
        {
            MultiListenerVistior(const TransactionInfo& trans, const ActionId actionId)
                                        :trans(trans), actionId(actionId)
                                         {

                                         }
            OVERRIDE(void visit(LinkedTransListener& list))
            {
                list.onActionStarted(trans, actionId);
            }
        private:
            const TransactionInfo& trans; const ActionId actionId;
        } visitor(trans, actionId);
        listeners.visitAll(visitor);
    }

    OVERRIDE(void onActionDone(const TransactionInfo& trans, const ActionId actionId, const Status status))
    {
        struct MultiListenerVistior :List<LinkedTransListener>::Visitor
        {
            MultiListenerVistior(const TransactionInfo& trans, const ActionId actionId, const Status status)
                                    :trans(trans), actionId(actionId), status(status)
                                     {

                                     }
            OVERRIDE(void visit(LinkedTransListener& list))
            {
                list.onActionDone(trans, actionId, status);
            }
        private:
            const TransactionInfo& trans; const ActionId actionId; const Status status;
        } visitor(trans, actionId, status);
        listeners.visitAll(visitor);
    }

    OVERRIDE(void onActionStartStopping(const TransactionInfo& trans, const ActionId actionId, const Status status))
    {
        NOTIFY_ALL(onActionStartStopping(trans, actionId, status));
    }

    OVERRIDE(void onActionStoppingStarted(const TransactionInfo& trans, const ActionId actionId))
    {
        NOTIFY_ALL(onActionStoppingStarted(trans, actionId));
    }

    OVERRIDE(void onStoppingEventConsumed(const TransactionInfo& trans, const ActionId actionId, const Event& event))
    {
        NOTIFY_ALL(onStoppingEventConsumed(trans, actionId, event));
    }

    OVERRIDE(void onActionStopped(const TransactionInfo& trans, const ActionId actionId, const Status status))
    {
        NOTIFY_ALL(onActionStopped(trans, actionId, status));
    }

    OVERRIDE(void onActionKilled(const TransactionInfo& trans, const ActionId actionId, const Status status))
    {
        NOTIFY_ALL(onActionKilled(trans, actionId, status));
    }

private:
    List<LinkedTransListener> listeners;
};

#endif

