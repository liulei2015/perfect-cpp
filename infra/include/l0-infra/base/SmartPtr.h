#ifndef INCL_SmartPtr_201389203017_H
#define INCL_SmartPtr_201389203017_H

#include "l0-infra/dci/Role.h"
#include "l0-infra/base/SharedObject.h"

template <typename OBJ>
struct SmartPtr
{
    SmartPtr() : p(0) {}
    SmartPtr(const OBJ* p) : p(const_cast<OBJ*>(p)) 
    {
        addRef();
    }

    SmartPtr(const SmartPtr& rhs) 
        : p(rhs.p)
    {
        addRef();
    }

    SmartPtr& operator=(const SmartPtr& rhs) 
    {
        release();

        p = rhs.p;
        addRef();

        return *this;
    }

    ~SmartPtr()
    {
        release();
    }

    bool operator==(const SmartPtr& rhs) const
    {
        return rhs.p == p;
    }

    bool operator!=(const SmartPtr& rhs) const
    {
        return !(*this == rhs);
    }

    OBJ* operator->()
    {
        return p;
    }

    const OBJ* operator->() const
    {
        return p;
    }

    bool isNull() const
    {
        return p == 0;
    }

    OBJ* raw() 
    {
        return p;
    }

    const OBJ* raw() const
    {
        return p;
    }

    OBJ& operator*()
    {
        return *p;
    }

    const OBJ& operator*() const
    {
        return *p;
    }

    void release()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).subRef();
            p = 0;
        }
    }

private:
    void addRef()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).addRef();
        }
    }

private:
    OBJ* p;
};

#endif
