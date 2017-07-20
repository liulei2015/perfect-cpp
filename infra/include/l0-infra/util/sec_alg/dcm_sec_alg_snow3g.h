/*<FH>*************************************************************************
* 版权所有: Copyright (C) 2009 中兴通讯股份有限公司LTE开发部
* 模块名称: USI
* 文件名称: DcmSecAlgSnow3G.h
* 内容摘要: 
* 其他说明: 
* 当前版本: v1.0
* 作    者: zhengwei
* 完成日期: 2009-8-22 
* 修改记录:
*    修改日期        版本        修改人            修改摘要
*-----------------------------------------------------------------------------
*   2009-8-21        V1.0       zhengwei            创建
**<FH>***********************************************************************/
#ifndef _INCL_USI_USI_SEC_ALG_SNOW3G_H__
#define _INCL_USI_USI_SEC_ALG_SNOW3G_H__


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

#else  /* #ifdef WIN32 */
   
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
#endif  /* #ifdef WIN32 */

#endif

#ifndef u8
typedef unsigned char u8;
#endif

#ifndef u32
typedef unsigned int u32;
#endif

#ifndef u64
#ifndef WIN32
typedef unsigned long long  u64;
#else
typedef unsigned __int64  u64;
#endif
#endif

VOID Snow3gF9(BYTE * key, WORD32 count, WORD32 fresh, WORD32 dir, BYTE *data, WORD32 length,BYTE *mac);


#ifdef      __cplusplus
}
#endif

#endif /* RNLUPDCPSECALGSNOW3G_H */


