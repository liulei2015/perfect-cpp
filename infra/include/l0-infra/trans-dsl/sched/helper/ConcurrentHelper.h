/*
 * ConcurrentHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef CONCURRENTHELPER_H_
#define CONCURRENTHELPER_H_

#include "l0-infra/base/Config.h"

#if   __SUPPORT_VARIADIC_TEMPLATES
#include "l0-infra/trans-dsl/sched/helper/11/Concurrent11.h"
#else
#include "l0-infra/trans-dsl/sched/helper/98/Concurrent98.h"
#endif

/////////////////////////////////////////////////////////////////////////////////
#define __concurrent(...) \
    ::details::CONCURRENT__< __VA_ARGS__ >

#define __void_concurrent(...) \
    ::details::VOID_CONCURRENT__< __VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////////

#endif /* CONCURRENTHELPER_H_ */

