/*
 * RoleBasedAsyncAction.cc
 *
 *  Created on: Sep 1, 2012
 *      Author: arthur
 */

#include "l0-infra/trans-dsl/action/RoleBasedAsyncAction.h"
#include "l0-infra/trans-dsl/role/AsyncRole.h"

//////////////////////////////////////////////////////////////////////
RoleBasedAsyncAction::RoleBasedAsyncAction()
   : role(0)
{
}

//////////////////////////////////////////////////////////////////////
Status RoleBasedAsyncAction::handleEvent(const TransactionInfo&, const Event& event)
{
   if (role != 0)
      return role->handleEvent(event);

   return USI_FATAL_BUG;
}

//////////////////////////////////////////////////////////////////////
void RoleBasedAsyncAction::kill(const TransactionInfo&, const Status)
{
    if (role != 0)
    {
        role->stop();
        role = 0;
    }
}

//////////////////////////////////////////////////////////////////////
void RoleBasedAsyncAction::setAsyncRole(AsyncRole* role)
{
   this->role = role;
}

//////////////////////////////////////////////////////////////////////
void RoleBasedAsyncAction::reset()
{
    role = 0;
}
