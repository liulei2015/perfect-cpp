#ifndef INCL_USI_ConcreteMap_20131117000434_H__
#define INCL_USI_ConcreteMap_20131117000434_H__

#include "l0-infra/base/AbstractMap.h"
#include "l0-infra/base/Map.h"

USI_NS_BEGIN

template <typename K, typename V, WORD32 MAX_NUM>
struct ConcreteMap : AbstractMap<K, V>
{
    Map<K, V, MAX_NUM> map;

    Status put(const K& key, const V& value)
    {
        return map.put(key, value);
    }

    const V* get(const K& key) const
    {
        return map.get(key);
    }

    void remove(const K& key)
    {
        map.remove(key);
    }

    bool contains(const K& key)
    {
        return map.contains(key);
    }

public:
    void removeBy(const V& value)
    {
        map.removeBy(value);
    }

    void removeOtherKeyExcept(const K& key, const V& value)
    {
        map.removeOtherKeyExcept(key, value);
    }

    void visit(ConstMapVisitor& visitor) const
    {
        map.visit(visitor);
    }

    void clear()
    {
        map.clear();
    }
};

USI_NS_END

#endif

