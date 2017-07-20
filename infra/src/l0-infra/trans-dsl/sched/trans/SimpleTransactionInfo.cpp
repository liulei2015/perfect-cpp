///*
// * SimpleTransactionInfo.cc
// *
// *  Created on: Apr 23, 2013
// *      Author: arthur
// */
//
//#include "l0-infra/trans-dsl/sched/trans/SimpleTransactionInfo.h"
//#include "l0-infra/trans-dsl/sched/concept/RuntimeContext.h"
//#include "l0-infra/trans-dsl/sched/concept/RuntimeContextInfo.h"
//#include "l0-infra/trans-dsl/utils/ActionStatus.h"
//#include "l0-infra/base/Likely.h"
//
///////////////////////////////////////////////////////////////////
//SimpleTransactionInfo::SimpleTransactionInfo(InstanceId iid)
//{
//    TransactionInfo::iid = iid;
//}
//
//void SimpleTransactionInfo::updateInstanceId(InstanceId iid)
//{
//   TransactionInfo::iid = iid;
//}
//
///////////////////////////////////////////////////////////////////
//Status SimpleTransactionInfo::getStatus() const
//{
//   RuntimeContext* context = ROLE(RuntimeContextInfo).getRuntimeContext();
//   if(__unlikely(context == 0))
//   {
//      return USI_SUCCESS;
//   }
//
//   Status status = context->getStatus();
//   return IS_FAILED_STATUS(status) ? status : USI_SUCCESS;
//}
//
///////////////////////////////////////////////////////////////////
//void SimpleTransactionInfo::updateUserContext(dci::Unknown* userContext)
//{
//   TransactionInfo::userContext = userContext;
//}
