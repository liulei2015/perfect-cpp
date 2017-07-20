#include "l0-infra/log/LogModule.h"
#include "l0-infra/log/UsfLog.h"
//#include "oss_timer.h"
#include <map>
//#include <string>
#include <stdarg.h>
#include <string.h>

using namespace std;

struct LevelInfo
{
	LevelInfo() :name(NULL),index(0),colorIndex(0){}
	LevelInfo(const char *name, BYTE index, BYTE colorIndex) : name(name), index(index), colorIndex(colorIndex) {}
	const char *name;
	BYTE index;
	BYTE colorIndex;/* 30:濠殿喗甯楅崘濠氬箯閿燂拷  31:缂傚倷鐒﹂幏婵嬪箯閿燂拷  32:缂傚倸鍊风欢銈夊箯閿燂拷  33:濠殿喗甯楅崘濠氬箯閿燂拷	34:闂備浇妫勯崯顖滄崲閸℃鐝堕柨鐕傛嫹	35:缂傚倷绶氱涵鎼佸磻婢跺鐝堕柨鐕傛嫹	36:婵犵數鍎戠紞锟藉ù婊庡墰閹告帡鏁撻敓锟�	37:闂備浇鐨崘鎸庡闁绘柨顨庡Λ锟�*/
};

static map<BYTE, LevelInfo> levels = {
		{DEBUG_LEVEL, LevelInfo("DEBUG", 1, 37)},
		{INFO_LEVEL, LevelInfo("INFO", 2, 32)},
		{WARN_LEVEL, LevelInfo("WARN", 3, 33)},
		{ERROR_LEVEL, LevelInfo("ERROR", 4, 31)},
		{FATAL_LEVEL, LevelInfo("FATAL", 5, 35)}
};

const char * getPrintLevelStr(BYTE ucPrtLevel)
{
    return levels[ucPrtLevel].name;
}

BYTE getLogLevelIndex(BYTE ucPrtLevel)
{
	return levels[ucPrtLevel].index;
}

BYTE getLogLevelColor(BYTE ucPrtLevel)
{
	return levels[ucPrtLevel].colorIndex;
}

bool LogModule::isLogLevelEnable(BYTE logLevel)
{
    return (getLogLevelIndex(logLevel) >= curLogLevel);
}

void LogModule::setCurLogLevel(BYTE logLevel)
{
    if(logLevel == 0 || logLevel > 5)
        curLogLevel = 6;
    else
        curLogLevel = logLevel;
}

namespace{
    struct LogModuleMgr
    {
        static LogModuleMgr& GetInstance()
        {
            static LogModuleMgr *inst = NULL;
            if(inst == NULL)
            {
                inst = new LogModuleMgr();
                inst->init();
            }
            return *inst;
        }

        void init();
        LogModule& getLogModule(const char *strModule);
        LogModule& getLogModule(U16 moduleNo);
        void setAllModuleLogLevel(BYTE level);
        void helpPrintSet();
    };

#define GET_LOGMODULEMGR()  LogModuleMgr::GetInstance()

    struct NullLogModule : LogModule
    {
        NullLogModule() : LogModule("unkown") {}
        virtual void setCurLogLevel(BYTE logLevel)
        {
            GET_LOGMODULEMGR().helpPrintSet();
        }
    };
    
    map<U16, LogModule> logModules; 
    static NullLogModule nullModule;
}

void LogModuleMgr::init()
{
    logModules[RRMCELL_MODULE] = LogModule("rrmcell");
    logModules[MCMCELL_MODULE] = LogModule("mcmcell");
    logModules[RRMUE_MODULE] = LogModule("rrmue");
    logModules[RRMLM_MODULE] = LogModule("rrmlm");
    logModules[CCMMAIN_MODULE] = LogModule("ccmmain");
    logModules[CCMINST_MODULE] = LogModule("ccminst");
    logModules[DCMMAIN_MODULE] = LogModule("dcmmain");
    logModules[DCMINST_MODULE] = LogModule("dcminst");
    logModules[USF_MODULE] = LogModule("usf");
    logModules[FT_MODULE] = LogModule("ft");
}

LogModule& LogModuleMgr::getLogModule(U16 moduleNo)
{
    if(logModules.count(moduleNo))
    {
        return logModules[moduleNo];
    }
    return nullModule;
}

LogModule& LogModuleMgr::getLogModule(const char *strModule)
{
    for(auto &module: logModules)
    {
        if(0 == strcmp(module.second.name, strModule))
            return module.second;
    }
    return nullModule;
}

void LogModuleMgr::setAllModuleLogLevel(BYTE level)
{
    for(auto &module: logModules)
    {
        module.second.setCurLogLevel(level);
    }
}

void LogModuleMgr::helpPrintSet()
{
    printf(">>>>>>>>>>>>>>>>PrintSet Use:--begin>>>>>>>>>>>>>>>> \n");
    printf("PrintSet(const CHAR *strModule, BYTE ucLevel);\n");
    printf("Support modules:");
    for(auto &module: logModules)
    {
        printf("%s,", module.second.name);
    }
    printf("all \n");
    printf("ucLevel value:    0--Close all print \n");
    printf("                  1--Print all level \n");
    printf("                  2--print INFO and above level \n");
    printf("                  3--print WARN and above level \n");
    printf("                  4--print ERROR and FATAL level \n");
    printf("                  5--print FATAL level \n");
    printf("example:PrintSet \"all\", 0 ----Close all module print. \n");
    printf("        PrintSet \"all\", 4 ----Print INFO and above level for all module. \n");
    printf("        PrintSet \"rrm\", 5 ----Only Print FATAL level for rrm module. \n");
    printf("<<<<<<<<<<<<<<<<PrintSet Use:--end  <<<<<<<<<<<<<<<< \n");
}

LogModule& getLogModule(U16 moduleNo)
{
    return GET_LOGMODULEMGR().getLogModule(moduleNo);
}

LogModule& getLogModule(const char *strModule)
{
    return GET_LOGMODULEMGR().getLogModule(strModule);
}

extern "C" void PrintSet(const CHAR *strModule, BYTE level)
{
    if(strcmp(strModule, "all") == 0)
    {
        GET_LOGMODULEMGR().setAllModuleLogLevel(level);
        return ;
    }

    getLogModule(strModule).setCurLogLevel(level);
}

#define MAX_FILENAME_LEN        360
#define MAX_LOG_INFO_LEN        550

extern "C" void uniLog(U16 softmodule,
                       const char *pcFileName,
                       U32  dwLineNum, BYTE ucPrtLevel,
                       const char *pchPrtInfo,
                       ...)
{
    if (NULL != pchPrtInfo && getLogModule(softmodule).isLogLevelEnable(ucPrtLevel))
    {
        static char achFileInfo[MAX_FILENAME_LEN + 1];
        static char achLogBuff[MAX_LOG_INFO_LEN + 1];

        achFileInfo[0] = 0;
        achLogBuff[0] = 0;
//        T_SoftClock tSysClock;
//        OSS_GetClock(&tSysClock);
//        %u-%u-%u %u:%u:%u.%u
        sprintf(achFileInfo, "[ %s-%s](%s:%d):",
//            tSysClock.wSysYear, tSysClock.ucSysMon, tSysClock.ucSysDay,
//            tSysClock.ucSysHour, tSysClock.ucSysMin, tSysClock.ucSysSec, tSysClock.wMilliSec,
            getLogModule(softmodule).name, getPrintLevelStr(ucPrtLevel),
			BASE_NAME(pcFileName), dwLineNum);

        va_list tParamList;
        memset(&tParamList, 0, sizeof(va_list));
        /* lint -e530 */
        va_start(tParamList, pchPrtInfo);
        /* lint +e530 */
        /* lint -restore */
        /* lint -save -e64 */
        vsnprintf(achLogBuff, MAX_LOG_INFO_LEN, pchPrtInfo, tParamList);
        /* lint -restore */
        va_end(tParamList);

        printf("\033[%dm%s %s\n\033[0m", getLogLevelColor(ucPrtLevel), achFileInfo, achLogBuff);
    }
}

