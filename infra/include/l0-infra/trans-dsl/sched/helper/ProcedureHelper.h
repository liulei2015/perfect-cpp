/*
 * ProcedureHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef PROCEDUREHELPER_H_
#define PROCEDUREHELPER_H_

#include "l0-infra/trans-dsl/sched/concept/SchedAction.h"
#include "l0-infra/trans-dsl/utils/SimpleRuntimeContext.h"
#include "l0-infra/trans-dsl/sched/action/NilFinalAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/trans-dsl/sched/concept/FinalAction.h"

namespace details
{
    #define __PROCEDURE_AUTO_SWITCH()  AutoSwitch autoSwitch(*this, context)

   template<typename T_ACTION, typename T_FINAL_ACTION, bool IS_PROTECTED>
   struct GenericProcedure : private SimpleRuntimeContext, SchedAction
   {
        GenericProcedure()
        : state(S_IDLE)
        {
        }

        OVERRIDE(Status exec(TransactionContext& context))
        {
            init();

           __PROCEDURE_AUTO_SWITCH();

           ActionStatus status = schedAction.exec(context);
           if(status.isWorking())
           {
               state = S_WORKING;
               return status;
           }

           return gotoFinal(context, status);
        }

        OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
        {
            __PROCEDURE_AUTO_SWITCH();

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

        OVERRIDE(Status stop(TransactionContext& context, const Status cause))
        {
            __PROCEDURE_AUTO_SWITCH();

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

        OVERRIDE(void   kill(TransactionContext& context, const Status cause))
        {
            __PROCEDURE_AUTO_SWITCH();

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

    private:
        OVERRIDE(bool shouldReportParent() const)
        {
            return !IS_PROTECTED;
        }

        void init()
        {
            SimpleRuntimeContext::init();
            state = S_IDLE;
        }

        Status gotoFinal(TransactionContext& context, const ActionStatus result)
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

        Status gotoDone(TransactionContext&, const ActionStatus result)
        {
            if(result.isFailed())
            {
                return result;
            }

            return IS_PROTECTED ? (Status)result : getFinalStatus();
        }

        Status stopOnWorking(TransactionContext& context, Status cause)
        {
            ActionStatus status = schedAction.stop(context, cause);
            if(status.isWorking())
            {
                state = S_STOPPING;
                return status;
            }

            return gotoFinal(context, status);
        }

        Status handleEventOnFinal(TransactionContext& context, const Event& event)
        {
            ActionStatus status = finalAction.handleEvent(context, event);
            if(status.isWorking())
            {
                return status;
            }

            return gotoDone(context, status);
        }

        Status handleEventOnWorking(TransactionContext& context, const Event& event)
        {
            ActionStatus status = schedAction.handleEvent(context, event);
            if(status.isWorking())
            {
                return status;
            }

            return gotoFinal(context, status);
        }

    private:
       void doKill(FinalAction& action, TransactionContext& context, Status cause)
       {
           action.kill(context, cause);
           gotoDone(context, USI_SUCCESS);
       }

       Status getFinalStatus() const
       {
           return IS_FAILED_STATUS(objectStatus) ? objectStatus : USI_SUCCESS;
       }

    private:
        enum { S_IDLE, S_WORKING, S_STOPPING, S_FINAL} state;

        struct AutoSwitch : RuntimeContextAutoSwitch
        {
            AutoSwitch(GenericProcedure& proc, TransactionContext& context)
                 : RuntimeContextAutoSwitch(proc, proc.parent, context)
            {
            }
        };

   private:
        T_ACTION schedAction;
        T_FINAL_ACTION finalAction;
   };

   template<typename T_ACTION, typename T_FINAL_ACTION = NilFinalAction>
   struct PROCEDURE__ : GenericProcedure<T_ACTION, T_FINAL_ACTION, false>
   {
   };

   template<typename T_ACTION, typename T_FINAL_ACTION = NilFinalAction>
   struct PROTECTED_PROC__: GenericProcedure<T_ACTION, T_FINAL_ACTION, true>
   {
   };

   template <typename T_ACTION>
   struct FINALLY__ : FinalAction
   {
       OVERRIDE(Status exec(TransactionContext& context))
       {
           return action.exec(context);
       }

       OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
       {
           return action.handleEvent(context, event);
       }

       OVERRIDE(void kill(TransactionContext& context, const Status cause))
       {
           action.kill(context, cause);
       }

   private:
      T_ACTION action;
   };
}

/////////////////////////////////////////////////////////////////////////////
#define __procedure(...) \
    ::details::PROCEDURE__< __VA_ARGS__ >

#define __prot_procedure(...) \
    ::details::PROTECTED_PROC__< __VA_ARGS__ >

#define __finally(...) \
    ::details::FINALLY__<__VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////

#endif /* PROCEDUREHELPER_H_ */

