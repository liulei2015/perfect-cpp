#ifndef INCL_USI_MultiListenerHelper_H
#define INCL_USI_MultiListenerHelper_H

#include "l0-infra/base/RepeatMacros.h"
#include "l0-infra/trans-dsl/listener/MultiTransListener.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

////////////////////////////////////////////////////////////////
#define __LISTENER_ARG(n)              LISTENER ## n   

#define __LISTENER_TMPL_ARG(n)       typename __LISTENER_ARG(n)
#define __LISTENER_TMPL_ARGS(n)      __LISTENER_TMPL_ARG(n),

//////////////////////////////////////////////////////////////////////////
#define __REPEAT_LISTENER_ARGS(n)  __LISTENER_ARG(n),
#define LISTENER_ARGS(n) SIMPLE_REPEAT(n, __REPEAT_LISTENER_ARGS)

#define DECL_LISTENER_TMPL_ARGS(n) REPEAT(n, __LISTENER_TMPL_ARGS, __LISTENER_TMPL_ARG)

//////////////////////////////////////////////////////////////////////////
#define __ADD_LISTENER(n)  addListener(listener ## n);
#define ADD_LISTENER(n) SIMPLE_REPEAT(n, __ADD_LISTENER)

//////////////////////////////////////////////////////////////////////////
namespace details
{
    template <typename T_LISTENER>
    struct LINKED_LISTENER__ : LinkedTransListener
    {
    	LINKED_LISTENER__() : LinkedTransListener(listener) {}

    private:
    	T_LISTENER listener;
    };
}

////////////////////////////////////////////////////////////////
#define __LISTENER_MEMBER_DEF(n)  ::details::LINKED_LISTENER__< __LISTENER_ARG(n) > listener ## n;
#define DECL_LISTENER_MEMBERS(n) SIMPLE_REPEAT(n, __LISTENER_MEMBER_DEF)

////////////////////////////////////////////////////////////////
struct DummyListener{};

#define __DUMMY_LISTENER(n)  DummyListener
#define __DUMMY_LISTENERS(n) DummyListener,
#define DUMMY_LISTENERS(n) REPEAT(n, __DUMMY_LISTENERS, __DUMMY_LISTENER)

////////////////////////////////////////////////////////////////
#define __LISTENER_PARTIAL_COLLECTION(n)                                  \
namespace details                                                         \
{                                                                         \
    template <DECL_LISTENER_TMPL_ARGS(n)>                                \
    struct MultiListeners __PARTIAL_20_##n(LISTENER_ARGS, DUMMY_LISTENERS) \
        : MultiTransListener                                              \
    {                                                                     \
        MultiListeners()                                                  \
        {                                                                 \
            ADD_LISTENER(n)                                               \
        }                                                                 \
    private:                                                              \
        DECL_LISTENER_MEMBERS(n)                                          \
    };                                                                    \
}

////////////////////////////////////////////////////////////////
__LISTENER_PARTIAL_COLLECTION(20)
__LISTENER_PARTIAL_COLLECTION(19)
__LISTENER_PARTIAL_COLLECTION(18)
__LISTENER_PARTIAL_COLLECTION(17)
__LISTENER_PARTIAL_COLLECTION(16)
__LISTENER_PARTIAL_COLLECTION(15)
__LISTENER_PARTIAL_COLLECTION(14)
__LISTENER_PARTIAL_COLLECTION(13)
__LISTENER_PARTIAL_COLLECTION(12)
__LISTENER_PARTIAL_COLLECTION(11)
__LISTENER_PARTIAL_COLLECTION(10)
__LISTENER_PARTIAL_COLLECTION(9)
__LISTENER_PARTIAL_COLLECTION(8)
__LISTENER_PARTIAL_COLLECTION(7)
__LISTENER_PARTIAL_COLLECTION(6)
__LISTENER_PARTIAL_COLLECTION(5)
__LISTENER_PARTIAL_COLLECTION(4)
__LISTENER_PARTIAL_COLLECTION(3)
__LISTENER_PARTIAL_COLLECTION(2)
__LISTENER_PARTIAL_COLLECTION(1)

////////////////////////////////////////////////////////////////
#define __WITH_DUMMY_LISTNER(n) __LISTENER_TMPL_ARG(n) = DummyListener
#define __WITH_DUMMY_LISTNERS(n) __WITH_DUMMY_LISTNER(n),

#define DECL_DUMMY_LISTNERS(n) REPEAT(n, __WITH_DUMMY_LISTNERS, __WITH_DUMMY_LISTNER)

///////////////////////////////////////////////////////////////
#define DECL_ALL_LISTENER_ARGS(n) REPEAT(n, __REPEAT_LISTENER_ARGS, __LISTENER_ARG)

/////////////////////////////////////////////////////////////////////////////////
#define __DEF_GENERIC_MULTI_LISTENER(n)                                                 \
namespace details                                                                       \
{                                                                                       \
    template <bool IS_OPT, DECL_DUMMY_LISTNERS(n)>                                      \
    struct LISTENERS__                                                                  \
    : MultiListeners<DECL_ALL_LISTENER_ARGS(n)>                                         \
    {                                                                                   \
        OVERRIDE(bool shouldOptimize() const)                                           \
        {                                                                               \
            return IS_OPT;                                                              \
        }                                                                               \
    };                                                                                  \
}

/////////////////////////////////////////////////////////////////////////////////
__DEF_GENERIC_MULTI_LISTENER(20)

//////////////////////////////////////////////////////////////////////////
#define __listeners(IS_OPT, ...) ::details::LISTENERS__< IS_OPT, __VA_ARGS__ >
#define __def_listeners(...) struct : __listeners(false, __VA_ARGS__) {}
#define __def_listeners_opt(...) struct : __listeners(true, __VA_ARGS__) {}

#endif

