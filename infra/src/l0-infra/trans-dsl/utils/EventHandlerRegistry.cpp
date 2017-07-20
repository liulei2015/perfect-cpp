/*
 * EventHandlerRegistry.cc
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#include "l0-infra/trans-dsl/utils/EventHandlerRegistry.h"
#include "l0-infra/event/concept/Event.h"
#include <new>

////////////////////////////////////////////////////////////////////
EventHandlerRegistry::EventHandler::EventHandler
        ( const EventId eventId
        , DummyEventHandlerClass* thisPointer
        , DummyEventHandler handler
        , bool isSpy)
            : thisPointer(thisPointer)
            , handler(handler)
            , eventId(eventId)
            , isSpy(isSpy)
{
}

////////////////////////////////////////////////////////////////////
EventHandlerRegistry::EventHandler::EventHandler
        ( const EventId eventId)
            : thisPointer(0)
            , handler(&DummyEventHandlerClass::dummy)
            , eventId(eventId)
            , isSpy(false)
{
}

////////////////////////////////////////////////////////////////////
inline bool EventHandlerRegistry::EventHandler::matches(const Event& event) const
{
   return event.matches(eventId);
}

EventHandlerRegistry::EventHandler::~EventHandler()
{
   thisPointer = 0;
   handler = 0;
   eventId = 0;
   isSpy = false;
}

////////////////////////////////////////////////////////////////////
EventHandlerRegistry::Handler::Handler() : used(false)
{}

////////////////////////////////////////////////////////////////////
inline void* EventHandlerRegistry::Handler::alloc()
{
   this->used = true;
   return handler.alloc();
}

////////////////////////////////////////////////////////////////////
inline bool EventHandlerRegistry::Handler::isFree() const
{
   return ! used;
}

////////////////////////////////////////////////////////////////////
inline void EventHandlerRegistry::Handler::clear()
{
   if(used)
   {
      handler->~EventHandler();
      used = false;
   }
}

////////////////////////////////////////////////////////////////////
inline void EventHandlerRegistry::Handler::reset()
{
   if(used)
   {
      handler->~EventHandler();
      used = false;
   }
}

////////////////////////////////////////////////////////////////////
inline bool EventHandlerRegistry::Handler::matches(const Event& event) const
{
   if(! used) return false;

   return handler->matches(event);
}

////////////////////////////////////////////////////////////////////
Status EventHandlerRegistry::EventHandler::handleEvent(const Event& event,
         EventHandlerExecuter& executer)
{
   // It's an untouched event.
   if(__unlikely(thisPointer == 0))
   {
      return USI_SUCCESS;
   }
   
   if(!isSpy)
   {
       event.consume();
   }

   return executer.exec(event, thisPointer, handler);
}

int EventHandlerRegistry::allocSlot()
{
    if(num < MAX_EVENT_HANDLER) return num++;
    return -1;
}

Status EventHandlerRegistry::addUntouchedEvent(const EventId eventId)
{
   int slot = allocSlot();
   if(slot < 0)
   {
      return USI_OUT_OF_SCOPE;
   }

   new (handlers[slot].alloc()) EventHandler(eventId);

   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////
Status EventHandlerRegistry::doAddHandler(const EventId eventId,
         DummyEventHandlerClass* thisPointer, DummyEventHandler handler, bool isSpy)
{
   int slot = allocSlot();
   if(slot < 0)
   {
      return USI_OUT_OF_SCOPE;
   }

   new (handlers[slot].alloc()) EventHandler(eventId, thisPointer, handler, isSpy);
   return USI_SUCCESS;
}

////////////////////////////////////////////////////////////////////
Status EventHandlerRegistry::handleEvent(const Event& event,
         EventHandlerExecuter& executer)
{
   for (int i = 0; i < num; i++)
   {
      if(handlers[i].matches(event))
      {
         Status status = (handlers[i].handler)->handleEvent(event, executer);
         if(USI_UNKNOWN_EVENT != status)
         {
			 clear();
         }
         return status;
      }
   }

   return USI_UNKNOWN_EVENT;
}

////////////////////////////////////////////////////////////////////
void EventHandlerRegistry::clear()
{
   for (int i = 0; i < num; i++)
   {
      handlers[i].clear();
   }
   num = 0;
}

////////////////////////////////////////////////////////////////////
void EventHandlerRegistry::reset()
{
   for (int i = 0; i < num; i++)
   {
      handlers[i].reset();
   }
   num = 0;
}

EventHandlerRegistry::EventHandlerRegistry():num(0)
{
}
