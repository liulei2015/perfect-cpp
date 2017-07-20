/*
 * GofState.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef GOFSTATE_H_
#define GOFSTATE_H_

#include <l0-infra/base/Singleton.h>
#include <l0-infra/base/Keywords.h>
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

struct TransactionContext;
struct Event;

template <typename T>
struct GofState
{
   virtual ~GofState() {}

   virtual Status enter(T&, TransactionContext&, const ActionStatus status)
   {
      return status;
   }

   virtual Status exec(T&, TransactionContext&)
   {
      return USI_FATAL_BUG;
   }

   virtual Status handleEvent(T&, TransactionContext&, const Event&)
   {
      return USI_UNKNOWN_EVENT;
   }

   virtual Status stop(T&, TransactionContext&, const Status)
   {
      return USI_SUCCESS;
   }

   virtual void   kill(T&, TransactionContext&, const Status)
   {
   }
};

#define __DEF_STATE_INTERFACE(object) \
     struct object::State : GofState<object>

#define __DECL_STATE_INTERFACE(object)   \
    __DEF_STATE_INTERFACE(object) {}

///////////////////////////////////////////////////////////////////
#define __DEF_BASE_STATE_CLASS(object, S) \
struct object::S : object::State

#define __DEF_DERIVED_STATE_CLASS(object, S, base) \
    DEF_SINGLETON(object::S) EXTENDS(object::base)

#define __DEF_STATE_CLASS(object, S) \
   __DEF_DERIVED_STATE_CLASS(object, S, State)

#define __DEF_BASE_STATE(object, S) \
struct object::S : object::State

///////////////////////////////////////////////////////////////////
#define ____GOTO_STATE(S, status) goto##S##State(context, status)
#define __GOTO_STATE(S) ____GOTO_STATE(S, status)

#define __DEF_STATE(object, S) \
Status object::goto##S##State(TransactionContext& context, const Status status) \
{                                                                                  \
   state = &S::getInstance();                                                       \
   return state->enter(*this, context, status);                                    \
}

#endif /* GOFSTATE_H_ */

