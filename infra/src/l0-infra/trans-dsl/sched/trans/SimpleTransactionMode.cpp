/*
 * SimpleTransactionMode.cc
 *
 * Created on: Jun 11, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionMode.h"
#include "l0-infra/base/Assertions.h"

/////////////////////////////////////////////////////////////////////
SimpleTransactionMode::SimpleTransactionMode()
   : safeModeRef(0)
{}

/////////////////////////////////////////////////////////////////////
Status SimpleTransactionMode::enterSafeMode()
{
   safeModeRef++;

   return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
Status SimpleTransactionMode::leaveSafeMode()
{
    USI_ASSERT_TRUE(safeModeRef > 0);
    safeModeRef--;

    return USI_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
bool SimpleTransactionMode::inSafeMode() const
{
   return safeModeRef > 0;
}

