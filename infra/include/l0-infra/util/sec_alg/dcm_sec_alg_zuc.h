/*******************************************************************************
* ��Ȩ���� (C)2008, ����������ͨѶ�ɷ����޹�˾
* 
*   ģ�����ƣ�  PDCP
*   �ļ����ƣ�  DcmPdcpSecAlgZuc.h
*   ����ժҪ��  Zuc�㷨ͷ�ļ�
*   ����˵����  
*   ��ǰ�汾��  v1.0
*   ��    �ߣ�  ��С��170295
*   ������ڣ�  
* 
*   �޸�����    �� �� ��    �� �� ��    �޸�����
*
*   2009-05-14     1.0       ��С��170295       �� ��          
*******************************************************************************/
#ifndef _INCL_USI_USI_SEC_ALG_ZUC_H__
#define _INCL_USI_USI_SEC_ALG_ZUC_H__


#ifdef  __cplusplus
extern  "C"     {
#endif


#ifdef _VC_TEST

/* ��С�� */
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER __LITTLE_ENDIAN
#endif

#else  /* #ifdef _VC_TEST */

/* ��С�� */
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif

#ifndef __BYTE_ORDER
#define __BYTE_ORDER __BIG_ENDIAN
#endif

#endif   /* #ifdef _VC_TEST */
#if __BYTE_ORDER == __LITTLE_ENDIAN
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
#else /* #if __BYTE_ORDER == __LITTLE_ENDIAN */
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
#endif  /* #if __BYTE_ORDER == __LITTLE_ENDIAN */

#define ZUC_BUFLENGTH    128    /* ���������� */


VOID DcmZucF9(BYTE * pbyKey, DWORD dwCount, DWORD dwBearer, DWORD dwDir, BYTE *pbyIn, DWORD dwLength,BYTE *pbyMac);


#ifdef      __cplusplus
}
#endif


#endif /* RNLUPDCPSECALGZUC_H */


