/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_drv_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/21
  Description   :
  History       :
  1.Date        : 2009/12/21
    Author      : w58735
    Modification: Created file

******************************************************************************/
#ifndef __HI_DRV_PVR_H__
#define __HI_DRV_PVR_H__

#include "hi_unf_pvr.h"
#include "hi_mpi_pvr.h"

/* definition of max play channel */
#define PVR_PLAY_MAX_CHN_NUM            2

/* definition of max record channel */
#define PVR_REC_MAX_CHN_NUM             3
#define PVR_REC_START_NUM               PVR_PLAY_MAX_CHN_NUM

#define CMD_PVR_INIT_PLAY               _IOR(HI_ID_PVR, 0x01, HI_U32)
#define CMD_PVR_CREATE_PLAY_CHN         _IOR(HI_ID_PVR, 0x02, HI_U32)
#define CMD_PVR_DESTROY_PLAY_CHN        _IOW(HI_ID_PVR, 0x03, HI_U32)

#define CMD_PVR_INIT_REC                _IOR(HI_ID_PVR, 0x11, HI_U32)
#define CMD_PVR_CREATE_REC_CHN          _IOR(HI_ID_PVR, 0x12, HI_U32)
#define CMD_PVR_DESTROY_REC_CHN         _IOW(HI_ID_PVR, 0x13, HI_U32)

/* attributes of play channel                                               */
typedef struct hiPVR_PLAY_CHN_PROC_S
{
    HI_U32           u32DmxId;
    HI_HANDLE        hAvplay;
    HI_HANDLE        hTsBuffer;
#ifdef HI_CIPHER_SUPPORT
    HI_HANDLE        hCipher;                              /* cipher handle */
#endif
    HI_CHAR          szFileName[PVR_MAX_FILENAME_LEN];     /**name of stream file for playing,static attribution *//*CNcomment: �������������ļ�������̬���ԡ�        */

    HI_UNF_PVR_PLAY_STATE_E enState;                       /* play state */
    HI_UNF_PVR_PLAY_SPEED_E enSpeed;

    HI_U64          u64CurReadPos;      /* current data file read position */
    HI_U32          u32StartFrame;      /* the first available frame number in index while play cycle playing *//*CNcomment: ѭ������ʱ��Ч�ĵ�һ֡��Index�е�֡�� */
    HI_U32          u32EndFrame;        /* the last available frame number in index while play cycle playing *//*CNcomment: ѭ������ʱ��Ч�����һ֡��Index�е�֡�� */
    HI_U32          u32LastFrame;       /* the frame number in the end of cycle playing *//*CNcomment: ѭ��β�����һ֡��֡�� */
    HI_U32          u32ReadFrame;       /* read pointer of index file when playing,frame amount *//*CNcomment:����ʱ�����ļ��Ķ�ָ�룬֡���� */

} PVR_PLAY_CHN_PROC_S;

/* attributes of record channel                                             */
typedef struct hiPVR_REC_CHN_PROC_S
{
    HI_UNF_PVR_REC_ATTR_S stUserCfg;
    HI_U32              u32RecOffset;
    HI_U64              u64CurFileSize;                     /* current position of record file */
    HI_UNF_PVR_REC_STATE_E     enState;                     /* record state */
    HI_UNF_PVR_REC_INDEX_TYPE_E enIndexType;                /**< index type,static attribution *//*CNcomment:�������ͣ���̬���ԡ� */
    HI_UNF_VCODEC_TYPE_E        enIndexVidType;             /**< code fomat of stream waitting for creating index,it should be configured when the index type is HI_UNF_PVR_REC_INDEX_TYPE_VIDEO,  static attribution*/
                                                            /*CNcomment:��������������������Ƶ����Э��,����������HI_UNF_PVR_REC_INDEX_TYPE_VIDEOʱ����Ҫ����,��̬����  */
    HI_U32                      u32WriteFrame;              /*current written index offset *//*CNcomment:��ǰд������ƫ��*/
    PVR_INDEX_ENTRY_S           stLastRecFrm;
} PVR_REC_CHN_PROC_S;

#endif
