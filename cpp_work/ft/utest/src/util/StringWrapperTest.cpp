#include "l0-infra/string-wrapper/StringWrapper.h"
#include <iostream>
#include "utest.h"

USING_USI_NS

UTESTING_NS_BEGIN

struct StringWrapperTest : testing::Test
{
};


TEST_F(StringWrapperTest, should_split_success)
{
//    INFO_LOG("AutoMsgTest, should_alloc_all_entities_success");
    string str = "1.1, 1.2, 1.3, 1.4, 1.5";
    vector<float> l1 = {1.1,1.2,1.3,1.4,1.5};
    vector<float> l2 = {};

    StringWrapper<float> strWrapper;

    vector<string> lstr = strWrapper.split(str, ",");

    std::cout << lstr.size() << std::endl;
    for(auto each_item : lstr)
    {
        l2.push_back(strWrapper.string2Num(each_item));
    }
    for(auto each_item : l2)
        std::cout << each_item << std::endl;

    ASSERT_TRUE(l1 == l2);

}

TEST_F(StringWrapperTest, should_split_success_when_continue_comma)
{
    string str = "1.1, ,1.3,1.4,1.5";
    vector<float> l1 = {1.1, 0.0, 1.3,1.4,1.5};
    vector<float> l2 = {};

    StringWrapper<float> strWrapper;

    vector<string> lstr = strWrapper.split(str, ",");

    for(auto each_item : lstr)
        std::cout << each_item << std::endl;

    std::cout << lstr.size() << std::endl;
    for(auto each_item : lstr)
        l2.push_back(strWrapper.string2Num(each_item));
//
    std::cout << strWrapper.string2Num(" ") << std::endl;

    for(auto each_item : l2)
        std::cout << each_item << std::endl;

    vector<float> l3 = {1.1, 0.0, 1.3,1.4,1.5};
    vector<float> l4 = {1.2,0.0,3.3,4.4,5.5};

//    bool result = l3 == l4;
    // there is another problem to deal
//    ASSERT_TRUE(result);
    //test git rebase, Release1.0 commit first

    //test master commit second

    //test reset, first Release1.0 commit once

    //after reset, commit again

    //test cherry-pick, mod in master

}

UTESTING_NS_END

