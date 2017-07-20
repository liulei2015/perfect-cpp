#ifndef INCL_SERVICE_H5F33FF02_01E2_4EFE_926F_31B6DB1ACE86
#define INCL_SERVICE_H5F33FF02_01E2_4EFE_926F_31B6DB1ACE86

#include "l0-infra/base/Service.h"
#include "l1-domain/round_situation/RoundSituation.h"
#include "l1-domain/round/Round.h"
#include "l0-infra/base/CelluarState.h"
#include "l1-domain/celluar/Celluar.h"
#include "l1-domain/position/Position.h"
#include "l1-domain/position/PositionType.h"
#include "l1-domain/celluar_machine/const.h"

SERVICE_NS_BEGIN

//{
//    {Celluar(LIVE, Position(0,0)),Celluar(LIVE, Position(0,1)),Celluar(LIVE, Position(0,2))},
//    {Celluar(LIVE, Position(1,0)),Celluar(DIE, Position(1,1)),Celluar(LIVE, Position(1,2))},
//    {Celluar(DIE, Position(2,0)),Celluar(LIVE, Position(2,1)),Celluar(LIVE, Position(2,2))}
//}

struct CelluarMachine
{
	CelluarMachine();
    void registerRound(Celluar& celluar);
    Celluar& getCelluar(const Position& pos);
    Celluar_State getNextState(const Position& pos);

    U32 computeRoundLiveNum(const Position& pos);
protected:
    U32 computeRoundLiveNum(POSITION_TYPE posType, const Position& pos);
private:
    Celluar allCelluar[ROW_NUM][LINE_NUM];
};


SERVICE_NS_END

#endif
