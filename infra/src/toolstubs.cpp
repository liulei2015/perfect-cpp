//#include "pub_tool_ccinterface.h"
#include "l0-infra/base/BaseTypes.h"

typedef struct T_ToolDataReportHeader
{
    WORD16     wHeaderFlag;    /* 0xAA55, 标记字段，解码时区分多个包 */
    BYTE       ucEventType;    /* CDT 上报时的事件号, 无效值0xFF */

    BYTE       ucRrcChannelType : 6; // RRC 消息逻辑信道类型，默认 0x3F
    BYTE       ucHoSourcePresent : 2;  // 0: 触发端，1：被触发端，3：无效值(默认填写无效值)
    WORD16     wModulerNo;     /* 数据上报模块号，使用TraceMe打印分配的模块号 */
    WORD16     wCellID;
    WORD16     wUeGid;
    WORD16     wDataLength;    /* 不包含上报结构头的数据长度 */
    WORD32     dwRemoteEnbId;  /* X2交互消息中，目标eNBID, 仅X2信令跟踪填写 */
    //T_ToolGuMmei  tGuMmei;     /* 小区级信令跟踪，S1口信令填写，无效值为全F */
    WORD16     wMsgId;         /* 信令跟踪时填写消息ID */
    BYTE       ucDataType;     /* T_ToolReportDataType 1: UE级数据，2:小区级数据，3:基站级数据 */
    BYTE       ucDirection;    /* 信令跟踪时填写，信令方向，0:接收，1:发送 */
    BYTE       ucDataIdListCount;  /* 本结构后连续跟上的DataId结构个数 */
    BYTE       ucIsPeriodData; /* 是否为周期类型数据，T_ToolDataReportType: 0:事件类型，1:周期类型 */
    BYTE       ucTaskId;       /* 任务ID，MR、MDT、SC任务时反填 */
    BYTE       ucSupperCellType;  /* 0:普通小区，1：主CP，2：辅CP（默认普通小区） */
    BYTE       ucSupperCellCpId;  /* 当小区类型不为普通小区时，该值有效（默认0xF） */
    BYTE       ucRes;    // 默认0xFFFF，保留位
    WORD16     wRnti;   // 默认0xFFFF，当不为0xFFFF时，TOOL模块上报消息中，使用该RNTI 填写上报消息头
} T_ToolDataReportHeader;

struct T_DataIdIndex;

extern "C"
{
///////////////////////////////////////////////////////////////////
BOOLEAN NeedToolUeDataReport(WORD32 dwDataId, WORD16 wGid, WORD16 wCellId)
{
    return true;
}

BOOLEAN NeedToolCellDataReport(WORD32 dwDataId, WORD16 wCellId)
{
    return true;
}

BOOLEAN NeedToolEnbDataReport(WORD32 dwDataId)
{
    return true;
}

WORD32 ReportOneData(T_ToolDataReportHeader &tHeader, T_DataIdIndex &tIndex, BYTE *pBuf)
{
    return 0;
}

BOOLEAN ToolIsStdSigTrace(WORD16 wGid, WORD32 dwDataId)
{
    return true;
}

BOOLEAN ToolIsInnerSigTrace()
{
    return true;
}

}
