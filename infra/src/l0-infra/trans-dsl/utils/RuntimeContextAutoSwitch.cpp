/*
 * RuntimeContextAutoSwitch.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/utils/RuntimeContextAutoSwitch.h"
#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
#include "l0-infra/trans-dsl/sched/concept/RuntimeContextInfo.h"

//RuntimeContextAutoSwitch::RuntimeContextAutoSwitch
//   ( RuntimeContext& newRuntimeContext
//   , RuntimeContext*& parentKeeper
//   , TransactionContext& context)
//   : parentKeeper(parentKeeper)
//   , contextInfo(dci::unknown_cast<RuntimeContextInfo>(&context))
//{
//   if(contextInfo == 0)
//   {
//      parentKeeper = 0;
//   }
//   else
//   {
//      parentKeeper = contextInfo->getRuntimeContext();
//      contextInfo->setRuntimeContext(newRuntimeContext);
//   }
//}

