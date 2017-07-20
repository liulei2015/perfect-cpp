#include <iostream>
#include "utest.h"

UTESTING_NS_BEGIN

struct ConsoleColorTest : testing::Test
{
};


TEST_F(ConsoleColorTest, should_print_select_color)
{
    printf("\033[0;30m Hello Black. \033[0m \n" );
    printf("\033[1;30m Hello Dark_Gray. \033[0m \n" );
    printf("\033[0;34m Hello Blue. \033[0m \n" );
    printf("\033[1;34m Hello Light_Blue. \033[0m \n" );
    printf("\033[0;32m Hello Green. \033[0m \n" );
    printf("\033[1;32m Hello Light_Green. \033[0m \n" );
    printf("\033[0;31m Hello Red. \033[0m \n" );
    printf("\033[1;31m Hello Light_Red. \033[0m \n" );
    printf("\033[0;35m Hello Purple. \033[0m \n" );
    printf("\033[1;35m Hello Light_Purple. \033[0m \n" );
    printf("\033[0;33m Hello Brown. \033[0m \n" );
    printf("\033[1;33m Hello Yellow. \033[0m \n" );
    printf("\033[0;37m Hello Light_Gray. \033[0m \n" );
    printf("\033[1;37m Hello White. \033[0m \n" );
}


UTESTING_NS_END




