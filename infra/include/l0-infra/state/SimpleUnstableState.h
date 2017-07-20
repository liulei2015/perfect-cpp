#ifndef INCL_USI_SimpleUnstableState_H__
#define INCL_USI_SimpleUnstableState_H__

#include "l0-infra/base/usi.h"
#include "l0-infra/state/UnstableTransState.h"

USI_NS_BEGIN

struct SimpleUnstableState : UnstableTransState
{
    SimpleUnstableState(const StateId to);

private:
    OVERRIDE(StateId getToState() const);

private:
    const StateId to;
};

USI_NS_END


#endif

