#include "l1-domain/celluar_machine/CelluarMachine.h"
#include "l0-infra/base/Spec.h"
#include "l0-infra/log/log.h"


#include <vector>
#include <unordered_map>

USING_SERVICE_NS



SERVICE_NS_BEGIN

namespace
{
    const U32 Left_Border_Y = 0;
    const U32 Right_Border_Y = ARRAY_NUM - 1;
    const U32 Up_Border_X = 0;
    const U32 Down_Border_X = ARRAY_NUM - 1;

    auto isLeftUp = [](const Position& pos)
            {return (pos.getX() == Up_Border_X && pos.getY() == Left_Border_Y);};

    auto isRightUp = [](const Position& pos)
			{return (pos.getX() == Up_Border_X && pos.getY() == Right_Border_Y);};

    auto isLeftDown = [](const Position& pos)
			{return (pos.getX() == Down_Border_X && pos.getY() == Left_Border_Y);};

    auto isRightDown = [](const Position& pos)
			{return (pos.getX() == Down_Border_X && pos.getY() == Right_Border_Y);};

	auto isOnlyUp = [](const Position& pos)
			{return (pos.getX() == Up_Border_X && pos.getY() > Left_Border_Y && pos.getY() < Right_Border_Y);};

	auto isOnlyDown = [](const Position& pos)
			{return (pos.getX() == Down_Border_X && pos.getY() > Left_Border_Y && pos.getY() < Right_Border_Y);};

	auto isOnlyLeft = [](const Position& pos)
			{return (pos.getY() == Left_Border_Y && pos.getX() > Up_Border_X && pos.getX() < Down_Border_X);};

	auto isOnlyRight = [](const Position& pos)
			{return (pos.getY() == Right_Border_Y && pos.getX() > Up_Border_X && pos.getX() < Down_Border_X);};

	auto isNormal = [](const Position& pos)
			{return (pos.getX() > Up_Border_X && pos.getX() < Down_Border_X &&
					 pos.getY() > Left_Border_Y && pos.getY() < Right_Border_Y);};

	auto makeSurePos = [](const Position& pos)->POSITION_TYPE
		{
			if(isLeftUp(pos))
				return LEFT_UP;
			if(isRightUp(pos))
				return RIGHT_UP;
			if(isLeftDown(pos))
				return LEFT_DOWN;
			if(isRightDown(pos))
				return RIGHT_DOWN;
			if(isOnlyUp(pos))
				return ONLY_UP;
			if(isOnlyDown(pos))
				return ONLY_DOWN;
			if(isOnlyLeft(pos))
				return ONLY_LEFT;
			if(isOnlyRight(pos))
				return ONLY_RIGHT;
			if(isNormal(pos))
				return NORMAL;
		};
}

CelluarMachine::CelluarMachine() :
		allCelluar({
    {Celluar(LIVE),Celluar(LIVE),Celluar(LIVE)},
    {Celluar(LIVE),Celluar(DIE),Celluar(LIVE)},
    {Celluar(DIE),Celluar(LIVE),Celluar(LIVE)}
})
{
	for(U32 i = 0; i < ROW_NUM; ++i)
	{
		for(U32 j = 0; j < LINE_NUM; ++j)
		{
			allCelluar[i][j].getPos().setPos(i,j);
		}
	}
}

void CelluarMachine::registerRound(Celluar& celluar)
{
    INFO_LOG("CelluarMachine::registerRound");
    Position& pos  = celluar.getPos();

    U32 Round_Live_Num = computeRoundLiveNum(pos);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);
}

Celluar& CelluarMachine::getCelluar(const Position& pos)
{
    INFO_LOG("CelluarMachine::getCelluar");
    INFO_LOG("posX : %u, posY : %u", pos.getX(), pos.getY());
    return allCelluar[pos.getX()][pos.getY()];
}

Celluar_State CelluarMachine::getNextState(const Position& pos)
{
    INFO_LOG("CelluarMachine::getNextState");
    INFO_LOG("posX : %u, posY : %u", pos.getX(), pos.getY());

    Celluar& celluar = getCelluar(pos);

    return celluar.getNextState();
}

namespace
{
	struct RetativePosition
	{
		int x;
		int y;
	};

	using RetativePosContainer = std::vector<RetativePosition>;

	struct POS_ROUND
	{
		POSITION_TYPE pos;
		RetativePosContainer roundInfo;
	};

	RetativePosContainer leftUp = {{0,1}, {1,0}, {1,1}};
	RetativePosContainer rightUp = {{0,-1}, {1,0}, {1,-1}};
	RetativePosContainer leftDown = {{-1,0}, {0,1}, {-1,1}};
	RetativePosContainer rightDown = {{0,-1}, {-1,0}, {-1,-1}};

	RetativePosContainer onlyUp = {{0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
	RetativePosContainer onlyDown = {{0,-1}, {0,1}, {-1,-1}, {-1,0}, {-1,1}};
	RetativePosContainer onlyLeft = {{-1,0}, {1,0}, {-1,1}, {0,1}, {1,1}};
	RetativePosContainer onlyRight = {{-1,0}, {1,0}, {-1,-1}, {0,-1}, {1,-1}};

	RetativePosContainer normal = {{-1,-1}, {-1,0}, {-1,1}, {0,-1},
			                       {0,1}, {1,-1}, {1,0}, {1,1}};

	RetativePosContainer roundHelper[] =
	{
		leftUp,
		rightUp,
		leftDown,
		rightDown,
		onlyUp,
		onlyDown,
		onlyLeft,
		onlyRight,
		normal
	};
}

U32 CelluarMachine::computeRoundLiveNum(const Position& pos)
{
	return computeRoundLiveNum(makeSurePos(pos), pos);
}

U32 CelluarMachine::computeRoundLiveNum(POSITION_TYPE posType, const Position& pos)
{
	U32 posX = pos.getX();
	U32 posY = pos.getY();
	U32 liveNum = 0;

	RetativePosContainer& leftUpHelper = roundHelper[posType];

	for (auto iter = leftUpHelper.cbegin(); iter != leftUpHelper.cend(); iter++)
	{
		Celluar side1Celluar = getCelluar(Position(posX+(*iter).x, posY+(*iter).y));
		Celluar_State side1State = side1Celluar.getCurrentState();
		if(side1State == LIVE)
			liveNum++;
	}

	return liveNum;
}

SERVICE_NS_END


