
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_buffer.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "drv_disp_buffer.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

HI_S32 BP_Create(HI_U32 u32BufNum, BUF_ALLOC_S *pstAlloc, BUF_POOL_S *pstBP)
{
    HI_U32 u, BufStride;
    HI_S32 nRet;
    
    if (!pstBP)
    {
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (   (u32BufNum < WIN_BUFFER_MIN_NUMBER)
        || (u32BufNum > WIN_BUFFER_MAX_NUMBER)
        )
    {
        return HI_ERR_DISP_INVALID_PARA;
    }

    DISP_MEMSET(pstBP, 0, sizeof(BUF_POOL_S));

	pstBP->enMemType = BUF_MEM_SRC_SUPPLY;
    
    if (pstAlloc)
    {
        if (  (pstAlloc->eDataFormat != HI_DRV_PIX_FMT_NV21)
            &&(pstAlloc->eDataFormat != HI_DRV_PIX_FMT_NV12)
            &&(pstAlloc->eDataFormat != HI_DRV_PIX_FMT_YUYV)
            &&(pstAlloc->eDataFormat != HI_DRV_PIX_FMT_YVYU)
            &&(pstAlloc->eDataFormat != HI_DRV_PIX_FMT_UYVY)
           )
        {
            return HI_ERR_DISP_INVALID_PARA;
        }

        if (  (pstAlloc->u32BufWidth < WIN_BUFFER_MIN_W)
            ||(pstAlloc->u32BufWidth > WIN_BUFFER_MAX_W)
            ||(pstAlloc->u32BufHeight < WIN_BUFFER_MIN_H)
            ||(pstAlloc->u32BufHeight > WIN_BUFFER_MAX_H)
            )
        {
            return HI_ERR_DISP_INVALID_PARA;
        }

		pstBP->stAlloc = *pstAlloc;

		if (!pstAlloc->bFbAllocMem)
		{
	        if (  (pstAlloc->u32BufStride < pstAlloc->u32BufWidth)
				||((pstAlloc->u32BufStride & 0xful) != 0)
				)
	        {
	            return HI_ERR_DISP_INVALID_PARA;
	        }
		}
		else
		{
	        if (  (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_NV21)
	            ||(pstAlloc->eDataFormat == HI_DRV_PIX_FMT_NV12)
	           )
	        {
	            BufStride = (pstAlloc->u32BufWidth + 15) & 0xFFFFFFF0ul;
	        }
			else if (  (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_YUYV)
			         ||(pstAlloc->eDataFormat == HI_DRV_PIX_FMT_YVYU)
			         ||(pstAlloc->eDataFormat == HI_DRV_PIX_FMT_UYVY)
			        )
	        {
	            BufStride = ( (pstAlloc->u32BufWidth * 2) + 15) & 0xFFFFFFF0ul;
	        }
			else
			{
			    BufStride =  (pstAlloc->u32BufWidth + 15) & 0xFFFFFFF0ul;
			}

			pstBP->stAlloc.u32BufStride = BufStride;
		}

		if (pstAlloc->bFbAllocMem)
		{
        	//pstBP->bAllocMemory = HI_TRUE;
			pstBP->enMemType = BUF_MEM_FB_SUPPLY;
		}
		else
		{
			// TODO:
			pstBP->enMemType = BUF_MEM_USER_SUPPLY;
		}


    }

    pstBP->pstBufQueue = DISP_MALLOC(sizeof(BUF_S) * u32BufNum);
    pstBP->pstEmptyQueue = DISP_MALLOC(sizeof(BUF_ID_S) * u32BufNum);
    pstBP->pstFullQueue = DISP_MALLOC(sizeof(BUF_ID_S) * u32BufNum);

    if (!pstBP->pstBufQueue || !pstBP->pstEmptyQueue || !pstBP->pstFullQueue)
    {
        goto __ERR_EXIT__;
    }

    if (pstBP->enMemType == BUF_MEM_FB_SUPPLY)
    {
        HI_U32 BufSize = 0;
        HI_CHAR BufName[6] = {'D', 'I', 'S', 'P', '0', '\0'};

        if (   (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_NV21)
            || (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_NV12)
           )
        {
            BufSize = (pstBP->stAlloc.u32BufStride * pstBP->stAlloc.u32BufHeight * 3 >> 1);
        }

        if (   (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_YUYV)
            || (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_YVYU)
            || (pstAlloc->eDataFormat == HI_DRV_PIX_FMT_UYVY)
           )
        {
            BufSize = pstBP->stAlloc.u32BufStride* pstBP->stAlloc.u32BufHeight * 2;
        }

        for(u=0; u<u32BufNum; u++)
        {
            BufName[4] = (HI_CHAR)('0' + u);

            nRet = DISP_OS_MMZ_Alloc((const char *)BufName, HI_NULL, BufSize, 16, &pstBP->pstBufQueue[u].stMem);
            if (nRet)
            {
                break;
            }

            //printk("buf[%d] addr=0x%x,size=%d\n", 
            //	    pstBP->pstBufQueue[u].stMem.u32StartPhyAddr,
            //	    pstBP->pstBufQueue[u].stMem.u32Size);
        }

        if (u<u32BufNum)
        {
            HI_U32 k;

            for(k=0; k<u; k++)
            {
                DISP_OS_MMZ_Release(&pstBP->pstBufQueue[k].stMem);
            }
                goto __ERR_EXIT__;
        }
    }

    pstBP->u32BufNum = u32BufNum;

    BP_Reset(pstBP);

    return HI_SUCCESS;

__ERR_EXIT__:

    if (pstBP->pstFullQueue)
    {
        DISP_FREE(pstBP->pstFullQueue);
    }

    if (pstBP->pstEmptyQueue)
    {
        DISP_FREE(pstBP->pstEmptyQueue);
    }
    
    if (pstBP->pstBufQueue)
    {
        DISP_FREE(pstBP->pstBufQueue);
    }
    
    return HI_SUCCESS;
}


HI_S32 BP_Destroy(BUF_POOL_S *pstBP)
{
    HI_U32 u;

    // if buffer in local memory, release memory
    if (pstBP->enMemType == BUF_MEM_FB_SUPPLY)
    {
        for(u=0; u<pstBP->u32BufNum; u++)
        {
            DISP_OS_MMZ_Release(&pstBP->pstBufQueue[u].stMem);
        }
    }

    if (pstBP->pstFullQueue)
    {
        DISP_FREE(pstBP->pstFullQueue);
    }
    if (pstBP->pstEmptyQueue)
    {
        DISP_FREE(pstBP->pstEmptyQueue);
    }
    if (pstBP->pstBufQueue)
    {
        DISP_FREE(pstBP->pstBufQueue);
    }
    
    return HI_SUCCESS;
}

HI_S32 BP_Reset(BUF_POOL_S *pstBP)
{
    HI_U32 u;
	HI_U32 Coffset = 0;

    // s1 reset buf queue
    if (   (pstBP->enMemType == BUF_MEM_FB_SUPPLY)
		|| (pstBP->enMemType == BUF_MEM_USER_SUPPLY)
		)
    {
    	Coffset = pstBP->stAlloc.u32BufStride * pstBP->stAlloc.u32BufHeight;
	}

    for(u=0; u<pstBP->u32BufNum; u++)
    {
        pstBP->pstBufQueue[u].u32Index = u;
        pstBP->pstBufQueue[u].enState  = BUF_STATE_EMPTY;

	    if ( (pstBP->enMemType == BUF_MEM_FB_SUPPLY) || (pstBP->enMemType == BUF_MEM_USER_SUPPLY))
	    {
	    	pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32Stride_Y = pstBP->stAlloc.u32BufStride;
	    	pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32Stride_C = pstBP->stAlloc.u32BufStride;
	        pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32PhyAddr_Y = pstBP->pstBufQueue[u].stMem.u32StartPhyAddr;
			pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32PhyAddr_C = pstBP->pstBufQueue[u].stMem.u32StartPhyAddr + Coffset;
#if 0
            printk("F: y=0x%x, c=0x%x\n",
				    pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32PhyAddr_Y,
				    pstBP->pstBufQueue[u].stFrame.stBufAddr[0].u32PhyAddr_C);
#endif
		}
    }


    // s2 reset empty queue 
    DISP_MEMSET(pstBP->pstEmptyQueue, 0, sizeof(BUF_ID_S) * pstBP->u32BufNum);

    for(u=0; u<pstBP->u32BufNum; u++)
    {
        pstBP->pstEmptyQueue[u].u32Index = WIN_BUFFER_INDEX_PREFIX |(u<<WIN_BUFFER_INDEX_SHIFT);
    }

    pstBP->u32EmptyRPtr = 0;
    pstBP->u32EmptyWPtr = 0;

    // s3 reset full queue 
    DISP_MEMSET(pstBP->pstFullQueue , 0, sizeof(BUF_ID_S) * pstBP->u32BufNum);
    for(u=0; u<pstBP->u32BufNum; u++)
    {
        pstBP->pstFullQueue[u].u32Index = WIN_BUFFER_INDEX_INVALID;
    }

    pstBP->u32FullRPtr = 0;
    pstBP->u32FullWPtr = 0;

    // s4 clean statistic
    DISP_MEMSET(&pstBP->stStatistic, 0, sizeof(BUF_STAT_S));

    return HI_SUCCESS;
}

// produce and consume empty buffer
// put in node
HI_S32 BP_GetEmptyBuf(BUF_POOL_S *pstBP, HI_U32 *pu32BufId)
{
    HI_U32 id, index;

    id = pstBP->pstEmptyQueue[pstBP->u32EmptyRPtr].u32Index;
    if (WIN_BUFFER_INDEX_INVALID == id)
    {
        DISP_INFO("GE queue empty!\n");
        return HI_FAILURE;
    }

    index = (id >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;
    if (BUF_STATE_EMPTY == pstBP->pstBufQueue[index].enState)
    {
        *pu32BufId = id;
        return HI_SUCCESS;
    }
    else
    {
        DISP_ERROR("GE invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
}


HI_S32 BP_GetDoneBuf(BUF_POOL_S *pstBP, HI_U32 *pu32BufId)
{
    HI_U32 id, index;

    id = pstBP->pstEmptyQueue[pstBP->u32EmptyRPtr].u32Index;
    if (WIN_BUFFER_INDEX_INVALID == id)
    {
        DISP_INFO("GD queue empty!\n");
        return HI_FAILURE;
    }

    index = (id >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;
    if (BUF_STATE_DONE == pstBP->pstBufQueue[index].enState)
    {
        *pu32BufId = id;
        return HI_SUCCESS;
    }
    else
    {
        DISP_ERROR("GD invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
}



HI_S32 BP_DelEmptyBuf(BUF_POOL_S *pstBP, HI_U32 u32BufId)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("DE invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (BUF_STATE_EMPTY == pstBP->pstBufQueue[index].enState)
    {
        pstBP->pstBufQueue[index].enState = BUF_STATE_WRITING;
        pstBP->pstEmptyQueue[pstBP->u32EmptyRPtr].u32Index = WIN_BUFFER_INDEX_INVALID;

        pstBP->u32EmptyRPtr = (pstBP->u32EmptyRPtr + 1) % pstBP->u32BufNum;

        pstBP->stStatistic.u32EmptyDoing = index;
        pstBP->stStatistic.u32EmptyDel++;
        return HI_SUCCESS;
    }
    else
    {
        DISP_ERROR("DE invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
}


HI_S32 BP_AddEmptyBuf(BUF_POOL_S *pstBP, HI_U32 u32BufId)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("AE invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (pstBP->pstEmptyQueue[pstBP->u32EmptyWPtr].u32Index != WIN_BUFFER_INDEX_INVALID)
    {
        DISP_ERROR("AE queue full!\n");
        return HI_FAILURE;
    }
    else if (pstBP->pstBufQueue[index].enState != BUF_STATE_READING)
    {
        DISP_ERROR("AE invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
    {
        pstBP->pstBufQueue[index].enState = BUF_STATE_DONE;
        pstBP->pstEmptyQueue[pstBP->u32EmptyWPtr].u32Index = u32BufId;
        pstBP->u32EmptyWPtr = (pstBP->u32EmptyWPtr + 1) % pstBP->u32BufNum;

        pstBP->stStatistic.u32EmptyAdd++;
        return HI_SUCCESS;
    }
}


HI_S32 BP_SetBufEmpty(BUF_POOL_S *pstBP, HI_U32 u32BufId)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("SE invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (pstBP->pstBufQueue[index].enState != BUF_STATE_DONE)
    {
        DISP_ERROR("SE invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
    {
        pstBP->pstBufQueue[index].enState = BUF_STATE_EMPTY;

        return HI_SUCCESS;
    }
}

// produce and consume full buffer
HI_S32 BP_GetFullBuf(BUF_POOL_S *pstBP, HI_U32 *pu32BufId)
{
    HI_U32 id, index;

    id = pstBP->pstFullQueue[pstBP->u32FullRPtr].u32Index;
    if (WIN_BUFFER_INDEX_INVALID == id)
    {
        DISP_INFO("GF queue empty!\n");
        return HI_FAILURE;
    }

    index = (id >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;
    
    if (BUF_STATE_FULL == pstBP->pstBufQueue[index].enState)
    {
        *pu32BufId = id;
        return HI_SUCCESS;
    }
    else
    {
        DISP_ERROR("GF invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
}

HI_S32 BP_DelFullBuf(BUF_POOL_S *pstBP, HI_U32 u32BufId)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("DF invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (BUF_STATE_FULL == pstBP->pstBufQueue[index].enState)
    {
        pstBP->pstBufQueue[index].enState = BUF_STATE_READING;
        pstBP->pstFullQueue[pstBP->u32FullRPtr].u32Index = WIN_BUFFER_INDEX_INVALID;
        pstBP->u32FullRPtr = (pstBP->u32FullRPtr + 1) % pstBP->u32BufNum;

        pstBP->stStatistic.u32FullDoing = index;
        pstBP->stStatistic.u32FullDel++;
        return HI_SUCCESS;
    }
    else
    {
        DISP_ERROR("DF invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
}

HI_S32 BP_AddFullBuf(BUF_POOL_S *pstBP, HI_U32 u32BufId)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("AF invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (pstBP->pstFullQueue[pstBP->u32FullWPtr].u32Index != WIN_BUFFER_INDEX_INVALID)
    {
        DISP_ERROR("AF queue full!\n");
        return HI_FAILURE;
    }
    else if (pstBP->pstBufQueue[index].enState != BUF_STATE_WRITING)
    {
        DISP_ERROR("AF invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
    {
        pstBP->pstBufQueue[index].enState = BUF_STATE_FULL;
        pstBP->pstFullQueue[pstBP->u32FullWPtr].u32Index = u32BufId;
        pstBP->u32FullWPtr = (pstBP->u32FullWPtr + 1) % pstBP->u32BufNum;

        pstBP->stStatistic.u32FullAdd++;
        return HI_SUCCESS;
    }
}


// get and set frame to buffer
HI_S32 BP_GetFrame(BUF_POOL_S *pstBP, HI_U32 u32BufId, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("GetF invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

#if 0
    if (pstBP->pstBufQueue[index].enState != BUF_STATE_WORKING)
    {
        DISP_ERROR("GetF invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
#endif
    {
        *pstFrame = pstBP->pstBufQueue[index].stFrame;

        return HI_SUCCESS;
    }
}

HI_S32 BP_SetFrame(BUF_POOL_S *pstBP, HI_U32 u32BufId, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("SetF invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (pstBP->pstBufQueue[index].enState != BUF_STATE_WRITING)
    {
        DISP_ERROR("SetF invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
    {
        pstBP->pstBufQueue[index].stFrame = *pstFrame;
        return HI_SUCCESS;
    }
}

// get and set user data to buffer
HI_S32 BP_GetUserData(BUF_POOL_S *pstBP, HI_U32 u32BufId, BUF_USERDATA_S *pstData)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("GetU invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

#if 0
    if (pstBP->pstBufQueue[index].enState != BUF_STATE_WORKING)
    {
        DISP_ERROR("GetU invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
#endif
    {
        memcpy(pstData, &pstBP->pstBufQueue[index].stUserData, sizeof(BUF_USERDATA_S));
        return HI_SUCCESS;
    }
}

HI_S32 BP_SetUserData(BUF_POOL_S *pstBP, HI_U32 u32BufId, BUF_USERDATA_S *pstData)
{
    HI_U32 index;

    index = (u32BufId >> WIN_BUFFER_INDEX_SHIFT) & WIN_BUFFER_INDEX_MASK;

    if (  ((u32BufId & WIN_BUFFER_INDEX_PREFIX_MASK) != WIN_BUFFER_INDEX_PREFIX)
        ||(index >= pstBP->u32BufNum)
        )
    {
        DISP_ERROR("SetU invalid id=0x%x\n", u32BufId);
        return HI_FAILURE;
    }

    if (pstBP->pstBufQueue[index].enState != BUF_STATE_WRITING)
    {
        DISP_ERROR("SetU invalid state buf[%d]=%d\n", index,(HI_S32)pstBP->pstBufQueue[index].enState);
        return HI_FAILURE;
    }
    else
    {
        memcpy(&pstBP->pstBufQueue[index].stUserData, pstData, sizeof(BUF_USERDATA_S));
        return HI_SUCCESS;
    }
}

HI_S32 BP_GetFullBufNum(BUF_POOL_S *pstBP, HI_U32 *pu32BufNum)
{
    HI_U32 num;
    HI_U32 r, w;

    r = pstBP->u32FullRPtr;
    w = pstBP->u32FullWPtr;
    if (w >= r)
    {
        num = w - r;
    }
    else
    {
        num = w + pstBP->u32BufNum - r;
    }

    if (num <= pstBP->u32BufNum)
    {
        *pu32BufNum = num;
    }
    else
    {
        DISP_ERROR("BP_GetFullBufNum invalid!\n");
        *pu32BufNum = 0;
    }

    return HI_SUCCESS;
}

HI_S32 BP_GetEmptyBufNum(BUF_POOL_S *pstBP, HI_U32 *pu32BufNum)
{
    HI_U32 num;

    if (pstBP->u32EmptyWPtr >= pstBP->u32EmptyRPtr)
    {
        num = pstBP->u32EmptyWPtr - pstBP->u32EmptyRPtr;
    }
    else
    {
        num = pstBP->u32EmptyWPtr+ pstBP->u32BufNum - pstBP->u32EmptyRPtr;
    }

    if (num <= pstBP->u32BufNum)
    {
        *pu32BufNum = num;
    }
    else
    {
        DISP_ERROR("BP_GetEmptyBufNum invalid!\n");
        *pu32BufNum = 0;
    }

    return HI_SUCCESS;
}

HI_S32 BP_GetBufState(BUF_POOL_S *pstBP, BUF_STT_S *pstBufState)
{
    HI_U32 BufId, u;

    if (!pstBP || !pstBufState)
    {
        DISP_ERROR("%s input null pointer!\n", __FUNCTION__);
        return HI_FAILURE;
    }

    DISP_MEMSET(pstBufState, 0, sizeof(BUF_STT_S));

    pstBufState->u32BufNum = pstBP->u32BufNum;
    pstBufState->enMemType    = (HI_U32)pstBP->enMemType;
    pstBufState->enPixFmt     = (HI_U32)pstBP->stAlloc.eDataFormat;

    pstBufState->u32EmptyRPtr = pstBP->u32EmptyRPtr;
    pstBufState->u32EmptyWPtr = pstBP->u32EmptyWPtr;
    pstBufState->u32FullRPtr  = pstBP->u32FullRPtr;
    pstBufState->u32FullWPtr  = pstBP->u32FullWPtr;
    pstBufState->u32EmptyDel  = pstBP->stStatistic.u32EmptyDel; 
    pstBufState->u32EmptyAdd  = pstBP->stStatistic.u32EmptyAdd;
    pstBufState->u32EmptyDoing= pstBP->stStatistic.u32EmptyDoing;
    pstBufState->u32FullDel   = pstBP->stStatistic.u32FullDel;
    pstBufState->u32FullAdd   = pstBP->stStatistic.u32FullAdd;
    pstBufState->u32FullDoing = pstBP->stStatistic.u32FullDoing;

    for(u=0; u<pstBP->u32BufNum; u++)
    {
        pstBufState->stBufState[u]   = (HI_U32)pstBP->pstBufQueue[u].enState;
        pstBufState->stEmptyQueue[u] = pstBP->pstEmptyQueue[u].u32Index;
        pstBufState->stFullQueue[u]  = pstBP->pstFullQueue[u].u32Index;
    }


    if (!BP_GetFullBuf(pstBP, &BufId))
    {
        BP_GetFrame(pstBP, BufId, &pstBufState->stFrame);
    }

    return HI_SUCCESS;
}


static HI_U32 s_u32BlackFrameCount = 0;
static BUF_S s_stBlackFrame;

#define BLACK_FRAME_WIDTH  64
#define BLACK_FRAME_HEIGHT 64
#define BLACK_FRAME_PIXFMT HI_DRV_PIX_FMT_NV21


HI_S32 BP_CreateBlackFrame(HI_VOID)
{
    HI_U32 BufSize = BLACK_FRAME_WIDTH*BLACK_FRAME_HEIGHT*2;
    HI_UCHAR *pY, *pUV;
    HI_DRV_VIDEO_FRAME_S *pstFrame = &(s_stBlackFrame.stFrame);
    HI_S32 nRet;

    if (s_u32BlackFrameCount)
    {
        DISP_ERROR("black frame has been created!\n");
        return HI_FAILURE;
    }

    DISP_MEMSET(&s_stBlackFrame, 0, sizeof(BUF_S));
    nRet = DISP_OS_MMZ_AllocAndMap((const char *)"Black", HI_NULL, BufSize, 16, &s_stBlackFrame.stMem);
    if (nRet)
    {
        DISP_ERROR("Alloc black frame memory failed\n");
        return HI_FAILURE;
    }

    pY  = (HI_UCHAR *)(s_stBlackFrame.stMem.u32StartVirAddr);
    DISP_MEMSET(pY, 0x10, BufSize);
    pUV = (HI_UCHAR *)(s_stBlackFrame.stMem.u32StartVirAddr + BLACK_FRAME_WIDTH*BLACK_FRAME_HEIGHT);
    DISP_MEMSET(pUV, 0x80, BufSize);

    pstFrame->u32FrameIndex = 0;
    pstFrame->stBufAddr[0].u32PhyAddr_Y = s_stBlackFrame.stMem.u32StartPhyAddr;  
    pstFrame->stBufAddr[0].u32PhyAddr_C=  pstFrame->stBufAddr[0].u32PhyAddr_Y + BLACK_FRAME_WIDTH*BLACK_FRAME_HEIGHT;  
    pstFrame->stBufAddr[0].u32Stride_Y = BLACK_FRAME_WIDTH;
    pstFrame->stBufAddr[0].u32Stride_C = BLACK_FRAME_WIDTH;

#if 0
    printk("@@@@@@@@@ Black frame Y=0x%x, C=0x%x\n", 
             pstFrame->stBufAddr[0].u32PhyAddr_Y,
             pstFrame->stBufAddr[0].u32PhyAddr_C);
#endif

    pstFrame->u32Width  = BLACK_FRAME_WIDTH;
    pstFrame->u32Height = BLACK_FRAME_HEIGHT;

    pstFrame->u32SrcPts = 0xffffffff;  /* 0xffffffff means unknown */
    pstFrame->u32Pts    = 0xffffffff;  /* 0xffffffff means unknown */

    pstFrame->u32AspectWidth  = 0;
    pstFrame->u32AspectHeight = 0; 
    pstFrame->u32FrameRate = 0;     /* in 1/100 Hz, 0 means unknown */

    pstFrame->ePixFormat = BLACK_FRAME_PIXFMT;
    pstFrame->bProgressive = HI_TRUE;
    pstFrame->enFieldMode  = HI_DRV_FIELD_ALL;
    pstFrame->bTopFieldFirst = HI_TRUE;

    //display region in rectangle (x,y,w,h)
    pstFrame->stDispRect.s32X = 0;
    pstFrame->stDispRect.s32Y = 0;
    pstFrame->stDispRect.s32Width  = pstFrame->u32Width;
    pstFrame->stDispRect.s32Height = pstFrame->u32Height;

    pstFrame->eFrmType = HI_DRV_FT_NOT_STEREO;
    pstFrame->u32Circumrotate = 0;
    pstFrame->bToFlip_H = HI_FALSE;
    pstFrame->bToFlip_V = HI_FALSE;
    pstFrame->u32ErrorLevel = 0;

    s_u32BlackFrameCount++;
    return HI_SUCCESS;
}

HI_S32 BP_DestroyBlackFrame(HI_VOID)
{
    if (!s_u32BlackFrameCount)
    {
        DISP_ERROR("black frame has not been created!\n");
        return HI_FAILURE;
    }

    DISP_OS_MMZ_UnmapAndRelease(&s_stBlackFrame.stMem);

    DISP_MEMSET(&s_stBlackFrame, 0, sizeof(BUF_S));

    s_u32BlackFrameCount = 0;

    return HI_SUCCESS;
}

HI_S32 BP_GetBlackFrame(HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    if (pstFrame && s_u32BlackFrameCount)
    {
        *pstFrame = s_stBlackFrame.stFrame;
         return HI_SUCCESS;
    }

    DISP_ERROR("black frame has not been created OR NULL pointer!\n");
    return HI_FAILURE;
}


HI_DRV_VIDEO_FRAME_S *BP_GetBlackFrameInfo(HI_VOID)
{
    if (s_u32BlackFrameCount)
    {
         return &s_stBlackFrame.stFrame;
    }

    DISP_ERROR("black frame has not been created OR NULL pointer!\n");
    return HI_NULL;
}



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

