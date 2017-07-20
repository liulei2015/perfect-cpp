#ifndef INCL_USI_H0B2830C8_4B3B_442D_B64C_73AC632A27F5
#define INCL_USI_H0B2830C8_4B3B_442D_B64C_73AC632A27F5

#include "l0-infra/base/usi.h"
#include "l0-infra/base/static_assert.h"

USI_NS_BEGIN

///////////////////////////////////////////////////////////////////////
template <typename FROM, typename TO>
struct StructWrapper : protected FROM
{
    static const TO& by(const FROM& from)
    {
        STATIC_ASSERT(sizeof(FROM) == sizeof(TO));

        return (const TO&)from;
    }

    static TO& by(FROM& from)
    {
        return (TO&)from;
    }
};

///////////////////////////////////////////////////////////////////////
#define STRUCT_WRAPPER(to, from) struct to : StructWrapper<from, to>

USI_NS_END

#endif
