#ifndef INCL_USI_SwitchCase11_20140311152758_H__
#define INCL_USI_SwitchCase11_20140311152758_H__

#include "l0-infra/trans-dsl/sched/action/SchedSwitchCaseAction.h"

namespace details
{
    template <typename... T_ACTION_PATHS> struct MultiPathCollection;

    template <typename T_HEAD, typename... T_TAIL>
    struct MultiPathCollection<T_HEAD, T_TAIL...> : MultiPathCollection<T_TAIL...>
    {
    protected:
        void init()
        {
            MultiPathCollection<T_TAIL...>::pushBackActionPath(path);
            MultiPathCollection<T_TAIL...>::init();
        }
    private:
        T_HEAD path;
    };

    template <>
    struct MultiPathCollection<> : SchedSwitchCaseAction
    {
    protected:
        void init() {}
    };

    template <typename... T_ACTION_PATHS>
    struct SWITCH__
        : MultiPathCollection< T_ACTION_PATHS...>
    {
        SWITCH__()
        {
            MultiPathCollection< T_ACTION_PATHS...>::init();
        }
    };
}
#endif

