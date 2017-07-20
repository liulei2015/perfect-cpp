/*
 * SimpleTransactionMode.h
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SIMPLETRANSACTIONMODE_H_
#define SIMPLETRANSACTIONMODE_H_

#include "l0-infra/trans-dsl/sched/concept/TransactionMode.h"

struct SimpleTransactionMode : TransactionMode
{
   SimpleTransactionMode();

   OVERRIDE(Status enterSafeMode());
   OVERRIDE(Status leaveSafeMode());

protected:
   bool inSafeMode() const;

private:
   int safeModeRef;
};

#endif /* SIMPLETRANSACTIONMODE_H_ */

