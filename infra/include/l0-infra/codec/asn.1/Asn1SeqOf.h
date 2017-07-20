#ifndef INCL_USI_Asn1SeqOf_2013107101301_H__
#define INCL_USI_Asn1SeqOf_2013107101301_H__

#include "l0-infra/codec/asn.1/Asn1Types.h"
#include "l0-infra/codec/asn.1/Asn1CodecBuf.h"
#include "l0-infra/codec/asn.1/Asn1Status.h"
#include "l0-infra/base/Assertions.h"

ASN1_NS_BEGIN

template <typename T>
struct Asn1SeqOf
{
    Asn1SeqOf() : n(0), elem(0)
    {
    }

    Status alloc(U32 n, Asn1CodecBuf& codecBuf)
    {
        elem = (T*)codecBuf.alloc(n * sizeof(T));
        USI_ASSERT_VALID_PTR_R(elem, ASN1_E_CODEC_BUF);
        this->n = n;

        for(U32 i=0; i<n; i++)
        {
            new (elem+i) T();
        }

        return USI_SUCCESS;
    }

    U32 size() const
    {
        return n;
    }

    T* operator[](U32 index)
    {
        USI_ASSERT_TRUE_NIL(index < n);
        return elem + index;
    }

private:
    U32 n;
    T*  elem;
};

ASN1_NS_END

#endif

