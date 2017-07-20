#include "l0-infra/base/LRUWeedOutStrategy.h"
#include "l0-infra/base/CacheNodeContainer.h"
#include "l0-infra/base/Status.h"

SERVICE_NS_BEGIN

U32 LRUWeedOutStrategy::findWeedOutNodeKey()
{
	return findMaxLruMeasureNodeKey();
}

U32 LRUWeedOutStrategy::findMaxLruMeasureNodeKey()
{
	if(container == nullptr)
		return USI_INVALID_WORD32;

	CacheNodeContainer& useContainer = *container;

	CacheNodeContainer::const_iterator iter = useContainer.begin();

	U32 maxLruMeasureNodeKey = iter->first;
	CacheNode firstNode = iter->second;
	U32 maxLruMeasure = firstNode.getMeasure();

	for (auto& item : useContainer) {
		CacheNode node = item.second;
		if (maxLruMeasure < node.getMeasure()) {
			maxLruMeasure = node.getMeasure();
			maxLruMeasureNodeKey = item.first;
		}
	}

	return maxLruMeasureNodeKey;
}



SERVICE_NS_END


