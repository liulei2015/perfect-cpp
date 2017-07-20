/*
 * JoinHelper.h
 *
 * Created on: Apr 23, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef JOINHELPER_H_
#define JOINHELPER_H_

#include "l0-infra/base/Config.h"

#if __SUPPORT_VARIADIC_TEMPLATES
#include "l0-infra/trans-dsl/ext/multi-thread/helper/11/Join11.h"
#else
#include "l0-infra/trans-dsl/ext/multi-thread/helper/98/Join98.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////

#define __join(...) ::details::JOIN__< __VA_ARGS__ >
/////////////////////////////////////////////////////////////////////////////////////

#endif /* JOINHELPER_H_ */

