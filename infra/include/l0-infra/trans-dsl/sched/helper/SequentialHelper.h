/*
 * SequentialHelper.h
 *
 * Created on: Apr 22, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef SEQUENTIALHELPER_H_
#define SEQUENTIALHELPER_H_

#include "l0-infra/base/Config.h"

#if __SUPPORT_VARIADIC_TEMPLATES
#include "l0-infra/trans-dsl/sched/helper/11/Sequential11.h"
#else
#include "l0-infra/trans-dsl/sched/helper/98/Sequential98.h"
#endif

/////////////////////////////////////////////////////////////////////////////////
#define __sequential(...) \
    ::details::SEQUENTIAL__< __VA_ARGS__ >

#define __void_sequential(...) \
    ::details::VOID_SEQUENTIAL__< __VA_ARGS__ >

/////////////////////////////////////////////////////////////////////////////////

#endif /* SEQUENTIALHELPER_H_ */
