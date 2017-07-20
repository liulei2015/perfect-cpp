#ifndef INCL_FT_Tracer_20131029092546_H_
#define INCL_FT_Tracer_20131029092546_H_

#include "fw/ftest.h"
#include "l0-infra/base/BaseTypes.h"
#include <iostream>
#include "l0-infra/base/Singleton.h"

FTESTING_NS_BEGIN

////////////////////////////////////////////////////////
struct ConsoleState
{
   bool isColorful() const
   {
      return colorful;
   }

protected:
   ConsoleState(bool c)
      : colorful(c)
   {}

private:
      bool colorful;
};

////////////////////////////////////////////////////////
#define DEF_COLOR_STATE(state)                       \
struct state : public ConsoleState                   \
{                                                    \
   state(bool colorful) : ConsoleState(colorful)     \
   {}                                                \
};                                                   \
std::ostream& operator<<(std::ostream& os, const state& succ);

////////////////////////////////////////////////////////
DEF_COLOR_STATE(SuccState)
DEF_COLOR_STATE(FailState)
DEF_COLOR_STATE(NormalState)
DEF_COLOR_STATE(InfoState)
DEF_COLOR_STATE(WarnState)
DEF_COLOR_STATE(DebugState)

///////////////////////////////////////////////////////
struct StdoutListener
{
    static StdoutListener* create(bool colorful);
    static StdoutListener& getInstance();
    static void destory();

    void println(const BYTE level, const char* msg);

private:
    StdoutListener(bool colorful);

    template <typename STATE>
    void doPrint(const STATE& state, const char* msg);

    static StdoutListener* inst;

private:
    SuccState succ;
    FailState fail;
    NormalState normal;
    InfoState info;
    WarnState warn;
    DebugState debug;
};

FTESTING_NS_END

#endif
