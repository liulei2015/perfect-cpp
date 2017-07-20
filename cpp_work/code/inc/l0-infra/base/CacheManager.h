#ifndef INCL_SERVICE_H8DB88CE3_71D7_4B78_8A04_6DAEA857E2E2
#define INCL_SERVICE_H8DB88CE3_71D7_4B78_8A04_6DAEA857E2E2

#include "l0-infra/base/Service.h"
#include "l0-infra/base/BaseTypes.h"
#include "CacheNode.h"
#include "l0-infra/base/CacheNodeContainer.h"
#include "l0-infra/base/WeedOutStrategy.h"

#include <unordered_map>
#include <memory>

SERVICE_NS_BEGIN

struct CacheManager
{
	CacheManager() : stratrgy(nullptr) {}
	~CacheManager()
	{
		if(stratrgy != nullptr)
			delete stratrgy;
	}

	CacheNode get(U32 key);

	void put(U32 key, const CacheNode& node);

	void remove(U32 key);

	U32 getContainerSize()	;

	void clear();

	void setStrategy(WeedOutStrategy* toSetStrategy)
	{this->stratrgy = toSetStrategy;}

	void notifyStrategyContainer() {stratrgy->setContainer(container);}
private:
	CacheNodeContainer container;
	WeedOutStrategy* stratrgy;
};


SERVICE_NS_END

#endif
