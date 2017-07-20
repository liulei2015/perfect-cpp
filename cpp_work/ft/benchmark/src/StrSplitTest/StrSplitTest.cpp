
#include <celero/Celero.h>
#include <celero/Benchmark.h>

#include "l0-infra/string-wrapper/StringWrapper.h"
#include <regex>

USING_USI_NS

//prepare add new folder for benchmark
//std::random_device RandomDevice;
//std::uniform_int_distribution<int> UniformDistribution(0, 1024);

StringWrapper<float> strWrapper;
string targetStr = "1.1, 1.2, 1.3, 1.4, 1.5";

string::const_iterator start = targetStr.begin();
string::const_iterator end = targetStr.end();

std::regex pattern("\\d+\\.\\d+");
std::smatch match;

int reConvert(const string& str)
{
    while(regex_search(start, end, match, pattern))
    {
        string msg(match[0].first, match[0].second);
//        std::cout << msg << std::endl;
        start = match[0].second;
    }
    return 0;
}

BASELINE(DemoSimple, Baseline, 10, 10000)
{
    celero::DoNotOptimizeAway(strWrapper.split(targetStr, ","));
}

BENCHMARK(DemoSimple, Regex, 10, 10000)
{
    celero::DoNotOptimizeAway(reConvert(targetStr));
}

