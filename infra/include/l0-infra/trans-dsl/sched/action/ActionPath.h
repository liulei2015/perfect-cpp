/*
 * ActionPath.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef ACTIONPATH_H_
#define ACTIONPATH_H_

#include <l0-infra/dci/ListBasedRole.h>
#include <l0-infra/base/Status.h>

struct TransactionInfo;
struct SchedAction;

DEFINE_LIST_BASED_ROLE(ActionPath)
{
   ActionPath(SchedAction& action) : action(action) {}

   ABSTRACT(bool shouldExecute(const TransactionInfo&));

   SchedAction& action;
};

#endif /* ACTIONPATH_H_ */

