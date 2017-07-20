#ifndef INCL_SERVICE_H7EE1512E_E218_4578_B578_65A84B562892
#define INCL_SERVICE_H7EE1512E_E218_4578_B578_65A84B562892

#include "l0-infra/base/Service.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/base/WeedOutStrategy.h"
#include "l0-infra/base/BaseTypes.h"


SERVICE_NS_BEGIN


struct LFUWeedOutStrategy : WeedOutStrategy
{
	LFUWeedOutStrategy() : container(nullptr) {}

	OVERRIDE(U32 findWeedOutNodeKey());

	void setContainer(CacheNodeContainer& container) {this->container = &container;}
private:
	U32 findMinLfuMeasureNodeKey();
private:
	CacheNodeContainer* container;
};


SERVICE_NS_END

#endif
