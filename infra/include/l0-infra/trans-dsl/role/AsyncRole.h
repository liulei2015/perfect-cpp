/*
 * AsyncRole.h
 *
 *  Created on: Sep 1, 2012
 *      Author: arthur
 */

#ifndef ASYNCROLE_H_
#define ASYNCROLE_H_

#include <l0-infra/base/Status.h>
#include <l0-infra/dci/Role.h>

struct Event;

DEFINE_ROLE(AsyncRole)
{
   ABSTRACT(Status handleEvent(const Event&));
   ABSTRACT(void stop());
};

#endif /* ASYNCROLE_H_ */

