#include "util/inner_class/InnerClass.h"
#include "celero/PimplImpl.h"
#include <iostream>

UTESTING_NS_BEGIN

struct InnerClass::FailInference
{
    FailInference():failCause("rnluUeCtxtSrbCfgFail") {}

    string sayFailCause(){return failCause;}
private:
    string failCause;
};

InnerClass::InnerClass() : inferencer()
{
}

InnerClass::~InnerClass()
{
}

string InnerClass::getFailCause()
{
    string cause = (*inferencer).sayFailCause();
    std::cout << cause << std::endl;
    return cause;
}



UTESTING_NS_END
