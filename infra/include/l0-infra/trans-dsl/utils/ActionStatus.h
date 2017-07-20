/*
 * ActionStatus.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONSTATUS_H_
#define ACTIONSTATUS_H_

#include <l0-infra/base/Status.h>

// 
// According to performance profiling tool, 
// inline everything of this class.
//
struct ActionStatus
{
   ActionStatus(Status status)
       : status(status)
   {
   }

   bool transFailed() const
   {
       return isFailed() && status != USI_NOTHING_CHANGED;
   }

   bool isWorking() const
   {
	   switch(status)
	   {
	   case USI_CONTINUE:
	   case USI_UNKNOWN_EVENT:
		   return true;
	   default:
		   return false;
	   }
   }

   bool isFailed() const
   {
       return IS_FAILED_STATUS(status);
   }

   bool eventAccepted() const
   {
       return status != USI_UNKNOWN_EVENT;
   }

   bool eventNotAccepted() const
   {
       return !eventAccepted();
   }

   bool isNothingChanged() const
   {
       return status == USI_NOTHING_CHANGED;
   }

   operator Status() const
   {
       return status;
   }

   bool isDone() const
   {
       return status == USI_SUCCESS;
   }

private:
   Status status;
};

#endif /* ACTIONSTATUS_H_ */

