/*
 * SimpleRuntimeContext.cc
 *
 *  Created on: Apr 22, 2013
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/utils/SimpleRuntimeContext.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

////////////////////////////////////////////////////////////////
SimpleRuntimeContext::SimpleRuntimeContext(Status parentFailure)
   : parent(0)
   , objectStatus(parentFailure)
{
}

////////////////////////////////////////////////////////////////
void SimpleRuntimeContext::init()
{
    parent = 0;
    objectStatus = USI_SUCCESS;
}

////////////////////////////////////////////////////////////////
void SimpleRuntimeContext::reportFailure(Status failure)
{
   if(!ActionStatus(failure).isFailed())
   {
      return;
   }

   objectStatus = failure;

   if(shouldReportParent() && parent != 0)
   {
      parent->reportFailure(failure);
   }
}
