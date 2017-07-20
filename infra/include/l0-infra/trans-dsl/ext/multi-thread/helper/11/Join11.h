#ifndef INCL_USI_Join11_20140311153650_H__
#define INCL_USI_Join11_20140311153650_H__

#include "l0-infra/trans-dsl/ext/multi-thread/action/SchedJoinAction.h"

namespace details
{
    template <ActionThreadId... T_TIDS> struct ThreadAdder;

    template <ActionThreadId T_HEAD, ActionThreadId... T_TAIL>
    struct ThreadAdder<T_HEAD, T_TAIL...>
    {
        void operator()(SchedJoinAction& actions) const
        {
            actions.addJoinThread(T_HEAD);
            ThreadAdder<T_TAIL...>()(actions);
        }
    };

    template <> struct ThreadAdder<>
    {
        void operator()(SchedJoinAction&) const {}
    };

    template <ActionThreadId... T_TIDS>
    struct JOIN__ : SchedJoinAction
    {
        JOIN__()
        {
            ThreadAdder< T_TIDS...>()(*this);
        }
    };
}

#endif

