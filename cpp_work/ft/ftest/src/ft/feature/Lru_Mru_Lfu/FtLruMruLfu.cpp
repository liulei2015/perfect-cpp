//#include "fw/ftest.h"
//#include "l0-infra/base/BaseTypes.h"
//#include "l0-infra/base/Keywords.h"
//#include "l0-infra/log/log.h"
//#include "l0-infra/base/CacheNode.h"
//#include "l0-infra/base/CacheManager.h"
//#include "l0-infra/base/LRUWeedOutStrategy.h"
//#include "l0-infra/base/MRUWeedOutStrategy.h"
//#include "l0-infra/base/LFUWeedOutStrategy.h"
//
//USING_SERVICE_NS
//
//FTESTING_NS_BEGIN
//
//struct TestLru : testing::Test
//{
//protected:
//    virtual void doSetUp()
//    {
//        cacheManager.put(1, CacheNode(1, 10, 5));
//        cacheManager.put(2, CacheNode(100, 20, 15));
//        cacheManager.put(3, CacheNode(255, 30, 25));
//        cacheManager.put(4, CacheNode(1000, 40, 35));
//    }
//
//    virtual void doTearDown()
//    {
//    	cacheManager.clear();
//    }
//
//    OVERRIDE(void SetUp()){doSetUp();}
//    OVERRIDE(void TearDown()){doTearDown();}
//protected:
//    CacheManager cacheManager;
//};
//
////////////////////////////////////////////////////////////////////////////////////////////
////base cases, no constraint. key: unsigned int
//TEST_F(TestLru, base_get_value_by_uint_key_ok)
//{
//    INFO_LOG("TestLru, base_get_value_by_uint_key_ok");
//
//    const U32 inputKey = 3;
//    const U32 lruMeasure = 30;
//    const U32 Expected_CacheNode_Id = 255;
//    const U32 Expected_VisitTimes = 25;
//    CacheNode expectedCacheNode(Expected_CacheNode_Id, lruMeasure, Expected_VisitTimes);
//
//    ASSERT_TRUE( expectedCacheNode == cacheManager.get(inputKey));
//}
//
//TEST_F(TestLru, base_put_uint_key_value_ok)
//{
//    INFO_LOG("TestLru, base_put_uint_key_value_ok");
//
//    const U32 inputKey = 4;
//    const U32 lruMeasure = 40;
//    const U32 Expected_CacheNode_Id = 1000;
//    const U32 Expected_VisitTimes = 35;
//    CacheNode expectedNewCacheNode(Expected_CacheNode_Id, lruMeasure, Expected_VisitTimes);
//    const U32 expectedCacheNodeSize = 4;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//    ASSERT_TRUE(expectedNewCacheNode == cacheManager.get(inputKey));
//}
//
//TEST_F(TestLru, base_remove_value_by_uint_key_ok)
//{
//    INFO_LOG("TestLru, base_remove_value_by_uint_key_ok");
//    cacheManager.remove(2);
//
//    const U32 expectedCacheNodeSize = 3;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////
//
////weed out strategy: LRU, key: Container Restrict Num = 4, unsigned int
//TEST_F(TestLru, lru_put_uint_key_value_ok)
//{
//    INFO_LOG("TestLru, lru_put_uint_key_value_ok");
//
//    const U32 inputKey = 4;
//    const U32 lruMeasure = 40;
//    const U32 Expected_CacheNode_Id = 1000;
//    const U32 Expected_VisitTimes = 35;
//    CacheNode expectedNewCacheNode(Expected_CacheNode_Id, lruMeasure, Expected_VisitTimes);
//    U32 expectedCacheNodeSize = 4;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//    ASSERT_TRUE(expectedNewCacheNode == cacheManager.get(inputKey));
//    // put the fifth elem, should rm one by LRU algorithm
//    LRUWeedOutStrategy lruStrategy;
//
//    cacheManager.setStrategy(&lruStrategy);
//    cacheManager.notifyStrategyContainer();
//
//    cacheManager.put(5, CacheNode(2000, 0, 45));
//
//
//    expectedCacheNodeSize = 4;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//	ASSERT_TRUE(CacheNode(1, 10, 5) == cacheManager.get(1));
//	ASSERT_TRUE(CacheNode(100, 20, 15) == cacheManager.get(2));
//	ASSERT_TRUE(CacheNode(255, 30, 25) == cacheManager.get(3));
//	ASSERT_TRUE(CacheNode(2000, 0, 45) == cacheManager.get(5));
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
////weed out strategy: MRU, key: Container Restrict Num = 4, unsigned int
//TEST_F(TestLru, Mru_put_uint_key_value_ok)
//{
//    INFO_LOG("TestLru, Mru_put_uint_key_value_ok");
//
//    const U32 inputKey = 4;
//    const U32 lruMeasure = 40;
//    const U32 Expected_CacheNode_Id = 1000;
//    const U32 Expected_VisitTimes = 35;
//    CacheNode expectedNewCacheNode(Expected_CacheNode_Id, lruMeasure, Expected_VisitTimes);
//    U32 expectedCacheNodeSize = 4;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//    ASSERT_TRUE(expectedNewCacheNode == cacheManager.get(inputKey));
//    // put the fifth elem, should rm one by MRU algorithm
//    MRUWeedOutStrategy mruStrategy;
//
//	cacheManager.setStrategy(&mruStrategy);
//	cacheManager.notifyStrategyContainer();
//
//	cacheManager.put(5, CacheNode(2000, 0, 45));
//
//	expectedCacheNodeSize = 4;
//
//	ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//	ASSERT_TRUE(CacheNode(1000, 40, 35) == cacheManager.get(4));
//	ASSERT_TRUE(CacheNode(100, 20, 15) == cacheManager.get(2));
//	ASSERT_TRUE(CacheNode(255, 30, 25) == cacheManager.get(3));
//	ASSERT_TRUE(CacheNode(2000, 0, 45) == cacheManager.get(5));
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
////weed out strategy: LFU, key: Container Restrict Num = 4, unsigned int
//TEST_F(TestLru, Lru_put_uint_key_value_ok)
//{
//    INFO_LOG("TestLru, Lru_put_uint_key_value_ok");
//
//    const U32 inputKey = 4;
//    const U32 lruMeasure = 40;
//    const U32 Expected_CacheNode_Id = 1000;
//    const U32 Expected_VisitTimes = 35;
//    CacheNode expectedNewCacheNode(Expected_CacheNode_Id, lruMeasure, Expected_VisitTimes);
//    U32 expectedCacheNodeSize = 4;
//
//    ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//    ASSERT_TRUE(expectedNewCacheNode == cacheManager.get(inputKey));
//    // put the fifth elem, should rm one by MRU algorithm
//    LFUWeedOutStrategy lfuStrategy;
//
//	cacheManager.setStrategy(&lfuStrategy);
//	cacheManager.notifyStrategyContainer();
//
//	cacheManager.put(5, CacheNode(2000, 0, 45));
//
//	expectedCacheNodeSize = 4;
//
//	ASSERT_TRUE(expectedCacheNodeSize == cacheManager.getContainerSize());
//	ASSERT_TRUE(CacheNode(1000, 40, 35) == cacheManager.get(4));
//	ASSERT_TRUE(CacheNode(100, 20, 15) == cacheManager.get(2));
//	ASSERT_TRUE(CacheNode(255, 30, 25) == cacheManager.get(3));
//	ASSERT_TRUE(CacheNode(2000, 0, 45) == cacheManager.get(5));
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////
////weed out strategy: LRU, key: string
//TEST_F(TestLru, lru_get_value_by_string_key_ok)
//{
//    INFO_LOG("TestLru, lru_get_value_by_string_key_ok");
//    ASSERT_TRUE(1==1);
//}
//
//TEST_F(TestLru, lru_put_string_key_value_ok)
//{
//    INFO_LOG("TestLru, lru_put_string_key_value_ok");
//    ASSERT_TRUE(1==1);
//}
//
//TEST_F(TestLru, lru_delete_value_by_string_key_ok)
//{
//    INFO_LOG("TestLru, lru_delete_value_by_string_key_ok");
//    ASSERT_TRUE(1==1);
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////
////performance copare
//TEST_F(TestLru, lru_get_value_by_uint_key_performance_ok)
//{
//    INFO_LOG("TestLru, lru_get_value_by_uint_key_performance_ok");
//    ASSERT_TRUE(1==1);
//}
//
//TEST_F(TestLru, lru_put_uint_key_value_performance_ok)
//{
//    INFO_LOG("TestLru, lru_put_uint_key_value_performance_ok");
//    ASSERT_TRUE(1==1);
//}
//
//TEST_F(TestLru, lru_delete_value_by_uint_key_performance_ok)
//{
//    INFO_LOG("TestLru, lru_delete_value_by_uint_key_performance_ok");
//    ASSERT_TRUE(1==1);
//}
////////////////////////////////////////////////////////////////////////////////////////////
//
//FTESTING_NS_END
//
//
