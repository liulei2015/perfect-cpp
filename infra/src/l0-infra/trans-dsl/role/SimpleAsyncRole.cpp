/*
 * SimpleAsyncRole.cc
 *
 *  Created on: Sep 1, 2012
 *      Author: arthur
 */

#include <l0-infra/trans-dsl/role/SimpleAsyncRole.h>

namespace
{
	typedef Status (DummyEventHandlerClass::*Handler)(const Event&);

	struct Executer: EventHandlerExecuter
	{
		OVERRIDE(Status exec(const Event& event, DummyEventHandlerClass* thisClass,
                        DummyEventHandler dummyHandler))
		{
			Handler handler = reinterpret_cast<Handler>(dummyHandler);
			return (thisClass->*handler)(event);
		}
	}executor;
}

/////////////////////////////////////////////////////////////////////////////
Status SimpleAsyncRole::handleEvent(const Event& event)
{
   return registry.handleEvent(event, executor);
}

/////////////////////////////////////////////////////////////////////////////
Status SimpleAsyncRole::waitUntouchEvent(const EventId eventId)
{
   return registry.addUntouchedEvent(eventId);
}

/////////////////////////////////////////////////////////////////////////////
void SimpleAsyncRole::stop()
{
   registry.reset();
   doStop();
}

