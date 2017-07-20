/*
 * BlockBufferedEventInfo.h
 *
 *  Created on: Nov 11, 2012
 *      Author: arthur
 */

#ifndef BLOCKBUFFEREDEVENTINFO_H_
#define BLOCKBUFFEREDEVENTINFO_H_

#include "BufferedEventInfo.h"

USI_NS_BEGIN

struct BlockBufferedEventInfo: BufferedEventInfo
{
   BlockBufferedEventInfo( const TransStrategyDecisionMaker& strategy
                         , const FailedRequestListener* listener);

   OVERRIDE(const void* getMsg() const);
   OVERRIDE(const void* getMsgBuffer() const);
   OVERRIDE(size_t getMsgSize() const);

   OVERRIDE(Status saveEvent(const EventInfo& event));

private:
   Status saveMsg(const EventInfo& event);

private:
   size_t size;

private:
   ABSTRACT(const void* getMsgBlock(size_t requiredSize) const);
};

template <WORD16 MSG_SIZE>
struct GenericBlockBufferedEventInfo : BlockBufferedEventInfo
{
   GenericBlockBufferedEventInfo
            ( const TransStrategyDecisionMaker& strategy
            , const FailedRequestListener* listener)
      : BlockBufferedEventInfo(strategy, listener)
   {}

private:
   const void* getMsgBlock(size_t requiredSize) const
   {
      return requiredSize > sizeof(msg) ? 0 : msg;
   }

private:
   BYTE    msg[MSG_SIZE];
};

USI_NS_END

#endif /* BLOCKBUFFEREDEVENTINFO_H_ */

