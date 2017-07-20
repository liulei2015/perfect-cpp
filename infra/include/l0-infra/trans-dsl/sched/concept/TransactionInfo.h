/*
 * TransactionInfo.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONINFO_H_
#define TRANSACTIONINFO_H_

#include <l0-infra/trans-dsl/sched/concept/InstanceId.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/dci/Role.h>
#include "l0-infra/base/Keywords.h"
#include "l0-infra/dci/Unknown.h"

DEFINE_ROLE(TransactionInfo)
{
   TransactionInfo() : userContext(0) {}

   InstanceId getInstanceId() const { return iid; }   
   dci::Unknown* getUserContext() const
   {
       return userContext;
   }

   template <typename ROLE>
   ROLE* toRole() const
   {
       return dci::unknown_cast<ROLE>(getUserContext());
   }

   ABSTRACT(Status getStatus() const);

protected:
    InstanceId iid;
    dci::Unknown*   userContext;
};

#define CONTEXT_ROLE(role) \
DECL_ROLE(role)            \
{                                                                                         \
    __IMPL_CONTEXT_ROLE(dci::unknown_cast<role>(ROLE(UeConnectionInfo).getUserContext())) \
}

#define CONTEXT_ROLE_PTR(role)                                                                \
role* ROLE(role) const                                                                        \
{                                                                                             \
    __IMPL_CONTEXT_ROLE_PTR(dci::unknown_cast<role>(ROLE(UeConnectionInfo).getUserContext())) \
}

#define IMPL_CONN_CONTEXT_ROLE(object, role)                                            \
    DECL_OBJECT_ROLE(object, role)                                                      \
{                                                                                       \
    __IMPL_CONTEXT_ROLE(dci::unknown_cast<role>(ROLE(UeConnectionInfo).getUserContext()))\
}

//////////////////////////////////////////////////////////////////////////
#define __TRANS_TO_ROLE(p_type, p_role)      \
    p_type* p_role = trans.toRole<p_type>()  \

//////////////////////////////////////////////////////////////////////////
#define TRANS_TO_ROLE(p_type, p_role)        \
    __TRANS_TO_ROLE(p_type, p_role);         \
    USI_ASSERT_VALID_PTR(p_role)

//////////////////////////////////////////////////////////////////////////
#define TRANS_TO_ROLE_VOID(p_type, p_role)   \
    __TRANS_TO_ROLE(p_type, p_role);         \
    USI_ASSERT_VALID_PTR_VOID(p_role)

#define TRANS_TO_ROLE_NIL(p_type, p_role)    \
    __TRANS_TO_ROLE(p_type, p_role);         \
    USI_ASSERT_VALID_PTR_NIL(p_role)

#define TRANS_TO_ROLE_BOOL(p_type, p_role)    \
    __TRANS_TO_ROLE(p_type, p_role);         \
    USI_ASSERT_VALID_PTR_BOOL(p_role)

#endif /* TRANSACTIONINFO_H_ */

