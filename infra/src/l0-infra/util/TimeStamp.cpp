#include "l0-infra/util/TimeStamp.h"

extern "C" WORD16 BspSubFrameNumGet();
extern "C" WORD16 BspFrameNumGet();

WORD16 getTimeStamp()
{
//    WORD16 frameNum = BspFrameNumGet();
//    frameNum = (frameNum & (WORD16)0x03ff) << 4;
//
//    WORD16 subFrameNum = BspSubFrameNumGet();
//    subFrameNum &= (BYTE)0x0f;
//
//    return (WORD16)(frameNum | subFrameNum);
    return 0;
}

