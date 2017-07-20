#ifndef INCL_USI_AbstractMap_20131117000310_H__
#define INCL_USI_AbstractMap_20131117000310_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/Status.h"

template <typename K, typename V>
struct AbstractMap
{
    ABSTRACT(Status put(const K& key, const V& value) throw());
    ABSTRACT(const V* get(const K& key) const);
    ABSTRACT(void remove(const K& key));
    ABSTRACT(bool contains(const K& key));

    virtual ~AbstractMap() {}

public:
    DEFINE_ROLE(ConstMapVisitor)
    {
        ABSTRACT(void visit(const K&, const V&));
    }; 
       
public:
    ABSTRACT(void removeBy(const V& value));
    ABSTRACT(void removeOtherKeyExcept(const K& key, const V& value));
    ABSTRACT(void visit(ConstMapVisitor& visitor) const);
    ABSTRACT(void clear());
    ABSTRACT(bool empty() const);
};

//////////////////////////////////////////////////////////////////////////

#define __DECL_MAP(p_name, p_key, p_value)                      \
struct p_name                                                   \
{                                                               \
    typedef AbstractMap<p_key, p_value> ThisMap;                \
    typedef ThisMap::ConstMapVisitor ConstMapVisitor;           \
                                                                \
    static ThisMap& getInstance();                              \
}

//////////////////////////////////////////////////////////////////////////

#define __DECL_UE_ID_MAP(p_name, p_key)  __DECL_MAP(p_name, p_key, WORD16)

#endif

