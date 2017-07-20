#ifndef INCL_static_assert_2013725105338_H
#define INCL_static_assert_2013725105338_H

#include "l0-infra/base/Config.h"

#if __SUPPORT_STATIC_ASSERT
#define __STATIC_ASSERT(expr, err_str) static_assert(expr, err_str)
#else

#define __JOIN_LINE(line) static_assert_failure##line
#define __MAKE_LINE(line) __JOIN_LINE(line)
#define MAKE_LINE __MAKE_LINE(__LINE__)

#define __STATIC_ASSERT(expr, err_str) \
    typedef int MAKE_LINE[(expr) ? 1 : -1]

#endif

#define STATIC_ASSERT(expr) __STATIC_ASSERT(expr, "static assert failed: " #expr)

#endif
