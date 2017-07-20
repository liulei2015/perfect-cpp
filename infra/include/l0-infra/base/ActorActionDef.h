#ifndef INCL_USI_ActorActionDef_20140210151611_H__
#define INCL_USI_ActorActionDef_20140210151611_H__

#include "l0-infra/dci/Role.h"
#include "l0-infra/trans-dsl/action/SyncAction.h"
#include "l0-infra/trans-dsl/action/Actor.h"
#include "l0-infra/trans-dsl/action/RoleBasedAsyncAction.h"

#define DEF_SIMPLE_SYNC_ACTOR_ACTION(p_name, p_actor)      \
struct p_actor;                                            \
DEFINE_ROLE(BASE_ACTION_NAME(p_name))                            \
{                                                          \
    Status exec(const TransactionInfo&);                   \
                                                           \
private:                                                   \
    USE_ACTOR(p_actor);                                    \
};                                                         \
DEF_ACTOR_BASED_ACTION(p_actor, p_name)

//////////////////////////////////////////////////////////////////////////
#define DEF_SIMPLE_ROLE_ACTOR_ACTION(p_name, p_actor)      \
struct p_actor;                                            \
struct BASE_ACTION_NAME(p_name) : RoleBasedAsyncAction     \
{                                                          \
    Status exec(const TransactionInfo&);                   \
private:                                                   \
    USE_ACTOR(p_actor);                                    \
};                                                         \
    DEF_ACTOR_BASED_ACTION(p_actor, p_name)

#endif

