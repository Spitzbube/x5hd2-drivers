/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : jpeg_hdec_mem.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2013/06/20
Description	    : the mem alloc realize in this file
                  CNcomment: jpegӲ��������Ҫ���ڴ�������ļ���ʵ��.
                  MMZ�ڴ�ʹ��ԭ��:
                  (1)ˢ�ֲ�cach������ˢȫ��cach��Ҫ���ڴ�С��cach��С�ֲ���ȫ�ֿ� 
                  (2)Ҫ��û���õ������ڴ治��Ҫӳ���Լ��÷�cach��ʽ��Ҫ��ʹ��cach��ʽ
                     ��ʹ������ڴ�֮ǰҪˢcach����Ȼcach�л������ݲ����Լ�Ҫ��cach����
                     ���������ڴ��д�������ݴ���cachֻ�������ڴ���Ӱ�졣
                  (3)ÿ�η���YUV�ڴ�ᵼ�������½��ܶ࣬TC��Ҫ���ڴ�Ƚ�С�����Լ�ά��
                     ����ڴ棬�̶�����һ���ڴ棬������ʱ�����·��䡣��Ϊ��ʱ�������ٽ�
                     ��Դ����Ӱ�쵽���߳��Լ��û������ڴ����������ǵ�ͨ���Բ���ͳһά���ˡ�
                     �����ÿ����Դ�Ƕ����ģ�������ԴҪ�������ͨ����
                  (4)���������������ڴ沢��ӳ���cach��ʽ�ڴ�֮��Ҫˢһ��cach�����Բ��ó�ʼ����
                     ����cach����ǰ�Ĳ�����Ӱ�쵽�����ʹ��Ч��CNend\n
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162		    Created file      	
******************************************************************************/

/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "hi_jpeg_config.h"
#include  "jpeg_hdec_mem.h"
#include  "jpeg_hdec_api.h"
#include  "jpeg_hdec_error.h"

/***************************** Macro Definition ******************************/

/** the first class is jpeg */
/** CNcomment:��һ���ڴ�Ϊjpeg���� */
#define MMZ_TAG          "jpeg"
/** the second class is jpeg */
/** CNcomment:�ڶ����ڴ�Ϊgraphics���� */
//#define MMZ_TAG_1        "graphics"
/** the last class is jpeg */
/** CNcomment:���һ���ڴ�Ϊ����MMZ���� */
//#define MMZ_TAG_2        ""

/** the module name */
/** CNcomment:�����jpegģ������֣��������ͨ��mmz proc���鿴�����˭�� */
#define MMZ_MODULE       "JPEG_STREAM_OUT_BUF"


#if defined(CONFIG_JPEG_ANDROID_DEBUG_ENABLE) && defined(CONFIG_JPEG_DEBUG_INFO)
#define LOG_TAG    "libjpeg"
#endif

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/


/*****************************************************************************
* func			: JPEG_HDEC_GetStreamMem
* description	: alloc the stream buffer mem
                  CNcomment: ��������buffer�ڴ� CNend\n
* param[in] 	: u32MemSize   CNcomment: Ҫ������ڴ��С    CNend\n
* param[out]	: pOutPhyAddr  CNcomment: ����õ��������ַ  CNend\n
* param[out]	: pOutVirAddr  CNcomment: ����õ��������ַ  CNend\n
* retval		: HI_SUCCESS   CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE   CNcomment: ʧ��   CNend\n
* others:		: NA
*****************************************************************************/
#ifdef CONFIG_JPEG_REALIZEFUNC_BEFORMAINFUNC
HI_S32	JPEG_HDEC_GetStreamMem(const HI_U32 u32MemSize,HI_CHAR **pOutPhyAddr,HI_CHAR **pOutVirAddr)
#else
HI_S32	JPEG_HDEC_GetStreamMem(JPEG_HDEC_HANDLE_S_PTR	 pJpegHandle,const HI_U32 u32MemSize)
#endif
{


		HI_CHAR *pPhyBuf = NULL;
		HI_CHAR *pVirBuf = NULL;
		HI_U32 u32StreamSize = JPGD_STREAM_BUFFER;

		JPEG_ASSERT((0 == u32MemSize),HI_FAILURE);

		if(u32StreamSize < 4096)/*lint !e774 ignore by y00181162, because this cast is ok */  
		{
			JPEG_TRACE("the save stream size is small than the input buffer size\n");
			return HI_FAILURE;
		}
		/**
		** use the third class manage to alloc mem,the stream buffer should 64bytes align
		** CNcomment: ʹ��������������������ڴ� CNend\n
		**/
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pPhyBuf = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize, JPGD_HDEC_MMZ_ALIGN_64BYTES, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
        #else
		pPhyBuf = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_ALIGN_64BYTES, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
        #endif
		if(NULL == pPhyBuf)
		{
			JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
	    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pVirBuf = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(HI_U32)pPhyBuf);
        #else
		pVirBuf = (HI_CHAR*)HI_GFX_MapCached((HI_U32)pPhyBuf);
        #endif
		if(NULL == pVirBuf)
		{
			JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
			return HI_FAILURE;
		}
#if 0
		/**
		** when use this mem, should memset this mem
		** CNcomment: ��ʹ�ø��ڴ�ĵ�ַ��ʼ�����ڴ棬memset��Ҫʱ�䣬ʹ��������� CNend\n
		**/
		memset(pVirAddr,0,u32MemSize);
		HI_GFX_Flush((HI_U32)pPhyBuf);
#endif


#ifdef CONFIG_JPEG_REALIZEFUNC_BEFORMAINFUNC
		*pOutPhyAddr = pPhyBuf;
		*pOutVirAddr = pVirBuf;
#else
		pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf      = pPhyBuf;
		pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf      = pVirBuf;
		/**
		** use the virtual memory, every time should read data size
		** CNcomment: �����ڴ�������ʱ��ÿ����Ҫ��ȡ��������С CNend\n
		**/
		pJpegHandle->stHDecDataBuf.u32ReadDataSize	      = u32StreamSize;
#endif


		return HI_SUCCESS;

		
}



/*****************************************************************************
* func			: JPEG_HDEC_FreeStreamMem
* description	: free the stream buffer mem
                  CNcomment: �ͷ�����buffer�ڴ� CNend\n
* param[in] 	: pInPhyAddr    CNcomment: Ҫ�ͷŵ�����buffer�����ַ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
#ifdef CONFIG_JPEG_REALIZEFUNC_BEFORMAINFUNC
HI_VOID JPEG_HDEC_FreeStreamMem(HI_CHAR *pInPhyAddr)
#else
HI_VOID JPEG_HDEC_FreeStreamMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
#endif
{

       HI_S32 s32Ret = HI_SUCCESS;
	   
#ifdef CONFIG_JPEG_REALIZEFUNC_BEFORMAINFUNC
	  if(NULL == pInPhyAddr)
	  {
	     return;
	  }
	  s32Ret = HI_GFX_Unmap((HI_U32)pInPhyAddr);
	  s32Ret = HI_GFX_FreeMem((HI_U32)pInPhyAddr);
	  if(HI_SUCCESS != s32Ret)
	  {
	     return;
	  }
#else

      if(NULL == pJpegHandle)
      {
           JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
		   return;
      }
	  
	  if( NULL == pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf)
	  {
		   return;
	  }
	  #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
	  s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  #else
	  s32Ret = HI_GFX_Unmap((HI_U32)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  s32Ret = HI_GFX_FreeMem((HI_U32)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  #endif
	  if(HI_SUCCESS != s32Ret)
	  {
	      JPEG_TRACE("HI_GFX_Unmap or  HI_GFX_FreeMem FAILURE\n");
	      return;
	  }
	  pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf	    = NULL;
	  pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf	    = NULL;
#endif
	  
}


/*****************************************************************************
* func			: JPEG_HDEC_GetYUVMem
* description	: get the hard decode output mem
				  CNcomment: ��ȡӲ������������ڴ� CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: HI_SUCCESS	CNcomment: �ɹ� CNend\n
* retval		: HI_FAILURE	CNcomment: ʧ�� CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetYUVMem(JPEG_HDEC_HANDLE_S_PTR	pJpegHandle)
{


		HI_U32 u32MemSize = 0;
		HI_CHAR *pYUVPhy  = NULL;
		HI_CHAR *pYUVVir  = NULL;
		HI_U32 u32Align   = 0;
		HI_S32 s32Ret = HI_SUCCESS;
		/**
		 ** check whether to alloc jpeg hard decode middle mem
		 ** CNcomment: �ж��Ƿ����Ӳ��������м�buffer CNend\n
		 **/
#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE == pJpegHandle->bDecARGB)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))
#else
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))	
#endif
		{/**
		  ** use user mem
		  ** CNcomment: ʹ���û��ڴ� CNend\n
		  **/
		      pJpegHandle->stMiddleSurface.pMiddlePhy[0] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[0];
		      pJpegHandle->stMiddleSurface.pMiddlePhy[1] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[1];
			  pJpegHandle->stMiddleSurface.pMiddlePhy[2] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[2];
		      pJpegHandle->stMiddleSurface.pMiddleVir[0] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		      pJpegHandle->stMiddleSurface.pMiddleVir[1] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];
			  pJpegHandle->stMiddleSurface.pMiddleVir[2] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[2];
		      return HI_SUCCESS;
		}


#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB)
		{
		  /**
		   ** 4bytes align just ok
		   ** CNcomment: 4�ֽڶ���Ϳ����� CNend\n
		   **/
		   u32Align   = JPGD_HDEC_MMZ_ALIGN_4BYTES;
		   u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize;
		}
		else
#endif
		{
		   u32Align   = JPGD_HDEC_MMZ_ALIGN_128BYTES;
		   u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize + pJpegHandle->stJpegSofInfo.u32CSize;
		}
		/**
		 ** use the third class manage to alloc mem,the stream buffer should 128bytes align
		 ** CNcomment: ʹ��������������������ڴ�,bufferҪ128�ֽڶ��� CNend\n
		 **/
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pYUVPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
		#else
		pYUVPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
		#endif
		if(NULL == pYUVPhy)
		{
		     JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
		     return HI_FAILURE;
		}

#ifndef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
/** if need save yuvsp data,should virtual address **/
		#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bDecARGB))
		#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
		#endif
#endif
		{
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			pYUVVir = (HI_CHAR *)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(HI_U32)pYUVPhy);
			#else
			pYUVVir = (HI_CHAR *)HI_GFX_MapCached((HI_U32)pYUVPhy);
			#endif
			if (NULL == pYUVVir)
			{
				JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
				return HI_FAILURE;
			}
			/**
			** when use this mem, should memset this mem
			** CNcomment: ��ʹ�ø��ڴ�ĵ�ַ��ʼ�����ڴ棬memset��Ҫʱ�䣬ʹ��������� CNend\n
			**/
			//memset(pYUVVir,0,u32MemSize);
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(HI_U32)pYUVPhy);
			#else
			s32Ret = HI_GFX_Flush((HI_U32)pYUVPhy);
			#endif
			if(HI_SUCCESS != s32Ret)
			{
				return HI_FAILURE;
			}
			pJpegHandle->stMiddleSurface.pMiddleVir[0] = pYUVVir;
			pJpegHandle->stMiddleSurface.pMiddleVir[1] = pYUVVir + pJpegHandle->stJpegSofInfo.u32YSize;
			
		}

		pJpegHandle->stMiddleSurface.pMiddlePhy[0] = pYUVPhy;
		pJpegHandle->stMiddleSurface.pMiddlePhy[1] = pYUVPhy + pJpegHandle->stJpegSofInfo.u32YSize;
		 
		return HI_SUCCESS;


}

/*****************************************************************************
* func			: JPEG_HDEC_FreeYUVMem
* description	: free the hard decode output mem
				  CNcomment: �ͷ�Ӳ����������ĵ�ַ  CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

		HI_S32 s32Ret = HI_SUCCESS;


		if(NULL == pJpegHandle)
		{
			JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
			return;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP || (HI_TRUE == pJpegHandle->bDecARGB))
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))
#else
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))

#endif
		{/**
		** use user mem
		** CNcomment: ʹ���û��ڴ� CNend\n
		**/
			return;
		}

		if(NULL == pJpegHandle->stMiddleSurface.pMiddlePhy[0])
		{
			return;
		}

#ifndef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
		#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bDecARGB))
		#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
		#endif
#endif
		{
		    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		    s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
			#else
			s32Ret = HI_GFX_Unmap((HI_U32)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
			#endif
			if(HI_SUCCESS != s32Ret)
			{
				JPEG_TRACE("HI_GFX_Unmap FAILURE\n");
				return;
			}
		}

		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
		#else
		s32Ret = HI_GFX_FreeMem((HI_U32)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			JPEG_TRACE("HI_GFX_FreeMem FAILURE\n");
			return;
		}
		pJpegHandle->stMiddleSurface.pMiddlePhy[0]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddlePhy[1]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddleVir[0]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddleVir[1]  = NULL;
					
}


#ifdef CONFIG_JPEG_HARDDEC2ARGB
/*****************************************************************************
* func			: JPEG_HDEC_GetMinMem
* description	: get dec output argb min memory
				  CNcomment: ��ȡӲ���������ΪARGB����buffer CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: HI_SUCCESS	CNcomment: �ɹ� CNend\n
* retval		: HI_FAILURE	CNcomment: ʧ�� CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

		HI_U32 u32MemSize = 0;
		HI_CHAR *pMinPhy  = NULL;

   		u32MemSize = pJpegHandle->stJpegSofInfo.u32RGBSizeReg;

		/**
	 	 ** use the third class manage to alloc mem,the min buffer should 128bytes align
	     ** CNcomment: ʹ��������������������ڴ�,argb��bufferҪ128�ֽڶ��� CNend\n
	     **/
	    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
        pMinPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize,JPGD_HDEC_MMZ_ALIGN_128BYTES,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
        #else
		pMinPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize,JPGD_HDEC_MMZ_ALIGN_128BYTES,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
		#endif
		if(NULL == pMinPhy)
		{
		     JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			 return HI_FAILURE;
		}

		pJpegHandle->pMinPhyBuf   =   pMinPhy;
			
		return HI_SUCCESS;


}

/*****************************************************************************
* func			: JPEG_HDEC_FreeMinMem
* description	: free dec output argb min memory
				  CNcomment: �ͷ�Ӳ���������ΪARGB����buffer  CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

	    HI_S32 s32Ret = HI_SUCCESS;

		if(NULL == pJpegHandle)
		{
			 JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
			 return;
		}

		if(NULL == pJpegHandle->pMinPhyBuf)
		{
		   return;
		}
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->pMinPhyBuf);
		#else
        s32Ret = HI_GFX_FreeMem((HI_U32)pJpegHandle->pMinPhyBuf);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
		   JPEG_TRACE("HI_GFX_FreeMem FAILURE\n");
		   return;
		}
				
		pJpegHandle->pMinPhyBuf  = NULL;

}
#endif


/*****************************************************************************
* func			: JPEG_HDEC_GetOutMem
* description	: get the output buffer
				  CNcomment: ��������������ڴ� 	 CNend\n
* param[in]	    : cinfo         CNcomment: �������  CNend\n
* retval		: HI_SUCCESS    CNcomment: �ɹ�		  CNend\n
* retval		: HI_FAILURE    CNcomment: ʧ��		  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetOutMem(const struct jpeg_decompress_struct *cinfo)
{


		HI_U32 u32OutStride = 0;
		HI_U32 u32MemSize   = 0;
		HI_CHAR* pOutPhy    = NULL;
		HI_CHAR* pOutVir    = NULL;
        HI_S32 s32Ret = HI_SUCCESS;
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if(HI_TRUE == pJpegHandle->stOutDesc.bCrop)
		{
			pJpegHandle->stJpegSofInfo.u32DisplayStride = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0];
		}

#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE  == pJpegHandle->bDecARGB)
#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
#endif
		{
		/**
		** shoule not csc,so not alloc output mem
		** CNcomment: ����Ҫ��ɫ�ռ�ת�������ԾͲ���Ҫ�������buffer CNend\n
		**/
			return HI_SUCCESS;
		}

		if(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		{  
		/**
		** use user mem
		** CNcomment: ʹ���û��ڴ� CNend\n
		**/
			pJpegHandle->stMiddleSurface.pOutPhy = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[0];
			pJpegHandle->stMiddleSurface.pOutVir = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
			return HI_SUCCESS;
		}
		u32OutStride = pJpegHandle->stJpegSofInfo.u32DisplayStride;
		u32MemSize   = u32OutStride * ((HI_U32)pJpegHandle->stOutDesc.stCropRect.h);
		
		/**
		** align depend the pixle
		** CNcomment: �������ض��� CNend\n
		**/
		/** 3�ֽڶ�����������ģ���Ϊmap������**/
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pOutPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize, JPGD_HDEC_MMZ_ALIGN_16BYTES, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
        #else
		pOutPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_ALIGN_16BYTES, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
		#endif
		if(0 == pOutPhy)
		{
			JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pOutVir = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(HI_U32)pOutPhy);
		#else
		pOutVir = (HI_CHAR*)HI_GFX_MapCached((HI_U32)pOutPhy);
		#endif
		if (NULL == pOutVir)
		{
			JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
			return HI_FAILURE;
		}
		/** memset Ҳ��Ҫ��ʱ�䣬������������Ͳ�Ҫmemset������ **/
		//memset(pOutVir,0,u32MemSize);
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(HI_U32)pOutPhy);
        #else
		s32Ret = HI_GFX_Flush((HI_U32)pOutPhy);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			return HI_FAILURE;
		}
		/**
		** Ҫ���û�û���������ͼ���С���ʹ��Ĭ�ϵ������Ҳ����ֻ��1/2/4/8��������
		**/
		pJpegHandle->stMiddleSurface.pOutPhy   =  pOutPhy;
		pJpegHandle->stMiddleSurface.pOutVir   =  pOutVir;

		return HI_SUCCESS;

		
}

/*****************************************************************************
* func			: JPEG_HDEC_FreeOutMem
* description	: free the output buf
				  CNcomment: �ͷ�����������ڴ� 	   CNend\n
* param[in]	    : pJpegHandle   CNcomment: ���������  CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeOutMem(JPEG_HDEC_HANDLE_S_PTR	 pJpegHandle)
{

		HI_S32 s32Ret = HI_SUCCESS;

		if(NULL == pJpegHandle)
		{
				JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
				return;
		}
#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE  == pJpegHandle->bDecARGB)
#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
#endif
		{
			return;
		}

		if(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		{   
			return;
		}


		if(NULL == pJpegHandle->stMiddleSurface.pOutPhy)
		{
			return;
		}
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stMiddleSurface.pOutPhy );
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(HI_U32)pJpegHandle->stMiddleSurface.pOutPhy);
		#else
		s32Ret = HI_GFX_Unmap((HI_U32)pJpegHandle->stMiddleSurface.pOutPhy );
		s32Ret = HI_GFX_FreeMem((HI_U32)pJpegHandle->stMiddleSurface.pOutPhy);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			JPEG_TRACE("HI_GFX_Unmap or HI_GFX_FreeMem FAILURE\n");
			return;
		}
		pJpegHandle->stMiddleSurface.pOutPhy  = NULL;
		pJpegHandle->stMiddleSurface.pOutVir  = NULL; 

}
