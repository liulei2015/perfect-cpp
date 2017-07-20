/*
 * FragmentHelper.h
 *
 * Created on: May 28, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef FRAGMENTHELPER_H_
#define FRAGMENTHELPER_H_

#if defined(__GNUC__)
#include "l0-infra/trans-dsl/sched/helper/gnu/FragmentGnu.h"
#elif defined(_MSC_VER)
#include "l0-infra/trans-dsl/sched/helper/msvc/FragmentMsvc.h"
#else
#error "unsupported compiler"
#endif

#include "l0-infra/trans-dsl/sched/helper/ProcedureHelper.h"

//////////////////////////////////////////////////////////////
#define __as_procedure(...) __as(__procedure(__VA_ARGS__))
#define __as_prot_procedure(...) __as(__prot_procedure(__VA_ARGS__))

//////////////////////////////////////////////////////////////
#define __action(action)   typename action
#define __action_id(id)    ActionId id
#define __timer_id(id)     TimerId  id
#define __status_id(id)    Status id
#define __thread_id(id)    ActionThreadId id
#define __object(obj)      typename obj
#define __actor(actor)     typename actor



#endif /* FRAGMENTHELPER_H_ */

