#ifndef INCL_USI_COMMON_IP_ADDRESS_H
#define INCL_USI_COMMON_IP_ADDRESS_H

#include "l0-infra/base/StreamBuffer.h"

struct TTransAddress;
struct TTransLayerAddr;
struct Asn1DynamicBitString;

const BYTE MAX_IP_ADDRESS_LEN = 20;

struct IpAddress : StreamBuffer<MAX_IP_ADDRESS_LEN>
{
    WORD32 getIpV4() const;

    void updateIpv4(const WORD32 addr);

    void updateBy(const Asn1DynamicBitString& addr);
    void updateBy(const TTransAddress& addr);

    void assignTo(Asn1DynamicBitString& addr) const;
    void assignTo(BYTE* data, BYTE& len) const;
};

#endif

