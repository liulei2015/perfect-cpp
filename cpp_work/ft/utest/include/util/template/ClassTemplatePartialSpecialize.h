#ifndef INCL_CODER_TL_UT_H1C033C86_229F_4484_B5DA_34A5FC3296AE
#define INCL_CODER_TL_UT_H1C033C86_229F_4484_B5DA_34A5FC3296AE

#include "utest.h"
#include <string>

using std::string;

UTESTING_NS_BEGIN

class NormalBb
{
};

class NormalRnlu
{
};

//inner interface config : {bb, rnlu, rru}
template <class BB, class RNLU, bool IsCfgRru = true>
class ClassTemplatePartialSpecialize
{
public:
    string cfg()
    {
        return string("Cfg-BB-RNLU-RRU");
    }
};

// partial specialize
template <class BB, class RNLU>
class ClassTemplatePartialSpecialize<BB, RNLU, false>
{
public:
    string cfg()
    {
        return string("Cfg-BB-RNLU");
    }
};

UTESTING_NS_END

#endif
