#include "l0-infra/mo/MoHelper.h"
#include "l0-infra/event/concept/Event.h"

json MoHelper::getMoResult(const Event& event)
{
    return json::parse((CHAR*)event.getMsg())["result"];
}
