#ifndef INCL_USI_RestartableTransaction_2013098200314_H__
#define INCL_USI_RestartableTransaction_2013098200314_H__

#include "l0-infra/trans-dsl/sched/trans/SchedTransaction.h"
#include "l0-infra/base/Maybe.h"
#include "l0-infra/trans-dsl/sched/concept/Transaction.h"
#include "l0-infra/trans-dsl/sched/concept/InstanceId.h"

struct Event;

USI_NS_BEGIN

namespace details
{
    struct RestartableTransaction : Transaction
    {
        RestartableTransaction();

        OVERRIDE(Status start());
        OVERRIDE(Status handleEvent(const Event& event));
        OVERRIDE(Status stop(const StopCause& cause = StopCause()));
        OVERRIDE(void   kill(const StopCause& = StopCause()));

        void updateInstanceId(InstanceId iid);
        void updateTimerInfo(const TimerInfo& info);

    private:
        Status final(Status status);

    private:
        InstanceId iid;
        TimerInfo* timerInfo;

    private:
        ABSTRACT(bool isPresent() const);
        ABSTRACT(void init());
        ABSTRACT(void clear());

        USE_ROLE(SchedTransaction);
    };

}

template <typename P_TRANS>
struct RestartableTransaction : details::RestartableTransaction
{
    ~RestartableTransaction()
    {
        if(isPresent())
        {
            trans->kill();
            clear();
        }
    }

private:
    OVERRIDE(bool isPresent() const)
    {
        return trans.isPresent();
    }

    OVERRIDE(void init())
    {
        trans.forceEffective();
        new (trans.getPointer()) P_TRANS();
    }

    OVERRIDE(void clear())
    {
        trans.reset();
    }

    DECL_ROLE(SchedTransaction)
    {
        return trans.getRef();
    }

private:
    mutable Maybe<P_TRANS> trans;
};

USI_NS_END

#endif

