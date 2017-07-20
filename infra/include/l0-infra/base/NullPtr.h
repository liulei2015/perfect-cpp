#ifndef INCL_USI_NullPtr_20140311151414_H__
#define INCL_USI_NullPtr_20140311151414_H__

#include "l0-infra/base/Config.h"

#if __SUPPORT_NULL_PTR
#define __null_ptr__ nullptr
#else
#define __null_ptr__ 0
#endif

#define __notnull__(ptr) ptr != __null_ptr__
#define __null__(ptr) ptr == __null_ptr__

#endif

