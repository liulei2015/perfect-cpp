#include "stubs/ConsoleState.h"
#include <iostream>
#include <stdarg.h>
#include "l0-infra/base/stdio_ng.h"

extern "C"
{
}

#ifdef _MSC_VER
  #include <Windows.h>
#endif


FTESTING_NS_BEGIN

#if defined(_MSC_VER)

///////////////////////////////////////////////////////////
#define C_RED     (FOREGROUND_RED   | FOREGROUND_INTENSITY)
#define C_BLUE    (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
#define C_GREEN   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define C_YELLOW  (FOREGROUND_RED   | FOREGROUND_GREEN |FOREGROUND_INTENSITY)
#define C_MAGENTA (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_WHITE   (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_GREEN )

///////////////////////////////////////////////////////////
namespace
{
   struct Color
   {
      explicit Color(unsigned int c)
         : color(c)
	  {}

      void operator()(void) const
      {
         ::SetConsoleTextAttribute
            ( ::GetStdHandle(STD_OUTPUT_HANDLE)
            , color);
      }

   private:
      unsigned int color;
   };
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Color color)
{
   color();
   return os;
}

///////////////////////////////////////////////////////////

#endif


///////////////////////////////////////////////////////////
#if defined(_MSC_VER)

#define __RED     Color(C_RED)
#define __GREEN   Color(C_GREEN)
#define __YELLOW  Color(C_YELLOW)
#define __BLUE    Color(C_BLUE)
#define __MAGENTA Color(C_MAGENTA)
#define __CYAN    Color(C_CYAN)
#define __WHITE   Color(C_WHITE)

#else

#define __RED     "\033[1;31m"
#define __GREEN   "\033[1;32m"
#define __YELLOW  "\033[1;33m"
#define __BLUE    "\033[1;34m"
#define __MAGENTA "\033[1;35m"
#define __CYAN    "\033[1;36m"
#define __WHITE   "\033[0m"

#endif

///////////////////////////////////////////////////////////
#define DEF_STATE_COLOR_MAPPING(S,C) \
std::ostream& operator<<(std::ostream& os, const S& state) \
{ \
   if(state.isColorful()) os << C; \
   return os; \
}

///////////////////////////////////////////////////////////
DEF_STATE_COLOR_MAPPING(SuccState,   __GREEN)
DEF_STATE_COLOR_MAPPING(InfoState,   __CYAN)
DEF_STATE_COLOR_MAPPING(WarnState,   __YELLOW)
DEF_STATE_COLOR_MAPPING(DebugState,  __MAGENTA)
DEF_STATE_COLOR_MAPPING(FailState,   __RED)
DEF_STATE_COLOR_MAPPING(NormalState, __WHITE)

///////////////////////////////////////////////////////////
StdoutListener* StdoutListener::inst = 0;

StdoutListener* StdoutListener::create(bool colorful)
{
    if (inst == 0)
        inst = new StdoutListener(colorful);

    return inst;
}

StdoutListener& StdoutListener::getInstance()
{
    return *inst;
}

void StdoutListener::destory()
{
    if (inst != 0)
         delete inst;
}

StdoutListener::StdoutListener(bool colorful)
        : succ(colorful)
        , fail(colorful)
        , normal(colorful)
        , info(colorful)
        , warn(colorful)
        , debug(colorful)
{
}

namespace
{
    enum
    {
        FT_DEBUG_LEVEL = 01,
        FT_INFO_LEVEL  = 02,
        FT_WARN_LEVEL  = 0x04,
        FT_ERR_LEVEL   = 0x08,
        FT_FATAL_LEVEL = 0x10
    };
}

template <typename STATE>
void StdoutListener::doPrint(const STATE& state, const char* msg)
{
    std::cout << state << msg << "\n" << normal;
}

void StdoutListener::println(const BYTE level, const char* msg)
{
#define ON_LEVEL(level, state) case level: doPrint(state, msg); break;

    switch(level)
    {
    ON_LEVEL(FT_DEBUG_LEVEL, debug)
    ON_LEVEL(FT_INFO_LEVEL,  info)
    ON_LEVEL(FT_WARN_LEVEL,  warn)
    ON_LEVEL(FT_ERR_LEVEL,   fail)
    ON_LEVEL(FT_FATAL_LEVEL, fail)
    default: doPrint(normal, msg);
    }
}

FTESTING_NS_END

USING_FTESTING_NS

//U32 OSS_Printf
//    ( WORD16   module
//    , WORD32   errId
//    , BYTE     level
//    , const void * format
//    , ...)
//{
//    va_list vaList;
//    va_start(vaList, format);
//
//    char buff[1024] = {0};
//    SWORD32 sdwRet = VSNPRINTF(buff, 1024, (const char*)format, vaList);
//
//    StdoutListener::getInstance().println(level, buff);
//
//    va_end(vaList);
//
//    return 0;
//}
