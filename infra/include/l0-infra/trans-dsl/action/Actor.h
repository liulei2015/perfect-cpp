/*
 * Actor.h
 *
 * Created on: Jul 14, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTOR_H_
#define ACTOR_H_

#include "l0-infra/base/Assertions.h"

#define BASE_ACTION_NAME(P_ACTION) P_ACTION##Base

#define USE_ACTOR(P_ACTOR_TYPE) \
   virtual P_ACTOR_TYPE* getActor(const TransactionInfo&) = 0

#define USE_NAMED_ACTOR(P_ACTOR_TYPE) \
    virtual P_ACTOR_TYPE* get##P_ACTOR_TYPE(const TransactionInfo&) = 0

#define ACTOR() getActor(trans)
#define NAMED_ACTOR(P_ACTOR_TYPE) get##P_ACTOR_TYPE(trans)

#define GET_ACTOR(p_type, p_name) \
    p_type* p_name = ACTOR();     \
    USI_ASSERT_VALID_PTR(p_name)

#define GET_NAMED_ACTOR(p_type, p_name) \
    p_type* p_name = NAMED_ACTOR(p_type);     \
    USI_ASSERT_VALID_PTR(p_name)

#define DECL_NAMED_ACTOR(P_ACTOR_TYPE) \
    P_ACTOR_TYPE* get##P_ACTOR_TYPE(const TransactionInfo& trans)

#define __IMPL_ACTOR(P_ACTOR_TYPE, ACTOR_NAME, CREATER_TYPE) \
      P_ACTOR_TYPE* get##ACTOR_NAME(const TransactionInfo& trans) \
      { return CREATER_TYPE()(trans); }                    

#define IMPL_ACTOR(P_ACTOR_TYPE, CREATER_TYPE) \
    __IMPL_ACTOR(P_ACTOR_TYPE, Actor, CREATER_TYPE)

#define IMPL_NAMED_ACTOR(P_ACTOR_TYPE, CREATER_TYPE) \
    __IMPL_ACTOR(P_ACTOR_TYPE, P_ACTOR_TYPE, CREATER_TYPE)

#define __ACTOR_BASED_ACTION_NAME(P_BASE_ACTION) \
    P_BASE_ACTION

#define __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION) \
    struct __ACTOR_BASED_ACTION_NAME(P_BASE_ACTION) : BASE_ACTION_NAME(P_BASE_ACTION) 

#define DEF_ACTOR_BASED_ACTION(P_ACTOR_TYPE, P_BASE_ACTION) \
   template <typename P_ACTOR>                             \
   __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION)                \
   {                                                       \
        IMPL_ACTOR(P_ACTOR_TYPE, P_ACTOR)                  \
   }

#define DEF_ACTOR_BASED_ACTION_2(P_ACTOR1_TYPE, P_ACTOR2_TYPE, P_BASE_ACTION) \
   template <typename P_ACTOR1, typename P_ACTOR2>         \
   __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION)                \
   {                                                       \
      IMPL_ACTOR(P_ACTOR1_TYPE, P_ACTOR1)                  \
      IMPL_NAMED_ACTOR(P_ACTOR2_TYPE, P_ACTOR2)            \
   }

#define DEF_ACTOR_BASED_ACTION_3(P_ACTOR1_TYPE, P_ACTOR2_TYPE, P_ACTOR3_TYPE, P_BASE_ACTION)  \
    template <typename P_ACTOR1, typename P_ACTOR2, typename P_ACTOR3>         \
    __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION)                \
    {                                                       \
       IMPL_ACTOR(P_ACTOR1_TYPE, P_ACTOR1)                  \
       IMPL_NAMED_ACTOR(P_ACTOR2_TYPE, P_ACTOR2)            \
       IMPL_NAMED_ACTOR(P_ACTOR3_TYPE, P_ACTOR3)            \
    }

#define DEF_NAMED_ACTOR_ACTION(P_ACTOR_TYPE, P_BASE_ACTION) \
    template <typename P_ACTOR>                             \
    __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION)                \
   {                                                        \
      IMPL_NAMED_ACTOR(P_ACTOR_TYPE, P_ACTOR)               \
   }

#define DEF_NAMED_ACTOR_ACTION_2(P_ACTOR_TYPE1, P_ACTOR_TYPE2, P_BASE_ACTION) \
    template <typename P_ACTOR1, typename P_ACTOR2>          \
    __DECL_ACTOR_BASED_ACTION(P_BASE_ACTION)                 \
    {                                                        \
        IMPL_NAMED_ACTOR(P_ACTOR_TYPE1, P_ACTOR1)            \
        IMPL_NAMED_ACTOR(P_ACTOR_TYPE2, P_ACTOR2)            \
    }

#endif /* ACTOR_H_ */

