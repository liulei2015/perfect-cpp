#ifndef INCL_USI_TriggerMatcherHelper_H_
#define INCL_USI_TriggerMatcherHelper_H_

#include "l0-infra/mem-dbs/TriggerMatcher.h"

USI_NS_BEGIN

namespace details
{
    #define DUMMY_TRIGGER_ID  (WORD16)0xFFFF

    template<WORD16 Trigger1 = DUMMY_TRIGGER_ID, 
             WORD16 Trigger2 = DUMMY_TRIGGER_ID, 
             WORD16 Trigger3 = DUMMY_TRIGGER_ID, 
             WORD16 Trigger4 = DUMMY_TRIGGER_ID, 
             WORD16 Trigger5 = DUMMY_TRIGGER_ID,
             WORD16 Trigger6 = DUMMY_TRIGGER_ID,
             WORD16 Trigger7 = DUMMY_TRIGGER_ID,
             WORD16 Trigger8 = DUMMY_TRIGGER_ID>

    struct TriggerMatcherHelper : TriggerMatcher
    {
        OVERRIDE(bool isMatched(WORD16 triggerId) const)
        {
            return (triggerId == Trigger1) ||
                   (triggerId == Trigger2) ||
                   (triggerId == Trigger3) ||
                   (triggerId == Trigger4) ||
                   (triggerId == Trigger5) ||
                   (triggerId == Trigger6) ||
                   (triggerId == Trigger7) ||
                   (triggerId == Trigger8);
        }
    };
}

///////////////////////////////////////////////////////////
#define __trigger(...)  details::TriggerMatcherHelper< __VA_ARGS__ >

USI_NS_END

#endif 

