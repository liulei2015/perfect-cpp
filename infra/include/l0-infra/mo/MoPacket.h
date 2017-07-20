/*
 * MoDataParser.h
 *
 *  Created on: 2016年9月6日
 *      Author: szdev
 */

#ifndef HF2E59B5D_A9D6_4EF4_B901_801486A5044F
#define HF2E59B5D_A9D6_4EF4_B901_801486A5044F

typedef void* JsonData;

struct MoPacket
{
    MoPacket();
    ~MoPacket();

    bool parse(const char* sourceData);

    bool pushDataInResult(const char* newData);

    JsonData getResult() const;

    void dump();

private:
    JsonData data;
};



#endif /* HF2E59B5D_A9D6_4EF4_B901_801486A5044F */
