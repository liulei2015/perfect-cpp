/*
 * MultiThreadScheduler.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef MULTITHREADSCHEDULER_H_
#define MULTITHREADSCHEDULER_H_

#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/sched/def/ActionThreadDefs.h"
#include "l0-infra/trans-dsl/ext/multi-thread/concept/MultiThreadContext.h"
#include "l0-infra/trans-dsl/utils/SimpleRuntimeContext.h"
#include <l0-infra/dci/Role.h>

struct Event;
struct TransactionContext;

struct MultiThreadScheduler
    : protected SimpleRuntimeContext
    , protected MultiThreadContext
{
   MultiThreadScheduler();

   Status startMainThread(ActionThread&);
   Status handleEvent(const Event&);
   Status stop(const Status);
   void   kill(const Status);

   bool isWorking() const;

private:
   OVERRIDE(Status startThread(const ActionThreadId, ActionThread&, Status& result));
   OVERRIDE(Status killThread(const ActionThreadId, const Status));
   OVERRIDE(Status stopThread(const ActionThreadId, const Status));
   OVERRIDE(Status joinThread(const ActionThreadId, Status& result) const);

private:
   void init();
   Status getFinalStatus() const;
   ActionStatus getMainThreadStatus() const;
   Status finalProcess(ActionStatus status);
   void doStop(const Status cause);
   Status doHandleEvent(const Event& event);
   void broadcastActionDone(const ActionThreadId, const Status);
   void notifyActionDone(const ActionThreadId tid, const ActionThreadId who, const Status result);
   void doneCheck(const ActionThreadId tid);

   inline void handleEventOnThread(const ActionThreadId tid, const Event& event);
   void doKillThread(const ActionThreadId tid, const Status cause);

private:

   struct NamedThread
   {
      NamedThread();

      Status start(ActionThread& thread, MultiThreadScheduler& context);
      Status handleEvent(MultiThreadScheduler& context, const Event&);
      Status stop(MultiThreadScheduler& context, const Status cause);
      Status kill(MultiThreadScheduler& context, const Status cause);
      Status getWorkingStatus() const;

      void reset();

   private:
      ActionThread* thread;
   }
   threads[MAX_NUM_OF_THREADS];

   ActionThreadId  current;
   bool stopping;

private:
   USE_ROLE(TransactionContext);
};

#endif /* MULTITHREADSCHEDULER_H_ */

