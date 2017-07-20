#ifndef INCL_SERVICE_HF104952B_30A0_4B42_8D37_374DC952D4E4
#define INCL_SERVICE_HF104952B_30A0_4B42_8D37_374DC952D4E4

#include "l0-infra/base/Service.h"
#include <unordered_map>
#include "l0-infra/base/CacheNode.h"

SERVICE_NS_BEGIN

using CacheNodeContainer = std::unordered_map<U32, CacheNode>;

SERVICE_NS_END

#endif
