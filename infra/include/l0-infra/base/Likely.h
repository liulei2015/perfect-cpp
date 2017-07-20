#ifndef INCL_USI_Likely_20140311141139_H__
#define INCL_USI_Likely_20140311141139_H__

#if defined(__GNUC__)
#define __likely(expr)   __builtin_expect(!!(expr), 1)
#define __unlikely(expr) __builtin_expect(!!(expr), 0)
#else
#define __likely(expr)   !!(expr)
#define __unlikely(expr) !!(expr)
#endif

#endif

