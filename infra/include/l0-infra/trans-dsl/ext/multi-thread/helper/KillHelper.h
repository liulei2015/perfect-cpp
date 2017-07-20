/*
 * KillHelper.h
 *
 *  Created on: Nov 29, 2012
 *      Author: arthur
 */

#ifndef KILLHELPER_H_
#define KILLHELPER_H_

#include "l0-infra/trans-dsl/ext/multi-thread/action/SchedKillAction.h"

namespace details
{
   template <ActionThreadId THREAD_ID, Status CAUSE = USI_SUCCESS>
   struct KILL__ : SchedKillAction
   {
      OVERRIDE(ActionThreadId getThreadId() const)
      {
         return THREAD_ID;
      }

      OVERRIDE(Status getCause() const)
      {
          return CAUSE;
      }
   };
}

#define __kill(...) ::details::KILL__< __VA_ARGS__ >

#endif /* KILLHELPER_H_ */

