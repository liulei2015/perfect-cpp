/*
 * RuntimeContextAutoSwitch.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef RUNTIMECONTEXTAUTOSWITCH_H_
#define RUNTIMECONTEXTAUTOSWITCH_H_

#include "l0-infra/trans-dsl/sched/concept/RuntimeContextInfo.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/RuntimeContextInfo.h"

struct RuntimeContext;
struct TransactionContext;

struct RuntimeContextAutoSwitch
{
   RuntimeContextAutoSwitch
        ( RuntimeContext& newRuntimeContext
        , RuntimeContext*& parentKeeper
        , TransactionContext& context)
       : parentKeeper(parentKeeper)
       , contextInfo(context.getRuntimeContextInfo())
   {
           parentKeeper = contextInfo.getRuntimeContext();
           contextInfo.setRuntimeContext(newRuntimeContext);
   }

   // inline for performance
   ~RuntimeContextAutoSwitch()
   {
       contextInfo.setRuntimeContext(*parentKeeper);
   }

private:
   RuntimeContext*& parentKeeper;
   RuntimeContextInfo& contextInfo;
};

#endif /* RUNTIMECONTEXTAUTOSWITCH_H_ */

