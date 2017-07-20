#include "l0-infra/base/MRUWeedOutStrategy.h"
#include "l0-infra/base/CacheNodeContainer.h"
#include "l0-infra/base/Status.h"


SERVICE_NS_BEGIN


////////////////////////////////////////////////////////////////////////////////////////////////////////
U32 MRUWeedOutStrategy::findWeedOutNodeKey()
{
	return findMinMruMeasureNodeKey();
}

U32 MRUWeedOutStrategy::findMinMruMeasureNodeKey()
{
	if(container == nullptr)
		return USI_INVALID_WORD32;

	CacheNodeContainer& useContainer = *container;
	CacheNodeContainer::const_iterator iter = useContainer.begin();

	U32 minMruMeasureNodeKey = iter->first;
	CacheNode firstNode = iter->second;
	U32 minMruMeasure = firstNode.getMeasure();

	for (auto& item : useContainer) {
		CacheNode node = item.second;
		if (minMruMeasure > node.getMeasure()) {
			minMruMeasure = node.getMeasure();
			minMruMeasureNodeKey = item.first;
		}
	}

	return minMruMeasureNodeKey;
}

SERVICE_NS_END


