#ifndef INCL_mem_zero_20131128135745_H_
#define INCL_mem_zero_20131128135745_H_

#include <string.h>

#define USI_MEM_SET_V(type, value) ::memset(&(type), value, sizeof((type)));
#define USI_MEM_SET(type) USI_MEM_SET_V(type, 0x00)

#endif

