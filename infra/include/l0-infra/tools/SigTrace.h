#ifndef INCL_USI_H8DBCF03A_FEEF_430E_B05E_D07287C64E24
#define INCL_USI_H8DBCF03A_FEEF_430E_B05E_D07287C64E24

#include "l0-infra/base/BaseTypes.h"

struct T_ToolDataReportHeader;
struct T_DataIdIndex;

const BYTE DefRrcChannelType = 0x3F;
const BYTE InvalidHoSourPresent = 0x03;

struct SigTrace
{
    SigTrace(const WORD32 peerEnbId, const WORD16 dataId,
             const WORD16 eventId, const WORD16 cellId,
             const WORD16 gid,const WORD16 dataLen,
             const BYTE direction, const void*  data,
             const BYTE rrcChannelType, const BYTE hoSourcePresent);
	
    void report() const;

private:
    void buildHeader(T_ToolDataReportHeader&) const;
    void buildIndex(T_DataIdIndex&) const;

    bool needReport() const;
    bool isToolNeedReport() const;

private:
    const WORD32 peerEnbId;
    const WORD16 dataId;
    const WORD16 eventId;
    const WORD16 cellId;
    const WORD16 dataLen;
    const BYTE   direction;
    WORD16 gid;
    WORD16 crnti;
	BYTE rrcChannelType;
	BYTE hoSourcePresent;
    const void*  data;
};

#endif
