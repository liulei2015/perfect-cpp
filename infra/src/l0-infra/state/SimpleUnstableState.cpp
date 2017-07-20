#include "l0-infra/state/SimpleUnstableState.h"

USI_NS_BEGIN

SimpleUnstableState::SimpleUnstableState(const StateId to)
  : to(to)
{
}

StateId SimpleUnstableState::getToState() const
{
    return to;
}

USI_NS_END

