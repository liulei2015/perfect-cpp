#include "l0-infra/base/SharedObject.h"
#include "l0-infra/log/UsfLog.h"

SharedObject::SharedObject() : count(0)
{
}

SharedObject::~SharedObject()
{
}

void SharedObject::addRef()
{
    count++;
    //DBG_LOG("Shared Object[%x] addRef[%d]", this, count);
}

unsigned int SharedObject::getRefCount() const
{
    return count;
}

bool SharedObject::onlyThisRef() const
{
    return count == 1;
}

void SharedObject::subRef()
{
    if(count > 0)
    {
        count--;
        //DBG_LOG("Shared Object[%x] Release[%d]", this, count);
    }

    if(count == 0) delete this;
}
