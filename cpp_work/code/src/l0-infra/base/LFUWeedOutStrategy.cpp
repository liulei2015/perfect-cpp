#include "l0-infra/base/LFUWeedOutStrategy.h"
#include "l0-infra/base/CacheNodeContainer.h"
#include "l0-infra/base/Status.h"

SERVICE_NS_BEGIN


////////////////////////////////////////////////////////////////////////////////////////////////////////
U32 LFUWeedOutStrategy::findWeedOutNodeKey()
{
	return findMinLfuMeasureNodeKey();
}

U32 LFUWeedOutStrategy::findMinLfuMeasureNodeKey()
{
	if(container == nullptr)
		return USI_INVALID_WORD32;

	CacheNodeContainer& useContainer = *container;
	CacheNodeContainer::const_iterator iter = useContainer.begin();

	U32 minLfuMeasureNodeKey = iter->first;
	CacheNode firstNode = iter->second;
	U32 minLfuMeasure = firstNode.getVisitTimes();

	for (auto& item : useContainer) {
		CacheNode node = item.second;
		if (minLfuMeasure > node.getVisitTimes()) {
			minLfuMeasure = node.getVisitTimes();
			minLfuMeasureNodeKey = item.first;
		}
	}

	return minLfuMeasureNodeKey;
}


SERVICE_NS_END


