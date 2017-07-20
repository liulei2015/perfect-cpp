#ifndef ASN1_MEMORY
#define ASN1_MEMORY

#include "Asn1Typedef.h"

#define ASN1_SYSTEM_MEM_SIZE    (ASN1UINT)(2000*1024)

/*根据BS8912情况修改用户面OP名称*/
#if ((_LOGIC_BOARD == _LOGIC_BS14TRA) || (_LOGIC_BOARD == _LOGIC_B33TRA))	 
#define ASN1_USER_MEM_SIZE      (ASN1UINT)(2000*1024)
#else
#define ASN1_USER_MEM_SIZE      (ASN1UINT)(4000*1024)
#endif

typedef struct tagAsn1MemHandler
{
    ASN1OCTET   *buff;
    ASN1OCTET   *head;
    ASN1UINT    freeSize;
}Asn1MemHandler;

#ifdef __cplusplus
extern "C" {
#endif

ASN1VOID Asn1InitMemory(Asn1MemHandler *memHandler, ASN1OCTET *buff, ASN1UINT size);
ASN1VOID Asn1InitSysMemory();
ASN1VOID Asn1InitUserMemory();
ASN1ANY Asn1Malloc(Asn1MemHandler *memHandler, ASN1UINT size);
ASN1ANY Asn1SysMalloc(ASN1UINT size);
ASN1ANY Asn1UserMalloc(ASN1UINT size);
ASN1ANY Asn1Mborrow(ASN1UINT size, ASN1ANY data);
ASN1UINT Asn1GetSysMemoryFreeSize();
ASN1UINT Asn1GetUserMemoryFreeSize();

#ifdef __cplusplus
}
#endif

#endif
