/*
 * AbstractTransMutexScheduler.cc
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/ext/mutex/impl/AbstractTransMutexScheduler.h"
#include "l0-infra/trans-dsl/ext/mutex/def/TransMutexAvailMsg.h"
#include "l0-infra/trans-dsl/ext/mutex/impl/TransMutexAvailNotifier.h"

///////////////////////////////////////////////////////////////////
AbstractTransMutexScheduler::AbstractTransMutexScheduler()
  : lockBitmap(0)
{
}

///////////////////////////////////////////////////////////////////
#define BITMASK(n) (1 << n)

#define IS_LOCKED(mutex) lockBitmap & BITMASK(mutex)

///////////////////////////////////////////////////////////////////
Status AbstractTransMutexScheduler::lock(TransMutexId mutex)
{
   if(mutex >= sizeof(lockBitmap) * 8)
   {
      return USI_OUT_OF_SCOPE;
   }

   if(IS_LOCKED(mutex)) return USI_CONTINUE;

   lockBitmap |= BITMASK(mutex);

   return USI_SUCCESS;
}

///////////////////////////////////////////////////////////////////
void AbstractTransMutexScheduler::unlock(TransMutexId mutex)
{
   if(mutex >= sizeof(lockBitmap) * 8)
   {
      return;
   }

   if(!IS_LOCKED(mutex)) return;

   lockBitmap &= ~BITMASK(mutex);

   ROLE(TransMutexAvailNotifier).notifyMutexAvail(mutex);
}

