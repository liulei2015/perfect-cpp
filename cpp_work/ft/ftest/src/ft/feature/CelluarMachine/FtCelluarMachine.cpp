#include "fw/ftest.h"
#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Keywords.h"
#include "l0-infra/log/log.h"
#include "l1-domain/round_situation/RoundSituation.h"
#include "l1-domain/round/Round.h"
#include "l0-infra/base/CelluarState.h"
#include "l1-domain/celluar/Celluar.h"
#include "l1-domain/position/Position.h"
#include "l0-infra/base/Spec.h"
#include "l1-domain/celluar_machine/CelluarMachine.h"

#include <array>
#include <iostream>



using namespace std;

USING_SERVICE_NS

//extern Celluar allCelluar[3][3];

FTESTING_NS_BEGIN

struct TestCelluarMachine : testing::Test
{
protected:
    virtual void doSetUp()
    {
    }

    virtual void doTearDown()
    {
    }

    OVERRIDE(void SetUp()){doSetUp();}
    OVERRIDE(void TearDown()){doTearDown();}
};

//////////////////////////////////////////////////////////////////////////////////////////
//
TEST_F(TestCelluarMachine, live_to_die_when_round_0)
{
    const U32 Round_Live_Num = 0;
    const Celluar_State Expected_Next_State = DIE;

    Celluar celluar(LIVE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, live_to_die_when_round_1)
{
    const U32 Round_Live_Num = 1;
    const Celluar_State Expected_Next_State = DIE;

    Celluar celluar(LIVE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, live_to_live_when_round_2)
{
    const U32 Round_Live_Num = 2;
    const Celluar_State Expected_Next_State = LIVE;

    Celluar celluar(LIVE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, live_to_live_when_round_3)
{
    const U32 Round_Live_Num = 3;
    const Celluar_State Expected_Next_State = LIVE;

    Celluar celluar(LIVE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, live_to_die_when_round_bigger_than_3_and_real_4)
{
    const U32 Round_Live_Num = 4;
    const Celluar_State Expected_Next_State = DIE;

    Celluar celluar(LIVE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}

//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, die_to_live_when_round_3)
{
    const U32 Round_Live_Num = 3;
    const Celluar_State Expected_Next_State = LIVE;

    Celluar celluar(DIE);
    RoundSituation situation(Round_Live_Num);
    Round round(situation);
    celluar.setRound(round);

    ASSERT_TRUE( Expected_Next_State == celluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
namespace
{

    char Expected_Show_Array [][ARRAY_NUM] =
    {
            {'$', '$', '$'},
            {'$', ' ', '$'},
            {' ', '$', '$'}
    };

    U32 u32Array [ARRAY_NUM][ARRAY_NUM] =
    {
            {1,1,1},
            {1,0,1},
            {0,1,1}
    };

    void printArray(U32** uArray)
    {
        printf("%c", '$');
    }

    void printExpected_Show_Array()
    {
        for(auto p = begin(Expected_Show_Array); p != end(Expected_Show_Array); ++p)
        {
            for(auto q = begin(*p); q != end(*p); ++q)
                cout << *q << ' ';
            cout << endl;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////

TEST_F(TestCelluarMachine, show_1)
{
    INFO_LOG("TestCelluarMachine, show_1");
    printExpected_Show_Array();
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_left_up_round)
{
    const Celluar_State Expected_Next_State = LIVE;

    CelluarMachine celluarMachine;

    Celluar& testCelluar = celluarMachine.getCelluar(Position(0,0));

    celluarMachine.registerRound(testCelluar);

    ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_right_up_round)
{
    const Celluar_State Expected_Next_State = LIVE;

    CelluarMachine celluarMachine;

    Celluar& testCelluar = celluarMachine.getCelluar(Position(0, ARRAY_NUM-1));

    celluarMachine.registerRound(testCelluar);

    ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_left_down_round)
{
    const Celluar_State Expected_Next_State = DIE;

    CelluarMachine celluarMachine;

    Celluar& testCelluar = celluarMachine.getCelluar(Position(ARRAY_NUM-1, 0));

    celluarMachine.registerRound(testCelluar);

    ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_right_down_round)
{
	const Celluar_State Expected_Next_State = LIVE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(ARRAY_NUM-1, ARRAY_NUM-1));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_only_up_round)
{
	const Celluar_State Expected_Next_State = DIE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(0, 1));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_only_down_round)
{
	const Celluar_State Expected_Next_State = LIVE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(2, 1));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_only_left_round)
{
	const Celluar_State Expected_Next_State = LIVE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(1, 0));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_only_right_round)
{
	const Celluar_State Expected_Next_State = DIE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(1, 2));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}

TEST_F(TestCelluarMachine, celluar_machine_help_get_celluar_pos_normal_round)
{
	const Celluar_State Expected_Next_State = DIE;

	CelluarMachine celluarMachine;

	Celluar& testCelluar = celluarMachine.getCelluar(Position(1, 1));

	celluarMachine.registerRound(testCelluar);

	ASSERT_TRUE( Expected_Next_State == testCelluar.getNextState() );
}




FTESTING_NS_END


