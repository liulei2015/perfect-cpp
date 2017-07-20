/*
 * MacAddress.h
 *
 *  Created on: 2016年10月28日
 *      Author: szdev
 */

#ifndef INFRA_INCLUDE_L0_INFRA_UTIL_MACADDRESS_H_
#define INFRA_INCLUDE_L0_INFRA_UTIL_MACADDRESS_H_

#include "l0-infra/base/StreamBuffer.h"

const BYTE MAC_ADDR_LEN = 6;
typedef StreamBuffer<MAC_ADDR_LEN> MacAddress;

#endif /* INFRA_INCLUDE_L0_INFRA_UTIL_MACADDRESS_H_ */
