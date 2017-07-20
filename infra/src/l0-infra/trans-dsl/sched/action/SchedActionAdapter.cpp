///*
// * SchedActionAdapter.cc
// *
// *  Created on: Apr 24, 2013
// *      Author: arthur
// */
//
//
//#include "l0-infra/trans-dsl/sched/action/SchedActionAdapter.h"
//#include "l0-infra/trans-dsl/sched/concept/TransactionContext.h"
//#include "l0-infra/trans-dsl/action/Action.h"
//
//////////////////////////////////////////////////////////////////
//Status SchedActionAdapter::exec(TransactionContext& context)
//{
//    ROLE(Action).reset();
//   return ROLE(Action).exec(context);
//}
//
//////////////////////////////////////////////////////////////////
//Status SchedActionAdapter::handleEvent(TransactionContext& context, const Event& event)
//{
//   return ROLE(Action).handleEvent(context, event);
//}
//
//////////////////////////////////////////////////////////////////
//Status SchedActionAdapter::stop(TransactionContext& context, const Status cause)
//{
//   ROLE(Action).kill(context, cause);
//
//   return cause;
//}
//
//////////////////////////////////////////////////////////////////
//void SchedActionAdapter::kill(TransactionContext& context, const Status cause)
//{
//   ROLE(Action).kill(context, cause);
//}
