/*
 * EventHandlerRegistry.h
 *
 * Created on: Apr 29, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef EVENTHANDLERREGISTRY_H_
#define EVENTHANDLERREGISTRY_H_

#include <l0-infra/dci/Role.h>
#include <l0-infra/base/Status.h>
#include <l0-infra/base/Placement.h>
#include <l0-infra/event/concept/EventId.h>

struct DummyEventHandlerClass
{
   void dummy()
   {
   }
};

typedef void (DummyEventHandlerClass::*DummyEventHandler)();

///////////////////////////////////////////////////////////////
struct Event;

DEFINE_ROLE(EventHandlerExecuter)
{
   ABSTRACT(Status exec(const Event&, DummyEventHandlerClass*, DummyEventHandler));
};

///////////////////////////////////////////////////////////////
struct EventHandlerRegistry
{
    EventHandlerRegistry();
   template<typename T, typename HANDLER>
   Status addHandler(const EventId eventId, T* thisPointer, HANDLER handler, bool isSpy = false)
   {
      return doAddHandler
               ( eventId
               , (DummyEventHandlerClass*) thisPointer
               , reinterpret_cast<DummyEventHandler>(handler)
               , isSpy);
   }

   Status addUntouchedEvent(const EventId eventId);

   Status handleEvent(const Event&, EventHandlerExecuter&);

   void reset();

private:
   Status doAddHandler(const EventId, DummyEventHandlerClass*,
            DummyEventHandler, bool isSpy);

   void clear();
private:

   struct EventHandler
   {
      EventHandler(const EventId, DummyEventHandlerClass*, DummyEventHandler, bool isSpy);
      EventHandler(const EventId);
      ~EventHandler();

      bool matches(const Event&) const;
      Status handleEvent(const Event&, EventHandlerExecuter&);

   private:
      DummyEventHandlerClass* thisPointer;
      DummyEventHandler handler;
      EventId eventId;
      bool isSpy;
   };

   int allocSlot();
private:
   enum
   {
      MAX_EVENT_HANDLER = 4
   };

   struct Handler
   {
      Handler();

      void* alloc();
      bool matches(const Event& event) const;
      bool isFree() const;
      void clear();
      void reset();

      Placement<EventHandler> handler;

   private:
      bool used;
   };

   int num;
   Handler handlers[MAX_EVENT_HANDLER];
};

#endif /* EVENTHANDLERREGISTRY_H_ */

