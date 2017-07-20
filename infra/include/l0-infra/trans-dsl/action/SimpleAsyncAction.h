/*
 * SimpleAsyncAction.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLEASYNCACTION_H_
#define SIMPLEASYNCACTION_H_

#include "l0-infra/trans-dsl/utils/EventHandlerRegistry.h"

struct TransactionInfo;

struct SimpleAsyncAction
{
   Status handleEvent(const TransactionInfo&, const Event&);
   void kill(const TransactionInfo&, const Status);

   template<typename T>
   Status waitOn(const EventId eventId, T* thisPointer,
            Status (T::*handler)(const TransactionInfo&, const Event&),
            bool isSpy = false)
   {
      return registry.addHandler(eventId, thisPointer, handler, isSpy);
   }

   Status waitUntouchEvent(const EventId eventId);

   void reset();

   virtual ~SimpleAsyncAction() {}

private:
   EventHandlerRegistry registry;

public:

private:
   virtual void doKill(const TransactionInfo&, const Status) {}
};

#endif /* SIMPLEASYNCACTION_H_ */

