/*
 * SimpleAsyncRole.h
 *
 *  Created on: Sep 1, 2012
 *      Author: arthur
 */

#ifndef SIMPLEASYNCROLE_H_
#define SIMPLEASYNCROLE_H_

#include "l0-infra/trans-dsl/role/AsyncRole.h"
#include "l0-infra/trans-dsl/utils/EventHandlerRegistry.h"

struct SimpleAsyncRole: AsyncRole
{
   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(void stop());

   template<typename T>
   Status waitOn(const EventId eventId, T* thisPointer,
            Status (T::*handler)(const Event&), bool = false)
   {
      return registry.addHandler(eventId, thisPointer, handler, false);
   }

   Status waitUntouchEvent(const EventId eventId);

private:
   EventHandlerRegistry registry;

private:
   virtual void doStop() {}
};

#endif /* SIMPLEASYNCROLE_H_ */

