/*
 * TransStrategy.h
 *
 *  Created on: Oct 28, 2012
 *      Author: arthur
 */

#ifndef TRANSSTRATEGY_H_
#define TRANSSTRATEGY_H_

#include "l0-infra/base/BaseTypes.h"

USI_NS_BEGIN

//////////////////////////////////////////////////////////////////////////
const BYTE __TS_KEEP_OLD = 0x01;
const BYTE __TS_STOP_OLD = 0x02;
const BYTE __TS_KILL_OLD = 0x04;
const BYTE __TS_SUSP_OLD = 0x08;

const BYTE __TS_BUFF_NEW  = 0x01;
const BYTE __TS_DENY_NEW  = 0x02;
const BYTE __TS_DROP_NEW = 0x03;
const BYTE __TS_EXEC_NEW = 0x04;

const BYTE __TS_NORM_SCHED = 0;
const BYTE __TS_FAIL_SCHED = 1;

//////////////////////////////////////////////////////////////////////////
#define __TS_DEF(ts_old, ts_new, ts_sched) \
   (__TS_##ts_old << 8) | (__TS_##ts_new << 1) | (__TS_##ts_sched)

//////////////////////////////////////////////////////////////////////////
typedef WORD16 TransStrategy;

//////////////////////////////////////////////////////////////////////////
const TransStrategy TS_DISCARD            = __TS_DEF(KEEP_OLD, DROP_NEW, NORM_SCHED);
const TransStrategy TS_REJECT             = __TS_DEF(KEEP_OLD, DENY_NEW, NORM_SCHED);
const TransStrategy TS_BUFFER             = __TS_DEF(KEEP_OLD, BUFF_NEW, NORM_SCHED);
const TransStrategy TS_INTERRUPT          = __TS_DEF(STOP_OLD, DROP_NEW, NORM_SCHED);
const TransStrategy TS_INTERRUPT_FAIL     = __TS_DEF(STOP_OLD, DROP_NEW, FAIL_SCHED);

const TransStrategy TS_PREEMPT            = __TS_DEF(STOP_OLD, BUFF_NEW, NORM_SCHED);
const TransStrategy TS_REPLACE            = __TS_DEF(KILL_OLD, EXEC_NEW, NORM_SCHED);
const TransStrategy TS_FAIL               = __TS_DEF(KILL_OLD, DROP_NEW, FAIL_SCHED);
const TransStrategy TS_REJ_FAIL           = __TS_DEF(KILL_OLD, DENY_NEW, FAIL_SCHED);
const TransStrategy TS_REJ_INTERRUPT      = __TS_DEF(STOP_OLD, DENY_NEW, NORM_SCHED);
const TransStrategy TS_SUSPEND            = __TS_DEF(SUSP_OLD, EXEC_NEW, NORM_SCHED);
const TransStrategy TS_INTERRUPT_SUSPEND  = __TS_DEF(STOP_OLD, EXEC_NEW, NORM_SCHED);

const TransStrategy TS_NIL                = 0;
const TransStrategy TS_UNKNOWN            = 0xFFFF;

//////////////////////////////////////////////////////////////////////////

USI_NS_END

#endif /* TRANSSTRATEGY_H_ */

