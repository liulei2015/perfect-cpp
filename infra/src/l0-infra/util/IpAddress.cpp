#include <l0-infra/util/IpAddress.h>
#include <l0-infra/util/VerifyAddr.h>
#include "l0-infra/util/BitRateConverter.h"
#include "l0-infra/base/Assertions.h"
#include <arpa/inet.h>      //在NetMacro之上包含
#include "l0-infra/util/NetMacro.h"
#include "l0-infra/codec/Asn1Typedef.h"

WORD32 IpAddress::getIpV4() const
{
    WORD32 ipV4;
    ::memcpy(&ipV4, getStreamBuf(), sizeof(WORD32));
    return ntohl(ipV4);
}

void IpAddress::updateIpv4(const WORD32 addr)
{
	WORD32 ipV4 = htonl(addr);
	updateStream((BYTE *)(&ipV4), 4);
}

//////////////////////////////////////////////////////////////////////////
void IpAddress::updateBy(const Asn1DynamicBitString& addr)
{
    BYTE numocts = BitRateConverter::getCeilingBitsToByte(addr.nbits);
    USI_ASSERT_TRUE_VOID(verifyAddr(addr.data, numocts));

    updateStream(addr.data, numocts);
}

//////////////////////////////////////////////////////////////////////////
void IpAddress::assignTo(Asn1DynamicBitString& addr) const
{
    addr.nbits = len * 8;
    memcpy(addr.data, buffer, len);
}

void IpAddress::updateBy(const TTransAddress& addr)
{
//    USI_ASSERT_TRUE_VOID(verifyAddr(addr.aucTranAddr, addr.ucAddrLen));
//
//    updateStream(addr.aucTranAddr, addr.ucAddrLen);
}

void IpAddress::assignTo(BYTE* data, BYTE& len) const
{
    copyTo(data, len);
}

