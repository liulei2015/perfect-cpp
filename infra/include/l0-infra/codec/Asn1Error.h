#ifndef ASN1_ERROR
#define ASN1_ERROR

#include "Asn1Typedef.h"

typedef struct tagAsn1ErrorTable
{
    ASN1USHORT          errorCode;
    Asn1ConstCharPtr    errorText;
}Asn1ErrorTable;

typedef struct tagAsn1ErrorPoint
{
    ASN1UINT            lineNo;
    Asn1ConstCharPtr    fileName;
}Asn1ErrorPoint;

#define ASN1_MAX_ERR_STACK_DEEP (ASN1BYTE)8
typedef struct tagAsn1ErrorInfo
{
    ASN1STATUS              errorCode;
    ASN1BYTE                stackDeep;
    Asn1ErrorPoint          stack[ASN1_MAX_ERR_STACK_DEEP];
    struct tagAsn1ErrorInfo *lastErrorInfo;
}Asn1ErrorInfo;

#define ASN1_MAX_ERROR_INFO (ASN1USHORT)10
typedef struct tagAsn1ErrorData
{
    ASN1USHORT      currentIndex;
    ASN1USHORT      nextIndex;
    Asn1ErrorInfo   errorInfo[ASN1_MAX_ERROR_INFO];
}Asn1ErrorData;

#ifdef __cplusplus
extern "C" {
#endif
Asn1ConstCharPtr Asn1GetErrorText(ASN1UINT errorCode);
Asn1ErrorInfo *Asn1NewErrorInfo();
ASN1STATUS Asn1PushErrorPoint(Asn1ErrorInfo *errorInfo, ASN1STATUS errorCode, ASN1UINT lineNo, Asn1ConstCharPtr fileName);
ASN1VOID Asn1PrintErrorInfo(Asn1ErrorInfo *errorInfo);
ASN1VOID Asn1PrintCurrentErrorInfo();
ASN1VOID Asn1PrintAllErrorInfo();
ASN1VOID Asn1PrintErrorInfoList(Asn1ErrorInfo *errorInfo);
ASN1STATUS Asn1CurrentErrorCode(Asn1ErrorInfo *errorInfo);

#ifdef __cplusplus
}
#endif


#endif

