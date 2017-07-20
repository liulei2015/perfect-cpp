#ifndef _INCL_USI_UeCellInfoTransfer_H__
#define _INCL_USI_UeCellInfoTransfer_H__

USI_NS_BEGIN

const WORD16 CELL_IDENTITY_LEN = 28;
const WORD16 CRINT_LEN = 16;

#define DcmGetEnbIdCellIdByCellIdentity(cellIdentity, dwENodeBId, wCellId)\
    do {\
        (dwENodeBId)  = ((cellIdentity).data[2] & 0xF0) >> 4;\
        (dwENodeBId) |= (cellIdentity).data[1] << 4;\
        (dwENodeBId) |= (cellIdentity).data[0] << 12;\
        (wCellId)     = ((cellIdentity).data[2] & 0xF) << 4;\
        (wCellId)    |= ((cellIdentity).data[3] & 0xF0) >> 4;\
    } while(0)

#define DcmFillCellIdentity(cellIdentity, dwENodeBId, wCellId) do{\
    (cellIdentity).numbits  = CELL_IDENTITY_LEN;\
    (cellIdentity).data[0]  = (BYTE) (((dwENodeBId) & 0xFF000) >> 12);\
    (cellIdentity).data[1]  = (BYTE) (((dwENodeBId) & 0xFF0) >> 4);\
    (cellIdentity).data[2]  = (BYTE) (((dwENodeBId) & 0xF) << 4);\
    (cellIdentity).data[2] |= (BYTE) (((wCellId)    & 0xF0) >> 4);\
    (cellIdentity).data[3]  = (BYTE) (((wCellId)    & 0xF) << 4);\
} while(0)

#define DcmFillCrnti(CRNTI, WORD_INPUT) do{\
    (CRNTI).numbits = CRINT_LEN;\
    (CRNTI).data[0] = (BYTE)(((WORD_INPUT) & 0xFF00) >> 8);\
    (CRNTI).data[1] = (BYTE)((WORD_INPUT) & 0x00FF);\
}while(0)

USI_NS_END

#endif // UeCellInfoTransfer_h__

