#ifndef INCL_USI_SwitchCase98_20140311152915_H__
#define INCL_USI_SwitchCase98_20140311152915_H__

#include "l0-infra/trans-dsl/sched/action/SchedSwitchCaseAction.h"
#include "l0-infra/trans-dsl/utils/DummyAction.h"

namespace details
{
    template <typename ACTION_PATH1, typename ACTION_PATH2, typename ACTION_PATH3, typename ACTION_PATH4>
    struct MultiPathCollection : SchedSwitchCaseAction
    {
        MultiPathCollection()
        {
            pushBackActionPath(path1);
            pushBackActionPath(path2);
            pushBackActionPath(path3);
            pushBackActionPath(path4);
        }

    private:
        ACTION_PATH1 path1;
        ACTION_PATH2 path2;
        ACTION_PATH3 path3;
        ACTION_PATH4 path4;
    };

    template <typename ACTION_PATH1, typename ACTION_PATH2, typename ACTION_PATH3>
    struct MultiPathCollection<ACTION_PATH1, ACTION_PATH2, ACTION_PATH3, DummyAction>
        : SchedSwitchCaseAction
    {
        MultiPathCollection()
        {
            pushBackActionPath(path1);
            pushBackActionPath(path2);
            pushBackActionPath(path3);
        }

    private:
        ACTION_PATH1 path1;
        ACTION_PATH2 path2;
        ACTION_PATH3 path3;
    };

    template <typename ACTION_PATH1, typename ACTION_PATH2>
    struct MultiPathCollection<ACTION_PATH1, ACTION_PATH2, DummyAction, DummyAction>
        : SchedSwitchCaseAction
    {
        MultiPathCollection()
        {
            pushBackActionPath(path1);
            pushBackActionPath(path2);
        }

    private:
        ACTION_PATH1 path1;
        ACTION_PATH2 path2;
    };

    template <typename ACTION_PATH1>
    struct MultiPathCollection<ACTION_PATH1, DummyAction, DummyAction, DummyAction>
        : SchedSwitchCaseAction
    {
        MultiPathCollection()
        {
            pushBackActionPath(path1);
        }

    private:
        ACTION_PATH1 path1;
    };

    /////////////////////////////////////////////////////////////////////
    template < typename ACTION_PATH1
        , typename ACTION_PATH2 = DummyAction
        , typename ACTION_PATH3 = DummyAction
        , typename ACTION_PATH4 = DummyAction>
    struct SWITCH__
        : MultiPathCollection
        < ACTION_PATH1
        , ACTION_PATH2
        , ACTION_PATH3
        , ACTION_PATH4>
    {
    };
}

#endif

