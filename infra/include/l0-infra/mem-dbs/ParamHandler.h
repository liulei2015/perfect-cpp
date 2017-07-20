#ifndef INCL_USI_Dbs_ParaHandler_H_
#define INCL_USI_Dbs_ParaHandler_H_

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Default.h"
#include "l0-infra/dci/Role.h"

DEFINE_ROLE(ParamHandler)
{
    virtual bool verify(void* req) const
    {
        return true;
    }

    DEFAULT(void, config(void* req, void* param));
    DEFAULT(void, dump() const);

    DEFAULT(void, loadMore(const WORD16 eventId, void* ack) const);
};

#endif

