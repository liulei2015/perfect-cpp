/*
 * InstanceId.h
 *
 * Created on: Apr 21, 2013
 *     author: Darwin Yuan
 *
 * Copyright 2013 ThoughtWorks, All Rights Reserved.
 *
 */ 

#ifndef INCL_USI_InstanceId_20131123092850_H__
#define INCL_USI_InstanceId_20131123092850_H__

#include "l0-infra/base/BaseTypes.h"
#include "l0-infra/base/Status.h"

//
// According to performance profiling, 
// inline everything of this class.
//
struct InstanceId
{
    enum
    {
        INVALID_IID = 0xFFFFFFFF
    };

    //////////////////////////////////////////////////////////////////////////
    InstanceId()
    {
        u.value = INVALID_IID;
    }

    //////////////////////////////////////////////////////////////////////////
    explicit InstanceId(const WORD32 value)
    {
        u.value = value;
    }

    //////////////////////////////////////////////////////////////////////////
    explicit InstanceId(void* p)
    {
        u.p = p;
    }

    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    explicit InstanceId(T* p)
    {
        u.p = (void*)p;
    }

    //////////////////////////////////////////////////////////////////////////
    InstanceId(const InstanceId& rhs)
    {
        u.p = rhs.u.p;
    }

    //////////////////////////////////////////////////////////////////////////
    operator WORD32() const
    {
        return u.value;
    }

    //////////////////////////////////////////////////////////////////////////
    bool operator==(const InstanceId& rhs) const
    {
        return rhs.u.p == u.p;
    }

    //////////////////////////////////////////////////////////////////////////
    bool operator!=(const InstanceId& rhs) const
    {
        return !(*this == rhs);
    }

    //////////////////////////////////////////////////////////////////////////
    InstanceId& operator=(const InstanceId& rhs)
    {
        u.p = rhs.u.p;

        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    bool isValid() const
    {
        return u.value != INVALID_IID && u.value != USI_INVALID_WORD16;
    }

    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    T* toPointer() const
    {
        return isValid() ? (T*)(u.p) : 0;
    }

private:
    union
    {
        WORD32 value;
        void*  p;
    }u;
};

#endif /* INSTANCEID_H_ */

