#ifndef INCL_USI_Map_H__
#define INCL_USI_Map_H__

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/StlAllocator.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/AbstractMap.h"

#include <map>
#include "l0-infra/multi-thread/Synchronization.h"
#include "l0-infra/multi-thread/DummyRwLock.h"
#include "l0-infra/multi-thread/PthreadRwLock.h"
#include "l0-infra/wrapper/ng_pub_platform.h"
#include "l0-infra/multi-thread/MultiThreadWrapper.h"

template <typename K, typename V, WORD32 MAX_ELEM_NUM
    , WORD32 THREAD_NUM = MAX_SERVICE_INST_THREAD_NUM
    , typename LOCK = DummyRwLock
    , typename ALLOCTOR = StlAllocator<std::pair<K, V>, MAX_ELEM_NUM, THREAD_NUM> >
struct Map : AbstractMap<K, V>
{
    Status put(const K& key, const V& value) throw()
    {
        WRITE_SYNCHRONIZED
        {
            if ((stlMap.size()+1) == MAX_ELEM_NUM) return USI_OUT_OF_SCOPE;

            stlMap[key] = value;
        }

        return USI_SUCCESS;
    }

    const V* get(const K& key) const
    {
        const V* v = 0;

        READ_SYNCHRONIZED
        {
            typename StlMap::const_iterator i = stlMap.find(key);
            v = i != stlMap.end() ? &i->second : 0;
        }

        return v;
    }

    void remove(const K& key)
    {
        WRITE_SYNCHRONIZED
        {
            stlMap.erase(key);
        }
    }

    bool contains(const K& key)
    {
        bool result;

        READ_SYNCHRONIZED
        {
            result = stlMap.find(key) != stlMap.end();
        }

        return result;
    }
    
	
public:
	typedef typename AbstractMap<K, V>::ConstMapVisitor ConstMapVisitor;

public:
    void removeBy(const V& value)
    {
        WRITE_SYNCHRONIZED
        {
            for(typename StlMap::iterator iter = stlMap.begin(); iter != stlMap.end();)
            {
                if (iter->second == value) stlMap.erase(iter++);
                else iter++;
            }
        }
    }

    void removeOtherKeyExcept(const K& key, const V& value)
    {
        WRITE_SYNCHRONIZED
        {
            for(typename StlMap::iterator iter = stlMap.begin(); iter != stlMap.end();)
            {
                if (iter->second == value && key != iter->first) stlMap.erase(iter++);
                else iter++;
            }
        }
    }

    void visit(ConstMapVisitor& visitor) const
    {
        READ_SYNCHRONIZED
        {
            for(typename StlMap::const_iterator iter = stlMap.begin(); iter != stlMap.end(); ++iter)
            {
                visitor.visit(iter->first, iter->second);
            }
        }
    }

    void clear()
    {
        WRITE_SYNCHRONIZED
        {
            stlMap.clear();
        }
    }

    bool empty() const
    {
        return stlMap.empty();
    }

private:
    typedef std::pair<K, V> NODE_TYPE;
    typedef std::map<K, V, std::less<K>, ALLOCTOR > StlMap;
    StlMap stlMap;

    DEF_RWLOCK_VAR(LOCK);
};

/////////////////////////////////////////////////////////////////////
#define __DECL_STL_MAP(p_name, p_key, p_value, p_num, p_lock)\
typedef SingleStlAllocator<std::pair<p_key, p_value>, p_num> p_name##Alloctor;\
typedef Map<p_key, p_value, p_num, 1, p_lock, p_name##Alloctor> p_name
//////////////////////////////////////////////////////////////////////////
#define DECL_STL_MAP_NO_LOCK(p_name, p_key, p_value, p_num)\
        __DECL_STL_MAP(p_name, p_key, p_value, p_num, DummyRwLock)
//////////////////////////////////////////////////////////////////////////
#define DECL_STL_MAP_WITH_LOCK(p_name, p_key, p_value, p_num)\
        __DECL_STL_MAP(p_name, p_key, p_value, p_num, PthreadRwLock)

//////////////////////////////////////////////////////////////////////////
#define INST_MAP_TYPE(p_name)  p_name##ImplOnInst
#define MAIN_MAP_TYPE(p_name)  p_name##ImplOnMain
#define VISITOR_NAME(p_name)   p_name##Impl##Visitor
#define GET_UE_ID_MAP(p_name)  get##p_name##OnInst()

#define DEF_UE_ID_MAP(p_name, p_key, p_value, p_num)                                \
namespace                                                                           \
{                                                                                   \
    typedef Map<p_key, p_value, p_num,                                               \
                MAX_SERVICE_INST_THREAD_NUM,                                        \
                PthreadRwLock> INST_MAP_TYPE(p_name);                               \
                                                                                    \
    typedef MultiThreadWrapper<INST_MAP_TYPE(p_name)>  p_name##OnInst;              \
    p_name##OnInst& get##p_name##OnInst()                                           \
    {                                                                               \
        static p_name##OnInst inst;                                                 \
        return inst;                                                                \
    }                                                                               \
                                                                                    \
    struct VISITOR_NAME(p_name)                                                     \
                        : ConstThreadElemVisitor<INST_MAP_TYPE(p_name)>             \
    {                                                                               \
        VISITOR_NAME(p_name)(const p_key& key)                                      \
            : key(key), value(0)                                                     \
        {                                                                           \
        }                                                                           \
        OVERRIDE(Status visit(const INST_MAP_TYPE(p_name)& map))                    \
        {                                                                           \
            if(value == 0)                                                           \
            {                                                                       \
                value = const_cast<p_value*>(map.get(key));                           \
            }                                                                       \
            return USI_SUCCESS;                                                     \
        }                                                                           \
        p_value* getValue() const                                                     \
        {                                                                           \
            return value;                                                            \
        }                                                                           \
    private:                                                                        \
        const p_key& key;                                                           \
        p_value* value;                                                               \
    };                                                                              \
                                                                                    \
    struct MAIN_MAP_TYPE(p_name) : AbstractMap<p_key, p_value>                       \
    {                                                                               \
        Status put(const p_key& key, const p_value& value) throw()                   \
        {                                                                           \
            return USI_FAILED;                                                      \
        }                                                                           \
        const p_value* get(const p_key& key) const                                   \
        {                                                                           \
            VISITOR_NAME(p_name) visitor(key);                                      \
            USI_ASSERT_SUCC_CALL_NIL(GET_UE_ID_MAP(p_name).visitAllThreadElems(visitor));       \
            return visitor.getValue();                                               \
        };                                                                          \
        bool contains(const p_key& key)                                             \
        {                                                                           \
            return get(key) != 0;                                                   \
        }                                                                           \
        DEFAULT(void, remove(const p_key& key));                                    \
        DEFAULT(void, removeBy(const p_value& value));                               \
        DEFAULT(void, removeOtherKeyExcept( const p_key& key                        \
                                          , const p_value& value));                  \
        DEFAULT(void, visit(ConstMapVisitor& visitor) const);                       \
        DEFAULT(void, clear());                                                     \
        DEFAULT(bool, empty() const);                                               \
    }p_name##mapOnMain;                                                             \
}                                                                                   \
                                                                                    \
p_name::ThisMap& p_name::getInstance()                                              \
{                                                                                   \
    if(!ThreadInfo::isOnThreadMain()) return p_name##mapOnMain;                     \
    return *GET_UE_ID_MAP(p_name);                                                  \
}

#define __DEF_UE_ID_MAP(p_name, p_key, p_num)  DEF_UE_ID_MAP(p_name, p_key, WORD16, p_num)

#endif
