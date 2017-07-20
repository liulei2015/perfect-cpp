#ifndef INCL_CODER_TL_UT_H6D1699F9_B89E_429B_990E_08DE28DCC3A3
#define INCL_CODER_TL_UT_H6D1699F9_B89E_429B_990E_08DE28DCC3A3

#include "l0-infra/base/usi.h"
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::vector;


struct RRU;

USI_NS_BEGIN

template<class Type>
struct StringWrapper
{
    vector<string> split(string str, string separator);

    Type string2Num(const string& str)
    {
        std::istringstream iss(str);
        Type num;
        iss >> num;
        return num;
    }
};

template<class Type>
vector<string> StringWrapper<Type>::split(string str, string separator)
{
    vector<string> result;
    size_t cutAt;
    while ((cutAt = str.find_first_of(separator)) != str.npos)
    {
        if (cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if (str.length() > 0)
    {
        result.push_back(str);
    }
    return result;
}

USI_NS_END


#endif
