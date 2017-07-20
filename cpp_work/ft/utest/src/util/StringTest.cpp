#include "utest.h"
#include "l0-infra/log/log.h"
#include <string>

using std::string;


UTESTING_NS_BEGIN

struct StringTest : testing::Test
{
};

TEST_F(StringTest, add_tail_ok)
{
    INFO_LOG("StringTest, add_tail_ok e.g. append '\0");

    string req = "I will do mo req";
    char* req_char =  const_cast<char*>(req.c_str());
    printf("string req: %s\n", req_char);
    for(BYTE i =0; i< req.length(); i++)
        printf("req_char[%u] : %d\n", i, req_char[i]);
    string req2 = req + '\0';
    char* req2_char =  const_cast<char*>(req2.c_str());
    printf("string req2: %s\n", req2.c_str());
    for(BYTE i =0; i< req2.size(); i++)
            printf("req2_char[%u] : %d\n", i, req2_char[i]);

    char* req3_char = const_cast<char*>((req+'\0').c_str());
    printf("string req3: %s\n", req2.c_str());
    for(BYTE i =0; i< req.size()+1; i++)
            printf("req3_char[%u] : %d\n", i, req3_char[i]);

}

UTESTING_NS_END


