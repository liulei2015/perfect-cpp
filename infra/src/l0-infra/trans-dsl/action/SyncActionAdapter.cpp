///*
// * SyncActionAdapter.cc
// *
// *  Created on: Apr 24, 2013
// *      Author: arthur
// */
//
//#include "l0-infra/trans-dsl/action/SyncActionAdapter.h"
//#include "l0-infra/trans-dsl/utils/ActionStatus.h"
//
/////////////////////////////////////////////////////////
//Status SyncActionAdapter::exec(const TransactionInfo& trans)
//{
//   ActionStatus status = ROLE(SyncAction).exec(trans);
//   if(status.isWorking())
//   {
//      return USI_FATAL_BUG;
//   }
//
//   return status;
//}
//
////////////////////////////////////////////////////////////////////////
//Status SyncActionAdapter::handleEvent(const TransactionInfo&, const Event&)
//{
//   return USI_UNKNOWN_EVENT;
//}
//
/////////////////////////////////////////////////////////
//void SyncActionAdapter::kill(const TransactionInfo&, const Status)
//{
//}
