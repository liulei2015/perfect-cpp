#ifndef INCL_USI_Asn1OptionalIe_2013104153944_H__
#define INCL_USI_Asn1OptionalIe_2013104153944_H__

#include "l0-infra/codec/asn.1/asn1.h"
#include "Asn1Types.h"

ASN1_NS_BEGIN

template <typename T>
struct Asn1OptionalIe
{
    Asn1OptionalIe() : present(false)
    {
    }

    void forceEffective()
    {
        present = true;
    }

    bool isPresent() const
    {
        return present;
    }

    U32 getOffsetOfPresent() const
    {
        return (U8*)&present - (U8*)this;
    }

    T& operator*()
    {
        return getRef();
    }

    const T& operator*() const
    {
        return getRef();
    }

    const T* operator->() const
    {
        return getObject();
    }

    const T* getObject() const
    {
        return &ie;
    }

    T& getRef() const
    {
        return ie;
    }

private:
    mutable T ie;
    bool present;

};

ASN1_NS_END

#endif

