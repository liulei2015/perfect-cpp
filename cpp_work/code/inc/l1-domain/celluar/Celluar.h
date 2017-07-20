#ifndef INCL_SERVICE_HC1EEEB07_A6E2_49CB_B8F7_F2C8AF92DED6
#define INCL_SERVICE_HC1EEEB07_A6E2_49CB_B8F7_F2C8AF92DED6

#include "l0-infra/base/Service.h"
#include "l0-infra/base/CelluarState.h"
#include "l1-domain/round/Round.h"
#include "l1-domain/position/Position.h"

SERVICE_NS_BEGIN

struct Celluar
{
	Celluar(): currentState(LIVE)
			 , nextState(INVALID_CELLUAR_STATE) {}
    Celluar(Celluar_State initState)
            : currentState(initState)
            , nextState(INVALID_CELLUAR_STATE) {}

    Celluar(Celluar_State initState, const Position& pos)
        : currentState(initState)
        , nextState(INVALID_CELLUAR_STATE)
        , position(pos) {}

    Celluar_State getCurrentState() const;
    Celluar_State getNextState();

    void setRound(const Round& round);
    Position& getPos() {return position;}
private:
    Celluar_State currentState;
    Celluar_State nextState;
    Position position;
    Round round;
};


SERVICE_NS_END

#endif
