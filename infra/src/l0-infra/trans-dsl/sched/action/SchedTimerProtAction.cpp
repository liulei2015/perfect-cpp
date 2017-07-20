/*
 * SchedTimerProtAction.cc
 *
 *  Created on: Apr 24, 2013
 *      Author: arthur
 */


#include "l0-infra/trans-dsl/sched/action/SchedTimerProtAction.h"
#include "l0-infra/trans-dsl/sched/concept/TimerInfo.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/utils/RelativeTimer.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionInfo.h"
#include "l0-infra/event/concept/Event.h"

//////////////////////////////////////////////////////////////////////////////////
SchedTimerProtAction::SchedTimerProtAction(SchedAction& schedAction, TimerId timerId, WORD32 timerParam)
: schedAction(schedAction), timer(timerId, timerParam), finalStatus(USI_SUCCESS), started(false)
{}

//////////////////////////////////////////////////////////////////////////////////
Status SchedTimerProtAction::startTimer(TransactionContext& context)
{
    TimerInfo* timerInfo = dci::unknown_cast<TimerInfo>(&context);
    USI_ASSERT_VALID_PTR(timerInfo);

    return timer.start(*timerInfo);
}

//////////////////////////////////////////////////////////////////////////////////
inline Status SchedTimerProtAction::final(ActionStatus status)
{
    if(status.isWorking()) return status;

    stopTimer();

    return (Status)status ;
}

inline void SchedTimerProtAction::init()
{
    started = false;
    finalStatus = USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////
Status SchedTimerProtAction::exec(TransactionContext& context)
{
    init();

    USI_ASSERT_SUCC_CALL(startTimer(context));

    started = true;

    return final(schedAction.exec(context));
}

//////////////////////////////////////////////////////////////////////////////////
Status SchedTimerProtAction::handleEvent(TransactionContext& context, const Event& event)
{
    if(started && timer.matches(event))
    {
        event.consume();
        return stop(context, ActionStatus(getTimeoutStatus()).isWorking() ? USI_TIMEDOUT : getTimeoutStatus());
    }

    return final(schedAction.handleEvent(context, event));
}

//////////////////////////////////////////////////////////////////////////////////
Status SchedTimerProtAction::stop(TransactionContext& context, const Status cause)
{
    if(!started) return USI_CONTINUE;


    finalStatus = cause;

    return final(schedAction.stop(context, cause));
}

void SchedTimerProtAction::stopTimer()
{
    if(__likely(started))
    {
        timer.stop();
        started = false;
    }
}

//////////////////////////////////////////////////////////////////////////////////
void SchedTimerProtAction::kill(TransactionContext& context, const Status cause)
{
    stopTimer();

    schedAction.kill(context, cause);
}
