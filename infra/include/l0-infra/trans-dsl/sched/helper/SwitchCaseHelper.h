/*
 * SwitchCaseHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SWITCHCASEHELPER_H_
#define SWITCHCASEHELPER_H_

#include "l0-infra/base/Config.h"
#include "l0-infra/trans-dsl/sched/action/ActionPath.h"

#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#if __SUPPORT_VARIADIC_TEMPLATES
#include "l0-infra/trans-dsl/sched/helper/11/SwitchCase11.h"
#else
#include "l0-infra/trans-dsl/sched/helper/98/SwitchCase98.h"
#endif
#include "string.h"

namespace details
{
    template <typename PRED, typename T_ACTION>
    struct CASE__ : ActionPath
    {
        CASE__() : ActionPath(action){}

        OVERRIDE(bool shouldExecute(const TransactionInfo& info))
        {
            return pred(info);
        }

    private:
        T_ACTION action;
        PRED pred;
    };

    template <typename PRED, typename T_ACTION>
    struct OPTIONAL__
        : SchedAction
    {
        OVERRIDE(Status exec(TransactionContext& context))
        {
            if(!pred(context)) return USI_SUCCESS;
            return action.exec(context);
        }

        OVERRIDE(Status handleEvent(TransactionContext& context, const Event& event))
        {
            return action.handleEvent(context, event);
        }

        OVERRIDE(Status stop(TransactionContext& context, const Status cause))
        {
            return action.stop(context, cause);
        }

        OVERRIDE(void   kill(TransactionContext& context, const Status cause))
        {
            action.kill(context, cause);
        }

    private:
        T_ACTION action;
        PRED pred;
    };
}

//////////////////////////////////////////////////////////////////
#define __switch(...) \
    ::details::SWITCH__< __VA_ARGS__ >

#define __case(...) \
    ::details::CASE__< __VA_ARGS__ >

#define __optional(...) ::details::OPTIONAL__< __VA_ARGS__ >

//////////////////////////////////////////////////////////////////

#endif /* SWITCHCASEHELPER_H_ */

