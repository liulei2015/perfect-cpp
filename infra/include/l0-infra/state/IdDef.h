#ifndef _INCL_USI_StateDef_H__
#define _INCL_USI_StateDef_H__

#include "l0-infra/base/usi.h"
#include "l0-infra/base/Keywords.h"
#include "StateId.h"

USI_NS_BEGIN

#define STATE_ID(p_name) STATE_##p_name

#define DEF_STATE_ID(p_name) \
    OVERRIDE(StateId getId() const) {return STATE_ID(p_name);}

USI_NS_END

#endif

