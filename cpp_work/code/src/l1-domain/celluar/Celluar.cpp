#include "l1-domain/celluar/Celluar.h"


SERVICE_NS_BEGIN

namespace
{
    auto isSatisfiedDieCondition = [](U32 roundLiveNum)
            {return (roundLiveNum == 0 || roundLiveNum == 1 || roundLiveNum > 3);};

    auto isSatisfiedLiveAgainCondition = [](U32 roundLiveNum)
                {return roundLiveNum == 3;};
}


Celluar_State Celluar::getCurrentState() const
{
    return currentState;
}

Celluar_State Celluar::getNextState()
{
    U32 roundLiveNum = round.getLiveNum();

    if(currentState == LIVE)
        nextState = isSatisfiedDieCondition(roundLiveNum) ? DIE : currentState;
    else
        nextState = isSatisfiedLiveAgainCondition(roundLiveNum) ? LIVE : currentState;

    return nextState;
}

void Celluar::setRound(const Round& round)
{
    this->round = round;
}



SERVICE_NS_END


