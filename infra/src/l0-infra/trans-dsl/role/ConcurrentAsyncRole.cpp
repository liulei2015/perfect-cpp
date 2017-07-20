/*
 * ConcurrentAsyncRole.cc
 *
 *  Created on: Aug 26, 2012
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/role/ConcurrentAsyncRole.h"

////////////////////////////////////////////////////////////////
#define FOREACH_ROLE(i) for(int i=0; i<MAX_NUM_OF_CONCURRENT_ROLES; ++i)


ConcurrentAsyncRole::ConcurrentAsyncRole()
{
    FOREACH_ROLE(i) roles[i] = 0;
}

////////////////////////////////////////////////////////////////
Status ConcurrentAsyncRole::addAsyncRole(AsyncRole& action)
{
   FOREACH_ROLE(i)
   {
      if(roles[i] == 0)
      {
         roles[i] = &action;
         return USI_SUCCESS;
      }
   }

   return USI_OUT_OF_SCOPE;
}

////////////////////////////////////////////////////////////////
bool ConcurrentAsyncRole::hasWorkingActions() const
{
   FOREACH_ROLE(i)
   {
      if(roles[i] != 0) return true;
   }

   return false;
}

////////////////////////////////////////////////////////////////
namespace
{
   bool hasActionDone(Status status)
   {
      return status != USI_UNKNOWN_EVENT && status != USI_CONTINUE;
   }
}

////////////////////////////////////////////////////////////////
Status ConcurrentAsyncRole::handleEventOn(const Event& event, int n)
{
   if(roles[n] == 0) return USI_UNKNOWN_EVENT;

   Status status = roles[n]->handleEvent(event);
   if (hasActionDone(status))
   {
      roles[n] = 0;
   }

   return status;
}

////////////////////////////////////////////////////////////////
Status ConcurrentAsyncRole::doHandleEvent(const Event& event)
{
   FOREACH_ROLE(i)
   {
      Status status = handleEventOn(event, i);
      if (status != USI_UNKNOWN_EVENT)
      {
         return status;
      }
   }

   return USI_UNKNOWN_EVENT;
}

////////////////////////////////////////////////////////////////
Status ConcurrentAsyncRole::handleEvent(const Event& event)
{
   Status status = doHandleEvent(event);
   if (IS_FAILED_STATUS(status))
   {
      stop();
   }

   if (status == USI_SUCCESS)
   {
      return hasWorkingActions() ? USI_CONTINUE : USI_SUCCESS;
   }

   return status;
}

////////////////////////////////////////////////////////////////
void ConcurrentAsyncRole::stop()
{
   FOREACH_ROLE(i)
   {
      if(roles[i] != 0)
      {
         roles[i]->stop();
         roles[i] = 0;
      }
   }

   doStop();
}

