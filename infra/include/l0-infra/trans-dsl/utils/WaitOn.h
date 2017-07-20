/*
 * WaitOn.h
 *
 * Created on: May 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef WAITON_H_
#define WAITON_H_

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
#define __WAIT_EVENT(...) do { \
   Status ___wait_on_status__ = __VA_ARGS__; \
   if( ___wait_on_status__ != USI_SUCCESS) return ___wait_on_status__; \
} while(0)

#define __WAIT_ON(eventId, handler,spy) \
   __WAIT_EVENT(waitOn(eventId, this, &ThisType::handler, spy))
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
#define WAIT_ON(eventId, handler) \
   __WAIT_ON(eventId, handler,  false)

#define SPY_ON(eventId, handler) \
    __WAIT_ON(eventId, handler, true)

/////////////////////////////////////////////////////////////

#endif /* WAITON_H_ */

