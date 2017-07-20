#ifndef INCL_USI_Concurrent11_20140311151953_H__
#define INCL_USI_Concurrent11_20140311151953_H__

#include "l0-infra/trans-dsl/sched/action/SchedConcurrentAction.h"
#include "l0-infra/trans-dsl/sched/helper/LinkedThreadHelper.h"
#include "l0-infra/trans-dsl/sched/helper/VoidHelper.h"

namespace details
{
    template <typename... T_ACTIONS> struct GenericConcurrent;

    template <typename T_HEAD, typename... T_TAIL>
    struct GenericConcurrent<T_HEAD, T_TAIL...> : GenericConcurrent<T_TAIL...>
    {
    protected:
        void init()
        {
            GenericConcurrent<T_TAIL...>::addThread(action);
            GenericConcurrent<T_TAIL...>::init();
        }
    private:
        details::LINKED_THREAD__< T_HEAD > action;
    };

    template <>
    struct GenericConcurrent<> : SchedConcurrentAction
    {
    protected:
        void init()
        {
        }
    };

    template <typename... T_ACTIONS>
    struct CONCURRENT__ : GenericConcurrent<T_ACTIONS...>
    {
        CONCURRENT__()
        {
            GenericConcurrent<T_ACTIONS...>::init();
        }
    };

    ///////////////////////////////////////////////////////////////////
    template <typename... T_ACTIONS> struct VoidGenericConcurrent;

    template <typename T_HEAD, typename... T_TAIL>
    struct VoidGenericConcurrent<T_HEAD, T_TAIL...> : VoidGenericConcurrent<T_TAIL...>
    {
    protected:
        void init()
        {
            VoidGenericConcurrent<T_TAIL...>::addThread(action);
            VoidGenericConcurrent<T_TAIL...>::init();
        }
    private:
        details::LINKED_THREAD__< details::VOID__< T_HEAD > > action;
    };

    template <>
    struct VoidGenericConcurrent<> : SchedConcurrentAction
    {
    protected:
        void init() {}
    };

    template <typename... T_ACTIONS>
    struct VOID_CONCURRENT__ : VoidGenericConcurrent<T_ACTIONS...>
    {
        VOID_CONCURRENT__()
        {
            VoidGenericConcurrent<T_ACTIONS...>::init();
        }
    };
}

#endif

