/*
 * BlockBufferedEventInfo.cc
 *
 *  Created on: Nov 11, 2012
 *      Author: arthur
 */


#include <l0-infra/state/BlockBufferedEventInfo.h>
#include <l0-infra/base/Assertions.h>
#include <string.h>
#include "l0-infra/event/concept/EventInfo.h"
#include "l0-infra/event/concept/InvalidMsgSize.h"

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////
BlockBufferedEventInfo::BlockBufferedEventInfo
     ( const TransStrategyDecisionMaker& strategy
     , const FailedRequestListener* listener)
   : BufferedEventInfo(&strategy, listener)
   , size(INVALID_MSG_SIZE)
{
}

//////////////////////////////////////////////////////////////////
const void* BlockBufferedEventInfo::getMsg() const
{
   return getMsgBuffer();
}

//////////////////////////////////////////////////////////////////
Status BlockBufferedEventInfo::saveEvent(const EventInfo& event)
{
   USI_ASSERT_SUCC_CALL(saveMsg(event));
   updateEventId(event.getEventId());
   return USI_SUCCESS;
}

//////////////////////////////////////////////////////////////////
const void* BlockBufferedEventInfo::getMsgBuffer() const
{
   return getMsgBlock(size);
}

//////////////////////////////////////////////////////////////////
size_t BlockBufferedEventInfo::getMsgSize() const
{
   return size;
}

//////////////////////////////////////////////////////////////////
Status BlockBufferedEventInfo::saveMsg(const EventInfo& event)
{
   const void* const src = event.getMsg();
   if (src == 0)
   {
      if(event.getMsgSize() != 0) return USI_FAILED;

      size = 0;
      return USI_SUCCESS;
   }

   const void* dest = getMsgBlock(event.getMsgSize());
   USI_ASSERT_VALID_PTR(dest);

   size = event.getMsgSize();
   ::memcpy((void*) dest, src, size);

   return USI_SUCCESS;
}

USI_NS_END

