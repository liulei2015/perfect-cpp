#include "l0-infra/codec/ap/ProtocolIesDecoder.h"
#include "l0-infra/codec/ap/trans/ApContainerDefs_T.h"

namespace
{
    ProtoIeItem* findIe(U16 id, ProtoIeItem* ies, U32 num)
    {
        for(U32 i=0; i<num; i++)
        {
            if(ies[i].matches(id))
            {
                return ies + i;
            }
        }

        return 0;
    }

    Status decodeSingleIe(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num, U16 order = 0)
    {
        AP_ProtocolIE_SingleContainer container;
        USI_ASSERT_SUCC_CALL(ASN1_CODEC(AP_ProtocolIE_SingleContainer)::decode(context, container));
        ProtoIeItem* ie = findIe(container.protocolIE_ID, ies, num);
        if(ie != 0)
        {
            USI_ASSERT_SUCC_CALL(ie->onRecv(context, order, container));
        }

        return USI_SUCCESS;
    }
}

Status AP_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num)
{
    U16 n = 0;
    USI_ASSERT_SUCC_CALL(context.getDecoder().decodeSeqOfN(Asn1Constraint<U16>(false, 0, maxProtocolIEs), n));

    for(U16 i=0; i< n; i++)
    {
        USI_ASSERT_SUCC_CALL(decodeSingleIe(context, ies, num, i));
    }

    return USI_SUCCESS;
}

Status AP_single_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num)
{
    USI_ASSERT_SUCC_CALL(decodeSingleIe(context, ies, num));

    return USI_SUCCESS;
}

Status AP_ext_container_decode(ASN1_NS::Asn1DecodingContext& context, ProtoIeItem* ies, U32 num)
{
    return AP_container_decode(context, ies, num);
}

