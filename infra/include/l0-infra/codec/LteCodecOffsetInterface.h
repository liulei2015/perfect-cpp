#ifndef __LTECODECOFFSETINTERFACE_H
#define __LTECODECOFFSETINTERFACE_H


#ifdef __cplusplus
extern "C" {
#endif


#ifndef __enum_IE_36331_OFFSET
#define __enum_IE_36331_OFFSET

enum enum_CODEC_OFFSET_36331 {
    CODEC_OFFSET_36331_SIB8_systemTimeInfo = 0 ,
    CODEC_OFFSET_36331_SIB8_longCodeState1XRTT ,
    CODEC_OFFSET_36331_MAX_ELEM
};

#endif //enum_IE_36331_OFFSET

#define MAX_IE_OFFSET_DATAELEM( PROTOCAL_OFFSET_PREFIX )  (PROTOCAL_OFFSET_PREFIX##_MAX_ELEM)

#define CODEC_OFFSET_RET_NULL_DATA_STRUCT   -1
#define CODEC_OFFSET_RET_OK   0


typedef unsigned int CODEC_IE_OFFSET_TYPE    ;

typedef unsigned int CODEC_OFFSET_DATASTRUCT ;


/* ------------------------------------------------------------------------- */
/*    offset  interface  */
#define DECLARE_OFFSET_DATASTRUCT( name , PROTOCAL_OFFSET_PREFIX ) \
    CODEC_OFFSET_DATASTRUCT  name [ 2 * MAX_IE_OFFSET_DATAELEM(PROTOCAL_OFFSET_PREFIX) ]

#define CODEC_OFFSET_PSTART(pdata ,  index)  ((pdata) + (index)*2)
#define CODEC_OFFSET_PEND(pdata ,  index)  ((pdata) + (index)*2+1)

/* �ж�ָ���Ƿ�Ϊ�� */
int LteCodecValidOffset(CODEC_OFFSET_DATASTRUCT *);
/* ȡ����ʼƫ��,��һ���������벻Ϊ�� */
unsigned int LteCodecGetIeStartOffset(CODEC_OFFSET_DATASTRUCT *pOffsetDataStruct , unsigned int index) ;
/* ȡ�ý���ƫ�ƣ���һ���������벻Ϊ�գ���ʱ����  */
unsigned int LteCodecGetIeEndOffset(CODEC_OFFSET_DATASTRUCT *pOffsetDataStruct , unsigned int index) ;
/* ����ƫ�� */
void LteCodecSetIeStartOffset(CODEC_OFFSET_DATASTRUCT *pOffsetDataStruct , unsigned int index ,CODEC_IE_OFFSET_TYPE offset) ;
/* ����ƫ��  */
void LteCodecSetIeEndOffset(CODEC_IE_OFFSET_TYPE *pOffsetDataStruct , unsigned int index , CODEC_IE_OFFSET_TYPE offset) ;
/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif


#endif

