/*
 * ConcurrentAsyncRole.h
 *
 *  Created on: Aug 26, 2012
 *      Author: arthur
 */

#ifndef CONCURRENTASYNCROLE_H_
#define CONCURRENTASYNCROLE_H_

#include "l0-infra/trans-dsl/role/AsyncRole.h"

struct ConcurrentAsyncRole : AsyncRole
{
    ConcurrentAsyncRole();

   Status addAsyncRole(AsyncRole& role);

   OVERRIDE(Status handleEvent(const Event&));
   OVERRIDE(void stop());

protected:
   Status doHandleEvent(const Event& event);
   bool hasWorkingActions() const;

private:
   Status handleEventOn(const Event& event, int n);

private:
   enum { MAX_NUM_OF_CONCURRENT_ROLES = 6 };

   AsyncRole* roles[MAX_NUM_OF_CONCURRENT_ROLES];

private:
   virtual void doStop() {}
};

#endif /* CONCURRENTASYNCACTION_H_ */

