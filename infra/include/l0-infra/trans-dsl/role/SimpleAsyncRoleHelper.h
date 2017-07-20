/*
 * SimpleAsyncRoleHelper.h
 *
 *  Created on: Sep 2, 2012
 *      Author: arthur
 */

#ifndef SIMPLEASYNCROLEHELPER_H_
#define SIMPLEASYNCROLEHELPER_H_


#include <l0-infra/trans-dsl/role/SimpleAsyncRole.h>
#include <l0-infra/trans-dsl/utils/WaitOn.h>
#include <l0-infra/event/concept/Event.h>
#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/log/UsfLog.h"

/////////////////////////////////////////////////////////////
namespace details
{
   template<typename T_ROLE>
   struct GenericSimpleAsyncRole: SimpleAsyncRole
   {
   protected:
      typedef T_ROLE ThisType;
   };
}

struct Event;

#define DEF_SIMPLE_ASYNC_ROLE(role) \
struct role : ::details::GenericSimpleAsyncRole<role>

/////////////////////////////////////////////////////////////
#define __ROLE_REAL_HANLDER(handler) actual_##handler

#define ROLE_EVENT_HANDLER_DECL(handler, eventType) \
   Status handler(const Event& event); \
   Status __ROLE_REAL_HANLDER(handler)(const eventType&)

#define ROLE_EVENT_HANDLER_DEF(role, handler, eventType) \
   Status role::handler(const Event& event) \
   { \
      DBG_LOG(#role "::" #handler "(" #eventType ")"); \
      ActionStatus status = __ROLE_REAL_HANLDER(handler)(*((const eventType*)event.getMsg())); \
      if(status.isFailed()) \
      { \
         DBG_LOG(#role "::" #handler "(" #eventType ") failed: [%08x]", (Status)status); \
      } \
      return status; \
   } \
   Status role::__ROLE_REAL_HANLDER(handler)(const eventType& event)


#endif /* SIMPLEASYNCROLEHELPER_H_ */

