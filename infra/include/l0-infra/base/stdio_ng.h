#ifndef INCL_USI_stdio_ng_H
#define INCL_USI_stdio_ng_H

#include <stdio.h>

#ifdef _MSC_VER
# define  VSNPRINTF _vsnprintf
# define  SNPRINTF  _snprintf
# define  SEPERATOR '\\'
#else
# define  VSNPRINTF vsnprintf
# define  SNPRINTF  snprintf
# define  SEPERATOR '/'
#endif

#endif

