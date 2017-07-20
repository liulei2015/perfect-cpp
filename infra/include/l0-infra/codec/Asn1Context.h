#ifndef ASN1_CONTEXT
#define ASN1_CONTEXT

#include "Asn1Error.h"
#include "Asn1Memory.h"
#include "LteCodecOffsetInterface.h"

#define LOG_ERROR(ctxt, errCode)    Asn1LogError((ctxt), (errCode), __LINE__, __FILE__)
#define CHECK_RESULT(ctxt, status)    \
do { \
    if (ASN1_OK != (status)) \
    { \
        return LOG_ERROR((ctxt), (status)); \
    } \
}while(0)
#define CHECK_RESULT_AND_RETURN(ctxt, status) \
do { \
    if (ASN1_OK != (status)) \
    { \
        LOG_ERROR((ctxt), (status)); \
    } \
    return (status); \
}while(0)
#define DECODE_STATUS(ctxt)     Asn1CurrentErrorCode((ctxt)->errorInfo)

#define ASN1_DEFAULT_CODE_BULL_LEN  (ASN1UINT)(32*1024)
#if (_LOGIC_BOARD == _LOGIC_CCE1) || (_LOGIC_BOARD == _LOGIC_CCE)
    #define ASN1_X2AP_SETUP_UPDATE_CODE_BUFF_LEN (ASN1UINT)(96*1024)
#else
    #define ASN1_X2AP_SETUP_UPDATE_CODE_BUFF_LEN (ASN1UINT)(32*1024)
#endif
typedef struct tagAsn1CodeBuff
{
    ASN1OCTET   *data;       // 数据指针
    ASN1UINT    byteIndex;   // 字节索引
    ASN1UINT    size;        // 数据大小
    ASN1USHORT  bitOffset;   // 位置偏移
    ASN1BOOL    dynamic;     // 是否动态
    ASN1BOOL    aligned;     // 对齐方式
}Asn1CodeBuff;

typedef struct tagAsn1DecodeBuff
{
    ASN1BOOL        dynamic;      // 是否动态内存
    Asn1MemHandler  buffHandler;  // 内存指针
}Asn1DecodeBuff;

typedef struct tagAsn1SizeConstraint
{
    ASN1BOOL                        extended;  //扩展
    ASN1UINT                        lower;     //范围下限
    ASN1UINT                        upper;     //范围上限
    struct tagAsn1SizeConstraint    *next;     //下一个的指针
}Asn1SizeConstraint;

typedef struct Asn1Ctxt
{
    Asn1CodeBuff        codeBuff;
    Asn1DecodeBuff      decodeBuff;
    Asn1ErrorInfo       *errorInfo;
    Asn1SizeConstraint  *sizeConstraint;
#if defined(ZY_TEST)
    ASN1ANY             *criticalityInfo;
#else
    ASN1ANY             criticalityInfo;
#endif
    CODEC_OFFSET_DATASTRUCT *pIE_OFFSETs;
}Asn1Ctxt;


#ifdef __cplusplus
extern "C" {
#endif

ASN1STATUS Asn1InitCodeBuff(Asn1Ctxt *ctxt, ASN1OCTET *dataBuff, ASN1UINT buffLen, ASN1BOOL aligned);
ASN1STATUS Asn1InitEncodeBuff(Asn1Ctxt *ctxt, ASN1OCTET *dataBuff, ASN1UINT buffLen, ASN1BOOL aligned);
ASN1STATUS Asn1InitEncodeCtxt(Asn1Ctxt *ctxt, ASN1OCTET *dataBuff, ASN1UINT buffLen, ASN1BOOL aligned);
ASN1STATUS Asn1InitDeodeBuff(Asn1Ctxt *ctxt, ASN1OCTET *decodeBuff, ASN1UINT deBuffLen);
ASN1STATUS Asn1InitDecodeCtxt(Asn1Ctxt *ctxt, ASN1OCTET *dataBuff, ASN1UINT buffLen, ASN1OCTET *decodeBuff, ASN1UINT deBuffLen, ASN1BOOL aligned);
ASN1ANY Asn1DecodeBuffMalloc(Asn1Ctxt *ctxt, ASN1UINT size);
// zy mod
//ASN1UINT   Asn1GetCodeLength(Asn1Ctxt *ctxt);
#define  ALLOC_ASN1ELEM(ctxt,type) Asn1DecodeBuffMalloc(ctxt,sizeof(type))
#define Asn1GetCodeLength(ctxt)  (((ctxt)->codeBuff.bitOffset == 8) ? (ctxt)->codeBuff.byteIndex : ((ctxt)->codeBuff.byteIndex + 1))
ASN1OCTET* Asn1GetCode(Asn1Ctxt *ctxt, ASN1UINT *length);
ASN1STATUS Asn1SetSizeConstraint(Asn1Ctxt *ctxt, Asn1SizeConstraint *sizeConstraint);
Asn1SizeConstraint *Asn1GetSizeConstraintByValue(Asn1SizeConstraint *constraint, ASN1UINT value);
Asn1SizeConstraint *Asn1GetSizeConstraintByExtensionMarker(Asn1SizeConstraint *constraint, ASN1BOOL extended);
ASN1BOOL Asn1IsSizeConstraintExtendable(Asn1Ctxt *ctxt);
ASN1VOID Asn1ClearSizeConstraint(Asn1Ctxt *ctxt);
//ASN1VOID   Asn1CopyCodeBuff(Asn1Ctxt *targetCtxt, Asn1Ctxt *sourceCtxt);
#define Asn1CopyCodeBuff(targetCtxt, sourceCtxt)\
do\
{\
    (targetCtxt)->codeBuff        = (sourceCtxt)->codeBuff;\
    (targetCtxt)->sizeConstraint  = (sourceCtxt)->sizeConstraint;\
}while(0)\


//ASN1UINT   Asn1GetBitOffset(Asn1Ctxt *ctxt);
#define   Asn1GetBitOffset(ctxt)  ((ctxt)->codeBuff.byteIndex * 8 + 8 - (ctxt)->codeBuff.bitOffset)
ASN1UINT Asn1SetBitOffset(Asn1Ctxt *ctxt, ASN1UINT bitOffset);
ASN1STATUS Asn1LogError(Asn1Ctxt *ctxt, ASN1STATUS errorCode, ASN1UINT lineNo, Asn1ConstCharPtr fileName);
ASN1STATUS Asn1CtxtStatus(Asn1Ctxt *ctxt);
ASN1VOID Asn1StoreErrorAndContinue(Asn1Ctxt *ctxt);
ASN1VOID Asn1InitCriticalityInfo(Asn1Ctxt *ctxt, ASN1ANY criticalityInfo);
ASN1VOID Asn1CopyContext(Asn1Ctxt* pdest, Asn1Ctxt* psrc);

#ifdef __cplusplus
}
#endif


#endif
