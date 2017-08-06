#include "utest.h"
#include <string>

using std::string;


UTESTING_NS_BEGIN

struct TestStateMachine : testing::Test
{

};

namespace
{

    struct Robot
    {
        Robot() : state(CLOSED) {}
        string beOpened() const
        {
            return "ready";
        }

        string beClosed() const
        {
            return "closed";
        }

        enum State
        {
            CLOSED,
            OPEN,
            DANCING
        };

    private:
        int state;
    };
}

//跳舞机器人，初始状态closed, open时， say: ready
TEST_F(TestStateMachine, should_say_ready_when_be_opened)
{
    Robot robot;

    ASSERT_TRUE("ready" == robot.beOpened());
}

//open时，被close, say: closed
TEST_F(TestStateMachine, should_say_closed_when_be_closed)
{
    Robot robot;
    robot.beOpened();

    ASSERT_TRUE("closed" == robot.beClosed());
}

//open时，被按play, say: closed




UTESTING_NS_END



