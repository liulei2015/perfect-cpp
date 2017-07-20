#ifndef INCL_USI_Dbs_Accessor_H_
#define INCL_USI_Dbs_Accessor_H_

#include "l0-infra/mem-dbs/DbsElem.h"
#include "l0-infra/base/StructObject.h"
#include "l0-infra/base/Assertions.h"
#include "l0-infra/wrapper/ng_pub_dbs.h"
#include <stdio.h>

extern "C" BOOL UsfDbsAccess(WORD16, void *, void *);

struct ParamHandler;

template<typename REQ, typename ACK, bool IS_CONTINUE = false>
struct Accessor : DbsElem
{
    OVERRIDE(Status load(void* param = 0))
    {
        initReq(param);

        USI_ASSERT_SUCC_CALL(loadFromDbs());

        return USI_SUCCESS;
    }

    OVERRIDE(bool access(WORD16 eventId, void* req, void* outAck) const)
    {
        if(!verify(eventId, req))  return false;

        assignAck(outAck);

        return true;
    }

    OVERRIDE(void dump() const)
    {
        printf("Accessor: eventId : %d\n", getEventId());
        printf("Accessor: result  : %lu\n", ack->dwResult);

        ROLE(ParamHandler).dump();
    }

private:
    bool verify(WORD16 eventId, void* req) const
    {
        if((eventId != getEventId()) || !verifyReq(req))
        {
            return false;
        }

        return true;
    }

    Status loadFromDbs()
    {
    	DBG_LOG("load from dbs eventId: [%d]", getEventId());

        if(!IS_CONTINUE)
        {
            USI_ASSERT_TRUE(0 != UsfDbsAccess( getEventId(), req.getPointer(), ack.getPointer()));
        }
        else
        {
        	USI_PEEK_TRUE(UsfDbsAccess( getEventId(), req.getPointer(), ack.getPointer()));
        }

        ROLE(ParamHandler).loadMore(getEventId(), ack.getPointer());

        return USI_SUCCESS;
    }

    void assignAck(void* outAck) const
    {
        *static_cast<ACK*>(outAck) = *ack;
    }

    void initReq(void* param)
    {
        req.reset();
        req.wCallType = USF_MSG_CALL;

        if(0 != param)
        {
            ROLE(ParamHandler).config(req.getPointer(), param);
        }
    }

    bool verifyReq(void* req) const
    {
        return ROLE(ParamHandler).verify(req);
    }

private:
    StructObject<REQ> req;
    StructObject<ACK> ack;

private:
    ABSTRACT(WORD16 getEventId() const);
    USE_ROLE(ParamHandler);
};

#endif 

