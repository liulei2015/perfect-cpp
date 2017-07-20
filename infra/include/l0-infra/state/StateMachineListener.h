#ifndef _INCL_USI_StateListener_H__
#define _INCL_USI_StateListener_H__

#include "l0-infra/dci/ListBasedRole.h"

USI_NS_BEGIN

struct State;

DEFINE_LIST_BASED_ROLE(StateMachineListener)
{
    ABSTRACT(void onStableStateEntering(const State&));    
    ABSTRACT(void onUnstableStateLeaving(const State&));
};

USI_NS_END

#endif 

