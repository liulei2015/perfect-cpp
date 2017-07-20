/*
 * Keywords.h
 *
 *  Created on: Apr 13, 2013
 *      Author: arthur
 */

#ifndef KEYWORDS_H_
#define KEYWORDS_H_

#include <l0-infra/base/Default.h>
#include "l0-infra/base/Config.h"

#define ABSTRACT(...) virtual __VA_ARGS__ = 0


#if __SUPPORT_VIRTUAL_OVERRIDE
#   define OVERRIDE(...) virtual __VA_ARGS__ override
#else
#   define OVERRIDE(...) virtual __VA_ARGS__
#endif

#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

#endif /* KEYWORDS_H_ */

