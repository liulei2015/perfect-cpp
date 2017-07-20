#include "l0-infra/tools/ToolsCpuControlStrategy.h"
//#include "pub_tool_ccinterface.h"
//#include "l0-infra/wrapper/ng_pub_lte_sig_trace.h"

namespace
{
    enum
    {
        CPU_STATE_LOW,
        CPU_STATE_MID,
        CPU_STATE_HIGH ,
        CPU_STATE_OVER,
    };

    BYTE getCpuPayloadLevel()
    {
//        return ToolGetPayload();
    	return 0;
    }

    bool isCpuLoadBelowMid()
    {
        return getCpuPayloadLevel() < (BYTE)CPU_STATE_MID;
    }

    bool isCpuLoadBelowHigh()
    {
        return getCpuPayloadLevel() < (BYTE)CPU_STATE_HIGH;
    }

    bool isCpuLoadBelowOver()
    {
        return getCpuPayloadLevel() < (BYTE)CPU_STATE_OVER;
    }

    bool isCpuLoadEqualMid()
    {
        return getCpuPayloadLevel() == (BYTE)CPU_STATE_MID;
    }

    bool isCpuLoadEqualOver()
    {
        return getCpuPayloadLevel() == (BYTE)CPU_STATE_OVER;
    }

    bool isStandardSignal(BYTE direction)
    {
//        return direction < RNLC_ENB_TRACE_RNLC_SENT;
    	return true;
    }
}
////////////////////////////////////////////////////////////////////////
//����       �͸���        �и���              �߸���     ����
//�������    ����       ������ֻ�ϱ���׼���    ֹͣ      ֹͣ
//CT         ����          ����                ֹͣ      ֹͣ
//CDT        ����          ����                ֹͣ      ֹͣ
//MR         ����       �ϱ�UE��������          ֹͣ      ֹͣ (RRM)
//���        ����         ����                ֹͣ      ֹͣ
//MDT        ����         ����                 ֹͣ      ֹͣ
//MTS        ����         ����                 ֹͣ      ֹͣ
//Ƶ��ɨ��    ����          ����                ֹͣ      ֹͣ
//TraceMe    ����         ֹͣ                 ֹͣ      ֹͣ
//SOP        ����         ֹͣ                 ֹͣ      ֹͣ
//TTI        ����          ֹͣ                ֹͣ      ֹͣ
//��������     ����         ֹͣ                ֹͣ      ֹͣ
////////////////////////////////////////////////////////////////////////

BYTE ToolsCpuControlStrategy::getCurrentCpuLevel()
{
    return getCpuPayloadLevel();
}

bool ToolsCpuControlStrategy::shouldReportMdt()
{
    return isCpuLoadBelowHigh();
}

bool ToolsCpuControlStrategy::shouldReportCdt()
{
    return isCpuLoadBelowHigh();
}

bool ToolsCpuControlStrategy::shouldReportSignalTraceBy(BYTE direction)
{
    return isCpuLoadBelowMid()
       || (isCpuLoadEqualMid() && isStandardSignal(direction));
}

bool ToolsCpuControlStrategy::shouldReportTraceMe()
{
    return isCpuLoadBelowMid();
}

bool ToolsCpuControlStrategy::shouldReportCt()
{
    return isCpuLoadBelowHigh();
}

bool ToolsCpuControlStrategy::shouldReportImsiTrace()
{
    return isCpuLoadBelowHigh();
}
