#ifndef INCL_SERVICE_H886B8D7B_8B9D_4F5E_93E5_D37D8DA46213
#define INCL_SERVICE_H886B8D7B_8B9D_4F5E_93E5_D37D8DA46213

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Service.h"

SERVICE_NS_BEGIN


struct Position
{
    Position() : x(0), y(0) {}

    Position(U32 posX, U32 posY)
        : x(posX)
        , y(posY) {}

    U32 getX() const {return x;}
    U32 getY() const {return y;}
    void setPos(U32 x_, U32 y_) {x = x_; y = y_;}

private:
    U32 x;
    U32 y;
};


SERVICE_NS_END

#endif
