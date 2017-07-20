#ifndef INCL_CPM_H4E90D26C_6023_490A_AB8C_71E3050DC74C
#define INCL_CPM_H4E90D26C_6023_490A_AB8C_71E3050DC74C

#include "l0-infra/base/BaseTypes.h"

const U32 MO_REQ_LEN = 200;

struct MoReq
{
    MoReq(): req({0}){}
    char* getMoReq() {return req;}
    U32 getReqSize() {return strlen(req)+1;}
private:
    char req[MO_REQ_LEN];
};


#endif
