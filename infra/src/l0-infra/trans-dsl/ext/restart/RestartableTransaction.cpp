#include "l0-infra/trans-dsl/ext/restart/RestartableTransaction.h"
#include "l0-infra/trans-dsl/utils/ActionStatus.h"

USI_NS_BEGIN

namespace details
{
    RestartableTransaction::RestartableTransaction() 
        : iid((WORD32)0), timerInfo(0)
    {
    }

    Status RestartableTransaction::final(Status status)
    {
        if(!ActionStatus(status).isWorking())
        {
            kill();
        }

        return status;
    }

    Status RestartableTransaction::start()
    {
        kill();

        init();

        ROLE(SchedTransaction).updateInstanceId(iid);
        if(timerInfo != 0)
        {
            ROLE(SchedTransaction).updateTimerInfo(*timerInfo);
        }

        return final(ROLE(SchedTransaction).start());
    }

    Status RestartableTransaction::handleEvent(const Event& event)
    {
        if(!isPresent()) return USI_UNKNOWN_EVENT;

        return final(ROLE(SchedTransaction).handleEvent(event));
    }

    Status RestartableTransaction::stop(const StopCause& cause)
    {
        if(!isPresent()) return cause;

        return final(ROLE(SchedTransaction).stop(cause));
    }

    void RestartableTransaction::kill(const StopCause& cause)
    {
        if(isPresent())
        {
            ROLE(SchedTransaction).kill(cause);
            clear();
        }
    }

    void RestartableTransaction::updateInstanceId(InstanceId iid)
    {
        this->iid = iid;
    }

    void RestartableTransaction::updateTimerInfo(const TimerInfo& info)
    {
        this->timerInfo = const_cast<TimerInfo*>(&info);
    }

}


USI_NS_END

