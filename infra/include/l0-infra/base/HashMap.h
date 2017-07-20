#ifndef INCL_USI_H569AC47A_98D9_42AD_B1C8_4EF1EA3DFAD7
#define INCL_USI_H569AC47A_98D9_42AD_B1C8_4EF1EA3DFAD7

#include "l0-infra/base/SequenceAllocator.h"
#include "l0-infra/base/NullPtr.h"
#include "l0-infra/base/Status.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/base/AbstractMap.h"
#include <string.h>

template <typename K, typename V, typename HASH_FUN, typename PRED, WORD32 MAX_SIZE>
struct HashMap
{
    HashMap()
    {
        memset(bucketList, 0, sizeof(bucketList));
    }

    const V* get(const K& key) const
    {
        Bucket* bucket = __null_ptr__;
        bucket = bucketList[getIndex(key)];

        for (WORD32 i = 0; (__null_ptr__ != bucket) && (i < MAX_SIZE); i++)
        {
            if (pred(key, bucket->pair.key))
            {
                return &(bucket->pair.value);
            }

            bucket = bucket->nextPair;
        }

        return __null_ptr__;
    }

    bool contains(const K& key)
    {
        Bucket *bucket = __null_ptr__;
        bucket = bucketList[getIndex(key)];

        for (WORD32 i = 0; (__null_ptr__ != bucket) && (i < MAX_SIZE) ; i++)
        {
            if (pred(key, bucket->pair.key))
            {
                return true;
            }
            bucket = bucket->nextPair;
        }

        return false;
    }

    bool empty() const
    {
        return bucketAllocator.getFreeNum() == MAX_SIZE;
    }

    Status put(const K& key, const V& value)
    {
        if(contains(key))
        {
            V* lastValue = const_cast<V*>(get(key));
            *lastValue = value;
            return USI_SUCCESS;
        }

        Bucket* bucket = __null_ptr__;
        bucket = bucketAllocator.alloc();
        USI_ASSERT_VALID_PTR(bucket);
        bucket->fillPair(key, value);

        WORD16 index  = getIndex(key);
        Bucket* head = bucketList[index];

        if(head == __null_ptr__)
        {
            bucketList[index] = bucket;
            return USI_SUCCESS;
        }

        for (WORD32 i = 0; (head->nextPair != __null_ptr__) && (i < MAX_SIZE); i++)
        {
            head = head->nextPair;
        }
        head->nextPair = bucket;

        return USI_SUCCESS;
    }

    void remove(const K& key)
    {
        USI_ASSERT_TRUE_VOID(contains(key));

        WORD16   index  = getIndex(key);
        Bucket* head = bucketList[index];

        if (pred(head->pair.key, key))
        {
            bucketList[index] = head->nextPair;
            bucketAllocator.free(head);
            head->nextPair = __null_ptr__;
            return;
        }

        Bucket* preCursor = head;
        Bucket* cursor = head->nextPair;
        for (WORD32 i = 0; ((cursor != __null_ptr__) && !pred(key, cursor->pair.key)) && (i < MAX_SIZE); i++)
        {
            preCursor = cursor;
            cursor = cursor->nextPair;
        }

        USI_ASSERT_VALID_PTR_VOID(cursor);
        if (pred(key, cursor->pair.key))
        {
            preCursor->nextPair = cursor->nextPair;
            bucketAllocator.free(cursor);
            cursor->nextPair = __null_ptr__;
        }
    }

    //important, ahead of dcmng removeBy, please think about performance!!!
    void removeBy(const V& value)
    {
        for(WORD32 i = 0; i < MAX_SIZE; i++)
        {
            Bucket* cursor = bucketList[i];
            while(cursor != __null_ptr__)
            {
                if(cursor->pair.value == value)
                {
                    Bucket* nextCursor = cursor->nextPair;
                    remove(cursor->pair.key);
                    cursor = nextCursor;
                    continue;
                }
                cursor = cursor->nextPair;
            }
        }
    }

    //important, ahead of dcmng removeBy, please think about performance!!!
    void removeOtherKeyExcept(const K& key, const V& value)
    {
        for(WORD32 i = 0; i < MAX_SIZE; i++)
        {
            Bucket* cursor = bucketList[i];
            while(cursor != __null_ptr__)
            {
                if(cursor->pair.value == value && cursor->pair.key != key)
                {
                    Bucket* nextCursor = cursor->nextPair;
                    remove(cursor->pair.key);
                    cursor = nextCursor;
                    continue;
                }
                cursor = cursor->nextPair;
            }
        }
    }

    //important, ahead of dcmng removeBy, please think about performance!!!
    typedef typename AbstractMap<K, V>::ConstMapVisitor ConstMapVisitor;
    void visit(ConstMapVisitor& visitor) const
    {
        for(WORD32 i = 0; i < MAX_SIZE; i++)
        {
            Bucket* cursor = bucketList[i];
            while(cursor != __null_ptr__)
            {
                visitor.visit(cursor->pair.key, cursor->pair.value);
                cursor = cursor->nextPair;
            }
        }
    }

    void dump()
    {
        printf("\n-----------------------------------------\n");
        for(WORD32 i = 0; i < MAX_SIZE; i++)
        {
        	Bucket* cursor = bucketList[i];
        	printf("bucketList[%lu]: ", i);
        	while(cursor != __null_ptr__)
        	{
        		cursor->dump();
        		cursor = cursor->nextPair;
        	}
        	printf("\n");
        }
    }

private:
    struct HashPair
    {
        K key;
        V value;
    };

    struct Bucket{
        HashPair pair;
        Bucket* nextPair;

        Bucket() : nextPair(__null_ptr__)
        {
        }

        inline void fillPair(const K& key, const V& value)
        {
            pair.key = key;
            pair.value = value;
        }

        void dump() const
        {
            pair.key.dump();
            printf(" | %lu ]", (WORD32)pair.value);
            const char* format = (nextPair == 0 ? "" : " -> ");
            printf(format, nextPair);
        }
    };

private:
    WORD16 getIndex(const K &key) const
    {
        return hashFunc(key) % MAX_SIZE;
    }

private:
    Bucket*  bucketList[MAX_SIZE];
    HASH_FUN hashFunc;
    PRED     pred;
    SequenceAllocator<Bucket, MAX_SIZE>  bucketAllocator;
};

//////////////////////////////////////////////////////////////////////////

#define DEF_UE_ID_HASH_MAP(p_name, p_key, p_value, p_hash_func, p_hash_pred, p_size)     \
struct p_name                                                                     \
{                                                                                 \
    typedef HashMap<p_key, p_value, p_hash_func, p_hash_pred, p_size> ThisMap;     \
    static ThisMap& getInstance()                                                 \
    {                                                                             \
        static ThisMap map;                                                       \
        return map;                                                               \
    }                                                                             \
};

#define __DEF_UE_ID_HASH_MAP(p_name, p_key, p_hash_func, p_hash_pred, p_size)     \
        DEF_UE_ID_HASH_MAP(p_name, p_key, WORD16, p_hash_func, p_hash_pred, p_size)

#endif
