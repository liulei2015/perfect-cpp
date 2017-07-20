/*
 * Procedure.cc
 *
 *  Created on: Apr 21, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/Procedure.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/base/Likely.h"

///////////////////////////////////////////////////////////////////////
Procedure::Procedure(SchedAction& schedAction, FinalAction& finalAction, const bool protect)
  : schedAction(schedAction)
  , finalAction(finalAction) 
  , state(S_IDLE)
  , protect(protect)
{
}

///////////////////////////////////////////////////////////////////////
bool Procedure::shouldReportParent() const
{
   return !protect;
}

///////////////////////////////////////////////////////////////////////
inline Status Procedure::getFinalStatus() const
{
   return IS_FAILED_STATUS(objectStatus) ? objectStatus : USI_SUCCESS;
}

///////////////////////////////////////////////////////////////////////
inline void Procedure::doKill(FinalAction& action, TransactionContext& context, Status cause)
{
   action.kill(context, cause);
   gotoDone(context, USI_SUCCESS);
}

///////////////////////////////////////////////////////////////////////
struct Procedure::AutoSwitch : RuntimeContextAutoSwitch
{
   AutoSwitch(Procedure& proc, TransactionContext& context)
        : RuntimeContextAutoSwitch(proc, proc.parent, context)
   {
   }
};

///////////////////////////////////////////////////////////////////////
#define __AUTO_SWITCH()  AutoSwitch autoSwitch(*this, context)

///////////////////////////////////////////////////////////////////////
inline void Procedure::init()
{
    SimpleRuntimeContext::init();
    state = S_IDLE;
}

///////////////////////////////////////////////////////////////////////
Status Procedure::gotoDone(TransactionContext&, const ActionStatus result)
{
    if(__unlikely(result.isFailed()))
    {
        return result;
    }

    return protect ? (Status)result : getFinalStatus();
}

///////////////////////////////////////////////////////////////////////
Status Procedure::gotoFinal(TransactionContext& context, const ActionStatus result)
{
    reportFailure(result);

    ActionStatus status = finalAction.exec(context);
    if(status.isWorking())
    {
        state = S_FINAL;
        return status;
    }

    return gotoDone(context, status);
}

///////////////////////////////////////////////////////////////////////
Status Procedure::exec(TransactionContext& context)
{
    init();

   __AUTO_SWITCH();

   ActionStatus status = schedAction.exec(context);
   if(status.isWorking())
   {
       state = S_WORKING;
       return status;
   }

   return gotoFinal(context, status);
}

///////////////////////////////////////////////////////////////////////
inline Status Procedure::handleEventOnWorking(TransactionContext& context, const Event& event)
{
    ActionStatus status = schedAction.handleEvent(context, event);
    if(status.isWorking())
    {
        return status;
    }

    return gotoFinal(context, status);
}

///////////////////////////////////////////////////////////////////////
inline Status Procedure::handleEventOnFinal(TransactionContext& context, const Event& event)
{
    ActionStatus status = finalAction.handleEvent(context, event);
    if(status.isWorking())
    {
        return status;
    }

    return gotoDone(context, status);
}

///////////////////////////////////////////////////////////////////////
Status Procedure::handleEvent(TransactionContext& context, const Event& event)
{
   __AUTO_SWITCH();

   switch(state)
   {
    case S_WORKING:
    case S_STOPPING:
        return handleEventOnWorking(context, event);
    case S_FINAL:
        return handleEventOnFinal(context, event);
    default:
        break;
   }

   return USI_UNKNOWN_EVENT;
}

///////////////////////////////////////////////////////////////////////
inline Status Procedure::stopOnWorking(TransactionContext& context, Status cause)
{
    ActionStatus status = schedAction.stop(context, cause);
    if(status.isWorking())
    {
        state = S_STOPPING;
        return status;
    }

    return gotoFinal(context, status);
}

///////////////////////////////////////////////////////////////////////
Status Procedure::stop(TransactionContext& context, Status cause)
{
   __AUTO_SWITCH();

   switch(state)
   {
   case S_WORKING:
       return stopOnWorking(context, cause);
   case S_STOPPING:
   case S_FINAL:
       return USI_CONTINUE;
   default:
       break;
   }

   return cause;
}

///////////////////////////////////////////////////////////////////////
void Procedure::kill(TransactionContext& context, Status cause)
{
    __AUTO_SWITCH();

    switch(state)
    {
    case S_WORKING:
    case S_STOPPING:
        doKill(schedAction, context, cause);
        break;
    case S_FINAL:
        doKill(finalAction, context, cause);
        break;
    default:
        break;
    }
}
