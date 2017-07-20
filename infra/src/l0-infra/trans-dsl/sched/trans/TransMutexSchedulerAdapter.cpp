/*
 * TransMutexSchedulerAdapter.cpp
 *
 * Created on: Aug 7, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/trans/TransMutexSchedulerAdapter.h"
#include "l0-infra/base/Assertions.h"

//////////////////////////////////////////////////////////////////////////////////
TransMutexSchedulerAdapter::TransMutexSchedulerAdapter()
   : scheduler(0)
{
}

//////////////////////////////////////////////////////////////////////////////////
Status TransMutexSchedulerAdapter::lock(TransMutexId mutex)
{
   USI_ASSERT_VALID_PTR(scheduler);

   return scheduler->lock(mutex);
}

//////////////////////////////////////////////////////////////////////////////////
void TransMutexSchedulerAdapter::unlock(TransMutexId mutex)
{
   if(scheduler != 0)
   {
      scheduler->unlock(mutex);
   }
}

//////////////////////////////////////////////////////////////////////////////////
void TransMutexSchedulerAdapter::updateMutexScheduler(TransMutexScheduler& scheduler)
{
   this->scheduler = &scheduler;
}

