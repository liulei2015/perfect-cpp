#ifndef INCL_CODER_TL_UT_HEC9C06BB_4A2F_40F4_8CEB_F5C77DB187EA
#define INCL_CODER_TL_UT_HEC9C06BB_4A2F_40F4_8CEB_F5C77DB187EA

#include "utest.h"
#include "celero/Celero.h"
#include <string>

using std::string;
using namespace celero;

UTESTING_NS_BEGIN

struct InnerClass
{
    InnerClass();
    ~InnerClass();

    string getFailCause();

private:
    struct  FailInference;
    Pimpl<FailInference> inferencer;
};


UTESTING_NS_END

#endif
