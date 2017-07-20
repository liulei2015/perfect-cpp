#ifndef INCL_CODER_TL_UT_H30FBE7AF_3F4E_4378_8773_16DCD7B93F37
#define INCL_CODER_TL_UT_H30FBE7AF_3F4E_4378_8773_16DCD7B93F37

#include "utest.h"
#include <string.h>

UTESTING_NS_BEGIN

class HugeMem
{
public:
    HugeMem(int size): sz(size > 0 ? size:1)
    {
        c = new int[size];
    }
    ~HugeMem() { delete [] c; }
    HugeMem(HugeMem && hm): sz(hm.sz), c(hm.c)
    {
        hm.c = nullptr;
    }

    HugeMem(const HugeMem & hm): sz(hm.sz > 0 ? hm.sz:1)
    {
        c = new int[sz];
        memcpy(c, hm.c, sz);
    }

    int * c;
    int sz;
};

class Moveable
{
public:
    const int HUGEMEM_SIZE = 1024;
    Moveable():i(new int(3)), h(HUGEMEM_SIZE)
    {}
    ~Moveable() {delete i;}
    Moveable(Moveable && m):i(m.i), h(std::move(m.h))
    {
        m.i = nullptr;
    }

    Moveable(const Moveable & m):i(new int(*m.i)), h(m.h)
    {}

    int* i;
    HugeMem h;
};

UTESTING_NS_END

#endif
