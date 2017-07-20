/*
 * RoleBasedAsyncAction.h
 *
 *  Created on: Aug 26, 2012
 *      Author: arthur
 */

#ifndef ROLEBASEDASYNCACTION_H_
#define ROLEBASEDASYNCACTION_H_

#include "l0-infra/trans-dsl/utils/ActionStatus.h"
#include "l0-infra/log/UsfLog.h"
#include "l0-infra/dci/Role.h"


struct AsyncRole;
struct TransactionInfo;
struct Event;

struct RoleBasedAsyncAction
{
   RoleBasedAsyncAction();

   Status handleEvent(const TransactionInfo&, const Event&);
   void kill(const TransactionInfo&, const Status cause);

   virtual ~RoleBasedAsyncAction() {}

protected:
   void setAsyncRole(AsyncRole*);

public:
   void reset();

private:
   AsyncRole* role;
};

#define  __RETURN_ROLE_BASED_INVOKE(role, method, asynRole)  \
    ActionStatus status = (role).method; \
    if(status.isWorking()) \
    { \
        setAsyncRole(asynRole); \
    } \
    else if (status.isFailed()) \
    { \
        DBG_LOG("invoke " #role "::" #method "=%d failed!", (Status)status); \
    } \
    return status

#define RETURN_ROLE_BASED_INVOKE(role, method) \
    __RETURN_ROLE_BASED_INVOKE((role), method, &(role))

#define RETURN_ROLE_PTR_BASED_INVOKE(role, method) \
    RETURN_ROLE_BASED_INVOKE(*role, method)
    
#define RETURN_ROLE_BASED_CALL(role, method) \
    __RETURN_ROLE_BASED_INVOKE((role), method, (role).getAsyncRole())

#define RETURN_REF_ROLE_BASED_CALL(role, method) \
    __RETURN_ROLE_BASED_INVOKE((role), method, &((role).getAsyncRole()))

#define DEF_SIMPLE_ROLE_BASED_ACTION(p_role)     \
struct p_role : RoleBasedAsyncAction             \
{                                                \
   Status exec(const TransactionInfo&);\
}

#endif /* ROLEBASEDASYNCACTION_H_ */

