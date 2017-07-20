/*
 * WithIdHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef WITHIDHELPER_H_
#define WITHIDHELPER_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionListener.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/event/concept/Event.h"

namespace details
{
   template <ActionId I_ACTION_ID, typename T_ACTION>
   struct WITH_ID__ : SchedAction
   {
       WITH_ID__()
       : state(S_IDLE)
       , listener(&NilTransactionListener::getInstance())
       {
       }

      OVERRIDE(Status exec(TransactionContext& context))
      {
          if(context.getListener() != 0) listener = context.getListener();
          state = S_IDLE;

          onActionStarted(context);
          ActionStatus status = action.exec(context);
          if(status.isWorking())
          {
              state = S_WORKING;
              return status;
          }

          onActionDone(context, status);

          return status;
      }

      OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
      {
          switch(state)
          {
          case S_WORKING:
          {
              ActionStatus status = action.handleEvent(context, event);
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
              ActionStatus status = action.handleEvent(context, event);
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

      OVERRIDE(Status stop(TransactionContext& context, const Status cause))
      {
          if(state == S_WORKING)
          {
              onActionStartStopping(context, cause);

              ActionStatus status = action.stop(context, cause);
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

      OVERRIDE(void kill(TransactionContext& context, const Status cause))
      {
          if(state == S_IDLE) return;

          action.kill(context, cause);
          onActionKilled(context, cause);

          state = S_IDLE;
      }

   private:
      void onActionStarting(TransactionContext& context);
      void onActionStarted(TransactionContext& context)
      {
          listener->onActionStarted(context, I_ACTION_ID);
      }

      void onActionDone(TransactionContext& context, Status status)
      {
          listener->onActionDone(context, I_ACTION_ID, status);
      }

      void onActionStoppingStarted(TransactionContext& context)
      {
          listener->onActionStoppingStarted(context, I_ACTION_ID);
      }

      void onStoppingEventConsumed(TransactionContext& context, const Event& event)
      {
          listener->onStoppingEventConsumed(context, I_ACTION_ID, event);
      }

      void onActionStartStopping(TransactionContext& context, Status cause)
      {
          listener->onActionStartStopping(context, I_ACTION_ID, cause);
      }

      void onActionStopped(TransactionContext& context, Status status)
      {
          listener->onActionStopped(context, I_ACTION_ID, status);
      }

      void onActionKilled(TransactionContext& context, Status cause)
      {
          listener->onActionKilled(context, I_ACTION_ID, cause);
      }

   private:
      enum { S_IDLE, S_WORKING, S_STOPPING} state;
      TransactionListener* listener;

   private:
      T_ACTION action;
   };
};

///////////////////////////////////////////////////////////////
#define __with_id(...) ::details::WITH_ID__< __VA_ARGS__ >

///////////////////////////////////////////////////////////////

#endif /* WITHIDHELPER_H_ */

