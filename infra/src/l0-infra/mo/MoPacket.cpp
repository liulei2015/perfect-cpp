#include "l0-infra/mo/MoPacket.h"
#include "json.hpp"

using json = nlohmann::json;

MoPacket::MoPacket()
{
    data = NULL;
}


MoPacket::~MoPacket()
{
    if(data != NULL)
    {
        json& sourceJson = *((json*)data);
        sourceJson.clear();
        data = NULL;
    }
}

bool MoPacket::parse(const char* sourceData)
{
    static json j;
    j = json::parse(sourceData);
    if(j== nullptr || j.is_null())
        return false;

    data = &j;
    return true;
}

bool pushDataTo(json *destData, const char* newData)
{
    static json newJson;
    newJson = json::parse(newData);
    json& sourceJson = *((json*)destData);

    if(newJson.is_null() || newJson.is_null() || destData == NULL)
        return false;

    json& sourceResult = sourceJson["result"];
    json& newResult = newJson["result"];

    if(newResult.is_null() || sourceResult.is_null())
           return false;


    for( json::iterator it = newResult.begin(); it != newResult.end(); ++it)
    {
        sourceResult[it.key()] = it.value();
    }

    return true;
}

bool MoPacket::pushDataInResult(const char* newData)
{
    return pushDataTo((json*)data, newData);
}

JsonData MoPacket::getResult() const
{
    json& sourceJson = *((json*)data);
    if(sourceJson== nullptr)
        return nullptr;

    json& sourceResult = sourceJson["result"];

   // std::cout<< sourceResult["ENBFunction.Non_Public"] << std::endl;

    return &sourceResult;
}

 void MoPacket::dump()
{
    json& sourceJson = *((json*)data);
    std::cout << sourceJson << std::endl;
}
