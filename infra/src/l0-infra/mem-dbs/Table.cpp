#include "l0-infra/mem-dbs/Table.h"
#include "l0-infra/mem-dbs/TriggerMatcher.h"
#include "l0-infra/event/concept/Event.h"

bool Table::access(WORD16 eventId, void* req, void* ack) const
{

        return ROLE(DbsElem).access(eventId, req, ack);

    return USI_SUCCESS;
}

Status Table::load(void* param)
{
    if(!verify(param))  return USI_SUCCESS;
    
    return ROLE(DbsElem).load(param);

    return USI_SUCCESS;
}

void Table::dump() const
{
    ROLE(DbsElem).dump();
}

bool Table::verify(void* param) const
{
    if(0 == param) return true;

    return verifyTrigger(static_cast<WORD16>(static_cast<Event*>(param)->getEventId()));
}

bool Table::verifyTrigger(WORD16 triggerId) const
{
    return ROLE(TriggerMatcher).isMatched(triggerId);
}

