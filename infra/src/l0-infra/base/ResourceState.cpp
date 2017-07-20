#include "l0-infra/base/ResourceState.h"

ResourceState::ResourceState() : state(IDLE_STATE)
{
}

bool ResourceState::isUntouched() const
{
    return state == IDLE_STATE;
}

bool ResourceState::isAcknowledged() const
{
    return state == ACKNOWLEDGED;
}

bool ResourceState::isRequesting() const
{
    return (state == REQUESTING_0 ||
            state == REQUESTING_1);
}

bool ResourceState::isRollbacking() const
{
    return (state == ROLLBACKING_0 ||
            state == ROLLBACKING_1);
}

Status ResourceState::request()
{
    switch (state)
    {
    case IDLE_STATE:
        state = REQUESTING_0;
        break;
    case ACKNOWLEDGED:
        state = REQUESTING_1;
        break;
    default:
        return USI_FAILED;
    }

    return USI_SUCCESS;
}

Status ResourceState::reset()
{
    //if ((state != IDLE) && (state != ACKNOWLEDGED)) return USI_FAILED;

    state = IDLE_STATE;

    return USI_SUCCESS;
}

void ResourceState::confirmed()
{
    if (!isRequesting())
    {
        return;
    }
    state = ACKNOWLEDGED;
}

void ResourceState::rollbacking()
{
    switch (state)
    {
    case REQUESTING_0:
        state = ROLLBACKING_0;
        break;
    case REQUESTING_1:
        state = ROLLBACKING_1;
        break;
	default:
		break;
    }
}

void ResourceState::rollbacked()
{
    switch (state)
    {
    case ROLLBACKING_0:
        state = IDLE_STATE;
        break;
    case ROLLBACKING_1:
        state = ACKNOWLEDGED;
        break;
	default:
		break;
    }
}


