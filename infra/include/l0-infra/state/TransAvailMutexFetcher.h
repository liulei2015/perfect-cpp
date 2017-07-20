#ifndef INCL_TransAvailMutexFetcher_2013814115531_H
#define INCL_TransAvailMutexFetcher_2013814115531_H

#include "l0-infra/dci/Role.h"
#include "l0-infra/trans-dsl/ext/mutex/concept/TransMutextId.h"

USI_NS_BEGIN

DEFINE_ROLE(TransAvailMutexFetcher)
{
    ABSTRACT(TransMutexId fetchAailMutex());
};

USI_NS_END

#endif
