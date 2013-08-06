/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : hi_jpeg_api.h
Version		    : Initial Draft
Author		    : 
Created		    : 2011/05/12
Description	    : JPEG6B application interface
Function List 	: HI_JPEG_SetMemMode
			    : HI_JPEG_GetMemMode
			    : HI_JPEG_BeginSuspend
			    : HI_JPEG_EndSuspend

			  		  
History       	:
Date				Author        		Modification
2011/05/11		            		    Created file      	
******************************************************************************/

#ifndef __HI_JPEG_API_H__
#define __HI_JPEG_API_H__





/*********************************add include here******************************/



#include "jpeglib.h"
#include "hi_type.h"


/*****************************************************************************/


#ifdef __cplusplus
      #if __cplusplus
   
extern "C" 
{

      #endif
#endif /* __cplusplus */

    /***************************** Macro Definition ******************************/

    #define NEED_ADDR_BLOCK_NUM   2
    #define NEED_STRIDE_BLOCK_NUM   2

    /*************************** Structure Definition ****************************/

    /**
	 ** �������������Ӧ�ò��Լ���װ��������ʽ 
	 ** ���ְ취�������ʱ����Ӧ�ò�ʹ�ñ�׼�Ķ������ӿ�
	 ** �ڶ���: �ⲿ���������ο��ڲ�������������α���������Ϣ���ָ�
	 ** ��ΪӦ�ò���������ֽ������������ڲ�ֻ����4096���ֽڣ�����Ҫע��
	 **/
	#if 1
	#define USE_EXTERN_STREAM
    #endif
	
    /***************************  The enum of Jpeg image format  ******************/

	typedef struct hiJPEG_APP_MESSAGE_S
	{

         /** u32OutPhyAddr[0]is RGB or YCbCr physical address
          **/
         HI_U32 u32OutPhyAddr[NEED_ADDR_BLOCK_NUM];
		 HI_U32 *pu32OutVirAddr[NEED_ADDR_BLOCK_NUM];/** extend use **/
		 
         
         /** s32OutStride[0]is RGB or Y stride, and s32OutStride[1] is c stride **/
         HI_S32 s32OutStride[NEED_STRIDE_BLOCK_NUM];

	}HI_JPEG_APP_MESSAGE_S;

    /** �������� **/
    typedef enum hiJPEG_STREAM_TYPE_E
    {

        STREAM_TYPE_INTER_FILE    = 0,   /** ʹ�ñ�׼���ļ��ӿ� **/
        STREAM_TYPE_INTER_STREAM  = 1,   /** ʹ�ñ�׼������ **/
        #ifdef USE_EXTERN_STREAM
        STREAM_TYPE_EXTERN_FILE   = 2,   /** ʹ���ⲿ���ļ��ӿ� **/
        STREAM_TYPE_EXTERN_STREAM = 3,   /** ʹ���ⲿ������ **/
        #endif
        STREAM_TYPE_BUTT
        
    }HI_JPEG_STREAM_TYPE_E;

	/** ������Ϣ״̬ **/
	typedef struct hiJPEG_HDEC_TO_SDEC_S
	{
	
     	 /** ====================Ӳ�ⲻ�ɹ����˵����Ĺ���=================== **/
		 /** �ж��Ƕ��ļ��������� **/
		 HI_JPEG_STREAM_TYPE_E eReadStreamType;
		 /** ��ǰ�������ļ�λ�� **/
		 HI_S32 s32FilePos;
		 /** ��ǰ������λ�� **/
		 HI_S32 s32StreamPos;
		  /** ʣ���������  **/
		 HI_S32 s32LeaveByte;
		 /** ʣ������ **/
		 HI_CHAR* pLeaveBuf;
         /** Ӳ���Ƿ�ɹ� **/
		 HI_BOOL bHDECSuc;

	}HI_JPEG_HDEC_TO_SDEC_S,*HI_JPEG_HDEC_TO_SDEC_S_PTR;
	
    /********************** Global Variable declaration **************************/



    /******************************* API declaration *****************************/

	/*****************************************************************************
	* func                     : HI_JPEG_GetVersion
	* description:
	* param[in] :ppVersion
	* param[in] :ppBuildTime
	* retval    :HI_SUCCESS    : success
	* retval    :HI_FAILURE    : failure
	* others:	:nothing
	*****************************************************************************/
	HI_S32 HI_JPEG_GetVersion(HI_CHAR **ppVersion, HI_CHAR **ppBuildTime);

    /*****************************************************************************
    * func                     : set the input memory mode
    * description: if users did not call this function, default use virtual address.
    *              and if users want use physical address mode, should call this function.
    * param[in] :cinfo         : decompress object
    * param[in] :pstAppMessage : HI_JPEG_APP_MESSAGE_S struct
    * param[in] :scanlines
    * retval    :HI_SUCCESS    : success
    * retval    :HI_FAILURE    : failure
    * others:	:nothing
    *****************************************************************************/

    HI_S32 HI_JPEG_SetMemMode(j_decompress_ptr cinfo,HI_JPEG_APP_MESSAGE_S pstAppMessage);





    /*****************************************************************************
    * func                     : get the input memory mode
    * param[in] :cinfo         : decompress object
    * param[in] :pstAppMessage : 
    * retval    :HI_SUCCESS    : success
    * retval    :HI_FAILURE    : failure
    * others:	:nothing
    *****************************************************************************/

    HI_S32 HI_JPEG_GetMemMode(j_decompress_ptr cinfo,HI_JPEG_APP_MESSAGE_S *pstAppMessage);

    /*****************************************************************************
    * func                     : HI_JPEG_BeginSuspend
    * param[in] : 
    * param[in] :
    * retval    :HI_SUCCESS    : success
    * retval    :HI_FAILURE    : failure
    * others:	:nothing
    *****************************************************************************/

    HI_S32 HI_JPEG_BeginSuspend();

    /*****************************************************************************
    * func                     : HI_JPEG_End_Suspend
    * param[in] :
    * retval    :HI_SUCCESS    : success
    * retval    :HI_FAILURE    : failure
    * others:	:nothing
    *****************************************************************************/

    HI_S32 HI_JPEG_EndSuspend();

	/*****************************************************************************
	* func                     : HI_JPEG_ForceDecodeType
	*                          if users only use soft or hard decode, user can
	                           call this function.
	* param[in] :cinfo         : decompress object
	* param[in] :SoftOrHard    : ture = use soft decode
	                             false = use hard decode
    * retval    :HI_SUCCESS    : success
    * retval    :HI_FAILURE    : failure
	* others:	:nothing
	*****************************************************************************/
    HI_S32 HI_JPEG_ForceDecodeType(j_decompress_ptr cinfo,HI_BOOL SoftOrHard);


	/*****************************************************************************
	* func        : hi_get_dec_state
	* description : ��ȡӲ������״̬,����ǽӿ������û��Լ�����������ʱ��ʹ��,
	                ����ʵ�ڵ��ý���֮�����,�Ӷ������Ƿ���Ҫ���µ���һ�ν���.
	                HI_FALSE����Ҫ���µ���һ��.
	* param[in]   : 
	* param[in]   :
	* param[in]   :
	* others:	  : nothing
	*****************************************************************************/
	HI_VOID hi_get_dec_state(HI_BOOL *bHDEC,j_decompress_ptr cinfo);

	#ifdef USE_EXTERN_STREAM

   /*****************************************************************************
	* func        : hi_set_read_stream_type
	* description : ���ö�������ʽ,���粻ʹ�ñ�׼��,�ڵ���jpeg_start_decompress֮ǰ
	                ���øýӿ�,Ҫ��û�е��øýӿ����ⲿ��������ʽĬ��Ӳ��ʧ�ܾͲ�����
	* param[in]   : 
	* param[in]   :
	* param[in]   :
	* others:	  : nothing
	*****************************************************************************/
	HI_VOID hi_set_read_stream_type(const HI_JPEG_HDEC_TO_SDEC_S stInfo,\
	                                            j_decompress_ptr cinfo);

    #endif
    
    /****************************************************************************/
    #ifdef __cplusplus
    
        #if __cplusplus


      
}
      
        #endif
        
   #endif /* __cplusplus */

#endif /* __HI_JPEG_API_H__*/
