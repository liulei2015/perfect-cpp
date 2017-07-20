/*
 * StopCause.cc
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/utils/StopCause.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

StopCause::StopCause() : cause(USI_FORCE_STOPPED)
{
}

StopCause::StopCause(const Status cause)
      : cause(ActionStatus(cause).isFailed() ? cause : USI_FORCE_STOPPED)
{
}

StopCause::operator Status() const
{
   return cause;
}

