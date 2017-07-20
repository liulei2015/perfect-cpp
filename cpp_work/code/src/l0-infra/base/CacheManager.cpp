#include "l0-infra/base/CacheManager.h"
#include "l0-infra/log/log.h"
#include "l0-infra/base/Spec.h"


SERVICE_NS_BEGIN

CacheNode CacheManager::get(U32 key)
{
	CacheNodeContainer::const_iterator got = container.find(key);
	if(got == container.end())
	{
		INFO_LOG("not find value by key[%u]", key);
		return CacheNode(0, 0, 0);
	}
	else
		return got->second;
}

void CacheManager::put(U32 key, const CacheNode& node)
{
	if(container.size() < MAX_CACHE_NODE_NUM)
	{
		container.insert(std::pair<U32, CacheNode>(key, node));
	}
	else
	{
		if(stratrgy == nullptr) return;

		remove(stratrgy->findWeedOutNodeKey());
		container.insert(std::pair<U32, CacheNode>(key, node));
	}
}

void CacheManager::remove(U32 key)
{
	container.erase(key);
}

U32 CacheManager::getContainerSize()
{
	return container.size();
}

void CacheManager::clear()
{
	container.clear();
}


SERVICE_NS_END



