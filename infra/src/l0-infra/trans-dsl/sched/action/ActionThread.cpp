/*
 * ActionThread.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/sched/action/ActionThread.h"
#include "l0-infra/trans-dsl/utils/GofState.h"
#include "l0-infra/trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "l0-infra/event/concept/Event.h"
//
//__DEF_STATE_INTERFACE(ActionThread)
//{
//   virtual bool isWorking() const
//   {
//      return false;
//   }
//};
//
//__DEF_STATE_CLASS(ActionThread, Idle)
//{
//   virtual Status exec(ActionThread& __THIS__, TransactionContext& context)
//   {
//      ActionStatus status = __THIS__.ROLE(SchedAction).exec(context);
//      if(status.isWorking())
//      {
//         return __THIS__.__GOTO_STATE(Working);
//      }
//
//      return __THIS__.__GOTO_STATE(Done);
//   }
//};
//
//__DEF_BASE_STATE_CLASS(ActionThread, WorkingState)
//{
//   virtual Status handleEvent(ActionThread& __THIS__, TransactionContext& context, const Event& event)
//   {
//      ActionStatus status = __THIS__.ROLE(SchedAction).handleEvent(context, event);
//      if(status.isWorking())
//      {
//         return status;
//      }
//
//      return __THIS__.__GOTO_STATE(Done);
//   }
//
//   void   kill(ActionThread& __THIS__, TransactionContext& context, const Status cause)
//   {
//      __THIS__.ROLE(SchedAction).kill(context, cause);
//      __THIS__.____GOTO_STATE(Done, USI_SUCCESS);
//   }
//
//   bool isWorking() const
//   {
//      return true;
//   }
//};
//
//__DEF_DERIVED_STATE_CLASS(ActionThread, Working, WorkingState)
//{
//   Status stop(ActionThread& __THIS__, TransactionContext& context, const Status cause)
//   {
//      ActionStatus status = __THIS__.ROLE(SchedAction).stop(context, cause);
//      if(status.isWorking())
//      {
//         return __THIS__.__GOTO_STATE(Stopping);
//      }
//
//      return __THIS__.__GOTO_STATE(Done);
//   }
//};
//
//__DEF_DERIVED_STATE_CLASS(ActionThread, Stopping, WorkingState)
//{
//   Status stop(ActionThread&, TransactionContext&, const Status)
//   {
//      return USI_CONTINUE;
//   }
//};
//
//__DEF_STATE_CLASS(ActionThread, Done)
//{
//   virtual Status enter(ActionThread& __THIS__, TransactionContext&, const ActionStatus status)
//   {
//      __THIS__.reportFailure(status);
//
//      return status;
//   }
//};
//
//__DEF_STATE(ActionThread, Idle)
//__DEF_STATE(ActionThread, Working)
//__DEF_STATE(ActionThread, Stopping)
//__DEF_STATE(ActionThread, Done)

ActionThread::ActionThread(SchedAction& schedAction)
  : schedAction(schedAction)
  , state(IDLE_STATE)
{
}

///////////////////////////////////////////////////////////////////
void ActionThread::init()
{
    SimpleRuntimeContext::init();
    state = IDLE_STATE;
}

///////////////////////////////////////////////////////////////////
inline Status ActionThread::onDone(const ActionStatus status)
{
	if(status.isFailed())
	{
		reportFailure(status);
	}

   state = IDLE_STATE;

   return status;
}

///////////////////////////////////////////////////////////////////
struct ActionThread::AutoSwitch : RuntimeContextAutoSwitch
{
   AutoSwitch(ActionThread& thread, TransactionContext& context)
        : RuntimeContextAutoSwitch(thread, thread.parent, context)
   {
   }
};

#define __AUTO_SWITCH() AutoSwitch autoSwitch(*this, context)

///////////////////////////////////////////////////////////////////
Status ActionThread::exec(TransactionContext& context)
{
    init();

   __AUTO_SWITCH();

   ActionStatus status = schedAction.exec(context);
   if(status.isWorking())
   {
	   state = WORKING_STATE;
	   return status;
   }

   return onDone(status);
}

///////////////////////////////////////////////////////////////////
inline Status ActionThread::doHandleEvent(TransactionContext& context, const Event& event)
{
    ActionStatus status = schedAction.handleEvent(context, event);
    if(status.isWorking())
    {
       return status;
    }

    return onDone(status);
}

///////////////////////////////////////////////////////////////////
Status ActionThread::handleEvent(TransactionContext& context, const Event& event)
{
   __AUTO_SWITCH();

   Status status = USI_CONTINUE;
   while(!event.isConsumed() && status == USI_CONTINUE)
   {
     status = doHandleEvent(context, event);
   }

   return status;
}

///////////////////////////////////////////////////////////////////
Status ActionThread::stop(TransactionContext& context, const Status cause)
{
	if(state == STOPPING_STATE) return USI_CONTINUE;

	if(state != WORKING_STATE) return cause;

   __AUTO_SWITCH();

   ActionStatus status = schedAction.stop(context, cause);
   if(status.isWorking())
   {
	   state = STOPPING_STATE;
	   return status;
   }

   return onDone(status);
}

///////////////////////////////////////////////////////////////////
void ActionThread::kill(TransactionContext& context, const Status cause)
{
	schedAction.kill(context, cause);
}
