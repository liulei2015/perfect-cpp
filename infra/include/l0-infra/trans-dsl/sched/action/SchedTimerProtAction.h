/*
 * SchedTimerProtAction.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SCHEDTIMERPROTACTION_H_
#define SCHEDTIMERPROTACTION_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/sched/port/PlatformSpecifiedRelativeTimer.h"

struct RelativeTimer;

struct SchedTimerProtAction : SchedAction
{
    SchedTimerProtAction(SchedAction& schedAction, TimerId timerId, WORD32 timerParam);

    OVERRIDE(Status exec(TransactionContext&));
    OVERRIDE(Status handleEvent(TransactionContext&, const Event&));
    OVERRIDE(Status stop(TransactionContext&, const Status));
    OVERRIDE(void   kill(TransactionContext&, const Status));

private:
    Status startTimer(TransactionContext&);
    Status final(ActionStatus status);
    void stopTimer();
    void init();

    SchedAction& schedAction;
    PlatformSpecifiedRelativeTimer timer;
    Status finalStatus;
    bool started;

private:
    

    ABSTRACT(Status getTimeoutStatus() const);
};

#endif /* SCHEDTIMERPROTACTION_H_ */

