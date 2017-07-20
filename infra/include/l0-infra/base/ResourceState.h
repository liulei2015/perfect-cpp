#ifndef INCL_USI_BASE_RESOURCE_STATE_H
#define INCL_USI_BASE_RESOURCE_STATE_H

#include "l0-infra/base/Status.h"

struct ResourceState
{
    ResourceState();

    bool isUntouched() const;
    bool isAcknowledged() const;
    bool isRequesting() const;
    bool isRollbacking() const;

    Status request();
    Status reset();

    void confirmed();

    void rollbacking();
    void rollbacked();

private:
    enum
    {
        IDLE_STATE,
        REQUESTING_0,
        ROLLBACKING_0,
        ACKNOWLEDGED,
        REQUESTING_1,
        ROLLBACKING_1
    }state;
};

#endif

