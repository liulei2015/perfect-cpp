/*
 * LoopHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef LOOPHELPER_H_
#define LOOPHELPER_H_

#include "l0-infra/trans-dsl/sched/action/SchedLoopAction.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include <l0-infra/base/Placement.h>
#include "l0-infra/trans-dsl/sched/action/Procedure.h"

namespace details
{

   template <typename T_PRED, typename T_ACTION>
   struct LoopProcedure : private LoopCondCheckAction, Procedure
   {
      LoopProcedure(T_PRED& pred) 
          : Procedure(c_schedAction, static_cast<LoopCondCheckAction&>(*this), true)
          , pred(pred) 
      {}

   private:
       T_ACTION c_schedAction;

   private:
      OVERRIDE(bool shouldExecute(TransactionContext& context) const)
      {
         return pred(context);
      }

      T_PRED& pred;
   };

   template <typename T_PRED, typename T_ACTION>
   struct GenericLoop : SchedLoopAction
   {
      GenericLoop() : cons(false) {}

   private:
      typedef LoopProcedure<T_PRED, T_ACTION> Proc;

   private:
      Placement<Proc> proc;
      bool cons;

      OVERRIDE(void reset())
      {
         if(cons) proc.destroy();

         new (proc.alloc()) Proc(pred);

         cons = true;
      }

      ROLE_PROTO_TYPE(SchedAction)
      {
         return *proc;
      }

   protected:
      T_PRED pred;
   };


   /////////////////////////////////////////////////////////////
   template<typename T_PRED, typename T_ACTION>
   struct LOOP0__ : GenericLoop<T_PRED, T_ACTION>
   {
   private:
      typedef GenericLoop<T_PRED, T_ACTION> Parent;

      bool shouldExecute(TransactionContext& context)
      {
         return Parent::pred(context);
      }
   };

   /////////////////////////////////////////////////////////////
   template<typename T_PRED, typename T_ACTION>
   struct LOOP1__ : GenericLoop<T_PRED, T_ACTION>
   {
   private:
      typedef GenericLoop<T_PRED, T_ACTION> Parent;

      bool shouldExecute(TransactionContext&)
      {
         return true;
      }
   };
}

///////////////////////////////////////////////////////////////
#define __loop0(...) \
    ::details::LOOP0__< __VA_ARGS__ >

#define __loop1(...) \
    ::details::LOOP1__< __VA_ARGS__ >

///////////////////////////////////////////////////////////////

#endif /* LOOPHELPER_H_ */

