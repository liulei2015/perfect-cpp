#include "gtest/gtest.h"
#include "l0-infra/base/Keywords.h"
#include "stubs/ConsoleState.h"

#include <celero/Celero.h>

USING_FTESTING_NS

namespace
{
    extern "C" void setDebugTraceSwitch(BYTE flag);
    extern "C" void setTraceMeSwitch(BYTE flag);
    extern "C" void PrintSet(const CHAR *strModule, BYTE level);

    struct FtServiceEnv : testing::Environment
    {
    };

    void initDumpTraceSwitch(bool colorful, bool verbose)
    {
        StdoutListener::create(colorful);

        bool on = verbose ? 1 : 0;
        setTraceMeSwitch(on);
        setDebugTraceSwitch(on);

        if(!verbose)
        {
//            PrintSet("all", 0);
//            PrintSet("ft", 3);
        }
    }
 }

bool hasVerbose(int argc, char* argv[])
   {
       for(int i = 0; i< argc; i++)
       {
           if(strcmp(argv[i], "verbose") == 0)
               return true;
       }
       return false;

   }

int main(int argc, char **argv)
{
    testing::GTEST_FLAG(break_on_failure) = 0;
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new FtServiceEnv());
    // append --gtest_verbose into google test option list when output detail log.
    initDumpTraceSwitch(true, hasVerbose(argc, argv));

    RUN_ALL_TESTS();

    celero::Run(argc, argv);

    return 0;

}


