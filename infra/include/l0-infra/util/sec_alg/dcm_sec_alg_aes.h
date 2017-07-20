/*<FH>*************************************************************************
* ��Ȩ����: Copyright (C) 2009 ����ͨѶ�ɷ����޹�˾LTE������
* ģ������: USI
* �ļ�����: DcmSecAlgAes.h
* ����ժҪ: 
* ����˵��: 
* ��ǰ�汾: v1.0
* ��    ��: zhengwei
* �������: 2009-8-22 
* �޸ļ�¼:
*    �޸�����        �汾        �޸���            �޸�ժҪ
*-----------------------------------------------------------------------------
*   2009-8-21        V1.0       zhengwei            ����
**<FH>***********************************************************************/
#ifndef _INCL_USI_USI_SEC_ALG_AES_H__
#define _INCL_USI_USI_SEC_ALG_AES_H__


#ifdef  __cplusplus
extern  "C"     {
#endif



#ifdef WIN32

#ifndef _LITTLE_ENDIAN
#define _LITTLE_ENDIAN
#endif

#ifdef _LITTLE_ENDIAN
#ifndef ntohs
#define ntohs(x) \
    (WORD32)(((WORD16)(x) & 0xffU) << 8 | ((WORD16)(x) & 0xff00U) >> 8)
#endif
#ifndef ntohl

#define ntohl(x) \
    (WORD32)(((WORD32)(x) & 0xff) << 24 |   \
    ((WORD32)(x) & 0xff00) << 8 | ((WORD32)(x) & 0xff0000) >> 8 |\
    ((WORD32)(x) & 0xff000000) >> 24)
#endif
#ifndef htons
#define htons(x) ntohs(x)
#endif
#ifndef htonl
#define htonl(x) ntohl(x)
#endif

#endif 

#else   /* #ifdef WIN32 */
   
#ifndef _BIG_ENDIAN
#define _BIG_ENDIAN
#endif

#ifndef ntohs
#define ntohs(x) (x)
#endif
#ifndef ntohl
#define ntohl(x) (x)
#endif
#ifndef htons
#define htons(x) (x)
#endif
#ifndef htonl
#define htonl(x) (x)
#endif


#endif /* #ifdef WIN32 */

/* �޸�C++Test�� DcmSecAlgAes.c���Ƴ�: �ܳ��� 2009-11-13 */

#define AES_MAXNR 14
#define AES_BLOCK_SIZE 16

typedef struct aes_key_st {
    unsigned int rd_key[4 *(AES_MAXNR + 1)];
    int rounds;
}AES_KEY;


/* �⼸�����Ͳ�����LTE����淶��ֻ������������ֲ���Ĵ��롣 */
#ifndef u32
typedef unsigned int u32;
#endif
#ifndef u8
typedef unsigned char u8;
#endif

void AesF9( BYTE * pbyKey, WORD32 dwCount, WORD32 dwBearer, WORD32 dwDir, BYTE *pbyIn, WORD32 dwLength,BYTE *pbyMac);

#ifdef      __cplusplus
}
#endif

#endif /* RNLUPDCPSECALGAES_H */


