#ifndef INCL_SERVICE_HE0CA7518_A9E9_4CAC_9A4C_B664F083DBA0
#define INCL_SERVICE_HE0CA7518_A9E9_4CAC_9A4C_B664F083DBA0

#include "l0-infra/base/Service.h"
#include "l0-infra/base/CacheNodeContainer.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/dci/Role.h"
#include "l0-infra/base/BaseTypes.h"

SERVICE_NS_BEGIN

DEFINE_ROLE( WeedOutStrategy)
{
	ABSTRACT(U32 findWeedOutNodeKey());
	ABSTRACT(void setContainer(CacheNodeContainer& container));
};


SERVICE_NS_END

#endif
