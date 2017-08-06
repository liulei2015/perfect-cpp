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
            if(state == CLOSED)
            {
                state = OPEN;
                return "ready";
            }
            else
                return defaultSpeak();
        }

        string beClosed() const
        {
            if(state == OPEN || state == DANCING)
            {
                state = CLOSED;
                return "closed";
            }
            else
                return defaultSpeak();
        }

        string bePlayed() const
        {
            if(state == OPEN)
            {
                state = DANCING;
                return "doDance";
            }
            else
                return defaultSpeak();
        }

        string beStopped() const
        {
            if(state == DANCING)
            {
                state = OPEN;
                return "stopped";
            }
            else
                return defaultSpeak();
        }

        string defaultSpeak() const
        {
            return "i'll do nothing";
        }

        enum State
        {
            CLOSED,
            OPEN,
            DANCING
        };

    private:
        mutable State state;
    };
}

//跳舞机器人，初始状态closed, open时， say: ready
TEST_F(TestStateMachine, should_say_ready_when_be_opened)
{
    Robot robot;

    ASSERT_TRUE("ready" == robot.beOpened());
}

//其他任何状态，被按open，默认speak: i'll do nothing
TEST_F(TestStateMachine, should_say_default_speak_when_other_state_be_opened)
{
    Robot robot;
    robot.beOpened();

    ASSERT_TRUE("i'll do nothing" == robot.beOpened());
}

//closed状态，被按closed，默认speak: i'll do nothing
TEST_F(TestStateMachine, should_say_default_speak_when_closed_state_be_closed)
{
    Robot robot;

    ASSERT_TRUE("i'll do nothing" == robot.beClosed());
}

//open时，被close, say: closed
TEST_F(TestStateMachine, should_say_closed_when_be_closed)
{
    Robot robot;
    robot.beOpened();

    ASSERT_TRUE("closed" == robot.beClosed());
}

//open时，被按play, say: doDance
TEST_F(TestStateMachine, should_say_doDance_when_be_played)
{
    Robot robot;
    robot.beOpened();

    ASSERT_TRUE("doDance" == robot.bePlayed());
}

//open时，被按stop，默认speak: i'll do nothing
TEST_F(TestStateMachine, should_say_default_speak_when_opened_state_be_stopped)
{
    Robot robot;
    robot.beOpened();

    ASSERT_TRUE("i'll do nothing" == robot.beStopped());
}

//doDance时，被按stop, say: stopped
TEST_F(TestStateMachine, should_say_stopped_when_be_stopped)
{
    Robot robot;
    robot.beOpened();
    robot.bePlayed();

    ASSERT_TRUE("stopped" == robot.beStopped());
}

//doDance时, 被close， say: closed
TEST_F(TestStateMachine, should_say_closed_when_first_be_played_then_be_closed)
{
    Robot robot;
    robot.beOpened();
    robot.bePlayed();

    ASSERT_TRUE("closed" == robot.beClosed());
}

//doDance时，被按open，默认speak: i'll do nothing
TEST_F(TestStateMachine, should_say_default_speak_when_doDance_state_be_opened)
{
    Robot robot;
    robot.beOpened();
    robot.bePlayed();

    ASSERT_TRUE("i'll do nothing" == robot.beOpened());
}

UTESTING_NS_END



