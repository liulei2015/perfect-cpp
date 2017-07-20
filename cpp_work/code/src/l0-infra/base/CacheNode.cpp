#include "l0-infra/base/CacheNode.h"

SERVICE_NS_BEGIN

U32 CacheNode::getId() const
{
	return id;
}

bool CacheNode::operator == (const CacheNode& rNode)
{
	return rNode.getId() == id;
}

SERVICE_NS_END


