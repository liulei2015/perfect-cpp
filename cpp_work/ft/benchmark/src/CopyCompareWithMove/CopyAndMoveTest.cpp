#include <celero/Celero.h>
#include <celero/Benchmark.h>
#include "util/copy_and_move/Moveable.h"
#include "utest.h"

USING_UTESTING_NS

Moveable getMoveable()
{
    Moveable tmp = Moveable();
    return tmp;
}

int testMove()
{
    Moveable a(getMoveable());
    return 0;
}

int testCopy()
{
    Moveable init;
    Moveable a(init);
    return 0;
}

BASELINE(CopyAndMove, Move, 10, 10000)
{
    celero::DoNotOptimizeAway(testMove());
}

BENCHMARK(CopyAndMove, Copy, 10, 10000)
{
    celero::DoNotOptimizeAway(testCopy());
}
