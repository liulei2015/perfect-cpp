/*
 * TransactionMode.h
 *
 * Created on: Jun 10, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef TRANSACTIONMODE_H_
#define TRANSACTIONMODE_H_

#include <l0-infra/dci/Role.h>
#include "l0-infra/base/Status.h"

DEFINE_ROLE(TransactionMode)
{
   ABSTRACT(Status enterSafeMode());
   ABSTRACT(Status leaveSafeMode());
};

#endif /* TRANSACTIONMODE_H_ */

