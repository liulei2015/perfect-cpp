#ifndef INCL_SERVICE_HE020A418_DB6C_401B_94FF_CBD960E1D0C2
#define INCL_SERVICE_HE020A418_DB6C_401B_94FF_CBD960E1D0C2

#include "l0-infra/base/Service.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/base/WeedOutStrategy.h"
#include "l0-infra/base/BaseTypes.h"

SERVICE_NS_BEGIN


struct LRUWeedOutStrategy : WeedOutStrategy
{
	LRUWeedOutStrategy() : container(nullptr) {}

	OVERRIDE(U32 findWeedOutNodeKey());

	void setContainer(CacheNodeContainer& container) {this->container = &container;}
private:
	U32 findMaxLruMeasureNodeKey();
private:
	CacheNodeContainer* container;
};

SERVICE_NS_END

#endif
