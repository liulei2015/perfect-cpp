#ifndef _INCLUDE_FTEST_1551
#define _INCLUDE_FTEST_1551

#include "gtest/gtest.h"

#define FTESTING_NS ftesting
#define FTESTING_NS_BEGIN namespace FTESTING_NS {
#define FTESTING_NS_END   }
#define USING_FTESTING_NS using namespace FTESTING_NS;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#endif
