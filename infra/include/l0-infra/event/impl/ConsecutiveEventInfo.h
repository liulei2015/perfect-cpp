#ifndef CONSECUTIVEEVENTINFO_H_
#define CONSECUTIVEEVENTINFO_H_

#include "l0-infra/event/impl/BaseEventInfo.h"

struct ConsecutiveEventInfo : BaseEventInfo
{
   template <typename T>
   ConsecutiveEventInfo(const EventId eventId, const T& msg)
      : BaseEventInfo(eventId), msg((void*)&msg), size(sizeof(msg))
   {}

   ConsecutiveEventInfo(const EventId eventId, const void* const msg, size_t size);

   OVERRIDE(const void* getMsg() const);
   OVERRIDE(size_t getMsgSize() const);

private:
   const void* const  msg;
   const size_t       size;
};

#endif /* CONSECUTIVEEVENTINFO_H_ */

