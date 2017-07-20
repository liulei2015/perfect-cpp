#ifndef INCL_SERVICE_H00070584_4D2B_41A2_BBA3_264CAB464470
#define INCL_SERVICE_H00070584_4D2B_41A2_BBA3_264CAB464470

#include "l0-infra/base/Service.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/base/WeedOutStrategy.h"
#include "l0-infra/base/BaseTypes.h"

SERVICE_NS_BEGIN

struct MRUWeedOutStrategy : WeedOutStrategy
{
	MRUWeedOutStrategy() : container(nullptr) {}

	OVERRIDE(U32 findWeedOutNodeKey());

	void setContainer(CacheNodeContainer& container) {this->container = &container;}
private:
	U32 findMinMruMeasureNodeKey();
private:
	CacheNodeContainer* container;
};

SERVICE_NS_END

#endif
