/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_venc.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/04/07
  Description   :
  History       :
  1.Date        : 2010/04/07
    Author      : j00131665
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief Describes the information about video encoding (VENC). CNcomment: �ṩVENC�������Ϣ CNend
 */

#ifndef  __HI_UNF_VENC_H__
#define  __HI_UNF_VENC_H__

#include "hi_unf_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/********************************Struct Definition********************************/
/** \addtogroup      VENC */
/** @{ */  /** <!-- ��VENC�� */

/**H.264 NALU type*/
/**CNcomment: H.264NALU���� */
typedef enum hiUNF_H264E_NALU_TYPE_E
{
    HI_UNF_H264E_NALU_PSLICE = 1,       /**<P slice NALU*/ 
    HI_UNF_H264E_NALU_ISLICE = 5,       /**<I slice NALU*/ 
    HI_UNF_H264E_NALU_SEI = 6,          /**<SEI NALU*/ 
    HI_UNF_H264E_NALU_SPS = 7,          /**<SPS NALU*/
    HI_UNF_H264E_NALU_PPS = 8,          /**<PPS NALU*/ 
    HI_UNF_H264E_NALU_BUTT
} HI_UNF_H264E_NALU_TYPE_E;

/**H.263 NALU type*/
/**CNcomment: H.263NALU���� */
typedef enum hiUNF_H263E_PACK_TYPE_E
{
    HI_UNF_H263E_NALU_PSLICE = 1,       /**<P slice NALU*/
    HI_UNF_H263E_NALU_ISLICE = 5,       /**<I slice NALU*/
    HI_UNF_H263E_NALU_SEI = 6,          /**<SEI NALU*/
    HI_UNF_H263E_NALU_SPS = 7,          /**<SPS NALU*/
    HI_UNF_H263E_NALU_PPS = 8,          /**<PPS NALU*/
    HI_UNF_H263E_NALU_BUTT
} HI_UNF_H263E_PACK_TYPE_E;

/**MPEG4 package type*/
/**CNcomment: MPEG4������� */
typedef enum hiUNF_MPEG4E_PACK_TYPE_E
{
    HI_UNF_MPEG4E_PACK_VO = 1,          /**<VO package*/ /**<CNcomment: VO ��*/
    HI_UNF_MPEG4E_PACK_VOS = 2,         /**<VOS package*/ /**<CNcomment: VOS ��*/
    HI_UNF_MPEG4E_PACK_VOL = 3,         /**<VOL package*/ /**<CNcomment: VOL ��*/
    HI_UNF_MPEG4E_PACK_VOP = 4,         /**<VOP package*/ /**<CNcomment: VOP ��*/
    HI_UNF_MPEG4E_PACK_SLICE = 5        /**<Slice package*/ /**<CNcomment: SLICE ��*/	
} HI_UNF_MPEG4E_PACK_TYPE_E;

/**Data type of the Encoder*/
/**CNcomment: �������������� */
typedef union hiUNF_VENC_DATA_TYPE_U
{
    HI_UNF_H264E_NALU_TYPE_E   enH264EType;	/**<H.264 encoding data*/ /**<CNcomment: h264��������*/	
    HI_UNF_H263E_PACK_TYPE_E   enH263EType;	/**<H.263 encoding data*/ /**<CNcomment: h263��������*/	
    HI_UNF_MPEG4E_PACK_TYPE_E  enMPEG4EType;    /**<MPEG4 encoding data*/ /**<CNcomment: MPEG4��������*/		
}HI_UNF_VENC_DATA_TYPE_U;

/*Output stream attributes structure*/
/**CNcomment: ����������Խṹ�� */
typedef struct hiVENC_STREAM_S
{
    HI_U8                   *pu8Addr ;       /**<Stream virtual address*/ /**<CNcomment: ���������ַ*/	
    HI_U32                  u32SlcLen ;      /**<Stream length*/ /**<CNcomment: ��������*/		
    HI_U32                  u32PtsMs;        /**<Presentation time stamp (PTS), in ms*/ /**<CNcomment: ʱ�������λ�Ǻ���*/
    HI_BOOL                 bFrameEnd;       /**<Frame end or not*/ /**<CNcomment: ��ʶ�Ƿ�Ϊ֡����*/
    HI_UNF_VENC_DATA_TYPE_U enDataType;      /**Encoding data type*/ /**<CNcomment: ������������*/
}HI_UNF_VENC_STREAM_S;

/*Coding channal attributes structure*/
/**CNcomment: ����ͨ�����Խṹ�� */
typedef struct hiUNF_VENC_CHN_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E        enVencType;	      /**<Encoder type*/ /**<CNcomment: ���������� */
    HI_UNF_VCODEC_CAP_LEVEL_E   enCapLevel;       /**<Encoder level*/ /**<CNcomment: �������������� */
    HI_U32                      u32Width;         /**<Width, 16-byte aligned. The width cannot be configured dynamically.*/ /**<CNcomment: ���,��֧�ֶ�̬����  */
    HI_U32                      u32Height;        /**<Height, 16-byte aligned. The height cannot be configured dynamically.*/ /**<CNcomment: �߶�,��֧�ֶ�̬���� */
    HI_U32                      u32StrmBufSize;	  /**<Stream buffer size*/ /**<CNcomment: ����buffer��С,���õ�����buffer��СҪ>=����ͨ����*��*2 */
    HI_U32                      u32RotationAngle; /**<Rotation angle. This parameter cannot be set.*/ /**<CNcomment: ��ת�Ƕ�,��Ч����  */
    HI_BOOL                     bSlcSplitEn;      /**<Slice split enable*/ /**<CNcomment: �Ƿ�ʹ�ָܷ�slice */ 	
    HI_U32                      u32TargetBitRate; /**<RC parameter for the VENC. It can be set dynamically.*/ /**<CNcomment: Venc����RC����,�ɶ�̬���� */
    HI_U32                      u32TargetFrmRate; /**<Target frame rate. It can be set dynamically.*/         /**<CNcomment: Ŀ��֡��,�ɶ�̬���� */ 
    HI_U32                      u32InputFrmRate;  /**<Input frame rate. It can be set dynamically. The value of u32TargetFrmRate is less than or equal to the value of u32InputFrmRate.*/ 
                                                  /**<CNcomment: ����֡��,�ɶ�̬����,u32TargetFrmRate <= u32InputFrmRate */ 
    HI_U32                      u32Gop;			  /**<GOP size. It can be set dynamically.*/ /**<CNcomment: GOP��С,�ɶ�̬���� */ 	
    HI_U32                      u32MaxQp;         /**<The maximum quantization parameter*/    /**<CNcomment: �����������*/	
    HI_U32                      u32MinQp;         /**<The minimum quantization parameter*/    /**<CNcomment: ��С��������*/	
    HI_BOOL			            bQuickEncode;     /**<Quick Encode Mode enable*/ /**<CNcomment:�Ƿ�ʹ�ܿ��ٱ���ģʽ*/
    HI_U8                       u8Priority;       /**<the Priority Level of the channal*/     /**<CNcomment: ����ͨ�������ȼ����ԣ�ȡֵ��ΧΪ0~���ͨ����*/
    
}HI_UNF_VENC_CHN_ATTR_S;

/** @} */  /** <!-- ==== Struct Definition End ==== */


/********************************API declaration********************************/
/** \addtogroup      VENC */
/** @{ */  /** <!-- ��VENC�� */

/** 
\brief Initializes the video encoder. CNcomment: ��ʼ����Ƶ������ CNend
\attention \n
Before using the VENC, you must call this API. CNcomment: ����VENCģ��Ҫ�����ȵ��øýӿ� CNend
\param[in] N/A CNcomment: �� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_DEV_NOT_EXIST No VENC device exists. CNcomment: �豸������ CNend
\retval ::HI_ERR_VENC_NOT_DEV_FILE The file is not a VENC file. CNcomment: �ļ����豸 CNend
\retval ::HI_ERR_VENC_DEV_OPEN_ERR The VENC device fails to start. CNcomment: ���豸ʧ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_Init(HI_VOID);


/** 
\brief Deinitializes the video encoder. CNcomment: ȥ��ʼ����Ƶ������ CNend
\attention \n
N/A CNcomment: �� CNend
\param[in] N/A CNcomment: �� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_DEV_CLOSE_ERR The video encoder fails to stop. CNcomment: �رձ�����ʧ�� CNend
\see \n
N/A CNcomment: ��  CNend
*/
HI_S32 HI_UNF_VENC_DeInit(HI_VOID);


/** 
\brief Obtains the default attributes of a VENC channel. CNcomment: ��ȡ����ͨ��Ĭ������ CNend
\attention \n
By default, the encoding size is D1, encoding format is H.264, and a frame is a slice.
CNcomment: Ĭ��D1���룬H.264��ʽ��һ֡Ϊһ��Slice CNend
\param[in] pstAttr Pointer to the attributes of a VENC channel. CNcomment: pstAttr ָ�����ͨ�����Ե�ָ�� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_NULL_PTR The input pointer parameter is null. CNcomment: ����ָ�����Ϊ��ָ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_GetDefaultAttr(HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief Creates a VENC channel. CNcomment: ������Ƶ����ͨ�� CNend
\attention \n
You must create a VENC channel before video encoding. 
CNcomment: ������Ƶ����Ҫ�����ȴ�������ͨ�� CNend
\param[in] phVenc Pointer to the handle of a VENC channel. CNcomment: phVenc ָ�����ͨ�������ָ�� CNend
\param[in] pstAttr Pointer to the attributes of a VENC channel. CNcomment: pstAttr ָ�����ͨ�����Ե�ָ�� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
\retval ::HI_ERR_VENC_NULL_PTR The input pointer parameter is null. CNcomment: ����ָ������п�ָ�� CNend
\retval ::HI_ERR_VENC_CREATE_ERR The number of VENC channels exceeds the limit. CNcomment: ����ͨ�������� CNend
\retval ::HI_ERR_VENC_INVALID_PARA The channel attributes are incorrect. CNcomment: ͨ���������ô��� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A
CNcomment: ��  CNend
*/
HI_S32 HI_UNF_VENC_Create(HI_HANDLE *phVenc,const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief Destroys a VENC channel. CNcomment: ������Ƶ����ͨ�� CNend
\attention \n
\param[in] hVenc Handle of a VENC channel. CNcomment: CNcomment: hVenc ����ͨ����� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No handle exists. CNcomment: ��������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A CNcomment: ��  CNend
*/
HI_S32 HI_UNF_VENC_Destroy(HI_HANDLE hVenc);


/** 
\brief Attaches a VENC channel to the video source. CNcomment: �󶨱���ͨ������ƵԴ CNend
\attention \n
You must call this API before performing encoding and obtaining streams. CNcomment: ��ʼ����ͻ�ȡ����֮ǰ��Ҫ���ȵ��øýӿ� CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] hSrc Data source handle CNcomment: hSrc ��ƵԴ��� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_INVALID_PARA The video source is invalid. CNcomment: ��ƵԴ����  CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_AttachInput(HI_HANDLE hVenc,HI_HANDLE hSrc);


/** 
\brief Detaches a VENC channel from the video source. CNcomment: �����ƵԴ CNend
\attention \n
You must stop encoding before calling this API.
CNcomment: ���øýӿ���Ҫ����ֹͣ���� CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] hSrc Data source handle CNcomment: hSrc ��ƵԴ��� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_INVALID_PARA The video source is invalid. CNcomment: ��ƵԴ���� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_CHN_INVALID_STAT The video encoder does not stop encoding. CNcomment: ������δֹͣ���� CNend
\see \n
N/A CNcomment: ��  CNend
*/
HI_S32 HI_UNF_VENC_DetachInput(HI_HANDLE hVencChn);


/** 
\brief Starts to perform encoding. CNcomment: ��ʼ���� CNend
\attention \n
You must initialize the video encoder, create a VENC channel, and attach the channel to the video source before calling this API.
CNcomment: ���øýӿ���Ҫ���ȳ�ʼ������������������ͨ��������ƵԴ CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_CHN_NO_ATTACH The VENC channel is not attached to the video source. CNcomment: ����ͨ��û�а󶨵���ƵԴ CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_Start(HI_HANDLE hVenc);


/** 
\brief Stops encoding. CNcomment: ֹͣ���� CNend
\attention \n
You must initialize the video encoder, create a VENC channel, attach the channel to the video source, and start to perform encoding before calling this API.
CNcomment: ���øýӿ���Ҫ���ȳ�ʼ������������������ͨ��������ƵԴ���Ѿ���ʼ���� CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_CHN_NO_ATTACH The VENC channel is not attached to the video source. CNcomment: ����ͨ��û�а󶨵���ƵԴ CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_Stop(HI_HANDLE hVenc);

/** 
\brief Obtains VENC streams. CNcomment: ��ȡ��Ƶ�������� CNend
\attention \n
You must attach a VENC channel to the video source and start to perform encoding before calling this API.
The block time (in ms) is configurable. If u32TimeOutMs is set to 0, the block time is 0; if u32TimeOutMs is set to 0xFFFFFFFF, it indicates infinite wait. \n
If the block time is reached but no data is received, ::HI_ERR_VENC_BUF_EMPTY is returned.\n
If the wait time is 0 and there is no data, ::HI_ERR_VENC_BUF_EMPTY is returned.\n
The non-block mode is not supported. You need to set u32TimeOutMs to 0, and call usleep(1) to release the CPU after HI_ERR_VENC_BUF_EMPTY is returned.
CNcomment: ���øýӿ���Ҫ���Ȱ���ƵԴ����ʼ����
����ʱ��������ã�ʱ�䵥λΪ���룬����Ϊ0���ȴ�������Ϊ0xffffffffһֱ�ȴ���\n
����������ʱ�䣬��û�����ݵ���򷵻�::HI_ERR_VENC_BUF_EMPTY\n
����ȴ�ʱ��Ϊ0����û���������ݣ��򷵻�::HI_ERR_VENC_BUF_EMPTY\n
��ʱ��֧�ַ�����ģʽ�����u32TimeOutMs����Ϊ0,�����ڴ˽ӿڷ���HI_ERR_VENC_BUF_EMPTY��ʱ�򣬵���usleep(10000)����CPU \n CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstStream Pointer to the structure for storing streams CNcomment: pstStream ��������ṹ��ָ�� CNend
\param[in] u32TimeoutMs: Wait timeout, count in ms CNcomment: u32TimeoutMs���ȴ���ʱʱ�䣬��λms CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_NULL_PTR The stream pointer is null. CNcomment: ����ָ��Ϊ�� CNend
\retval ::HI_ERR_VENC_CHN_NO_ATTACH The VENC channel is not attached to the video source. CNcomment: ����ͨ��û�а󶨵���ƵԴ CNend
\retval ::HI_ERR_VENC_BUF_EMPTY Streams fail to be obtained. CNcomment: ��ȡ����ʧ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_AcquireStream(HI_HANDLE hVenc,HI_UNF_VENC_STREAM_S *pstStream, HI_U32 u32TimeoutMs);


/** 
\brief Releases VENC streams. CNcomment: �ͷ���Ƶ�������� CNend
\attention \n
You must obtain streams and keep the streams unchanged before calling this API.
CNcomment: ���øýӿ���Ҫ���Ȼ�ȡ�������Ҳ��ܸı��������� CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstStream Pointer to the structure for storing streams CNcomment: pstStream ��������ṹ��ָ�� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_NULL_PTR The stream pointer is null. CNcomment: ����ָ��Ϊ�� CNend
\retval ::HI_ERR_VENC_CHN_NO_ATTACH The VENC channel is not attached to the video source. CNcomment: ����ͨ��û�а󶨵���ƵԴ CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_ReleaseStream(HI_HANDLE hVenc, const HI_UNF_VENC_STREAM_S *pstStream);


/** 
\brief Sets the encoding channel attributes dynamically. CNcomment: ��̬���ñ���ͨ������ CNend
\attention \n
You must create a VENC channel before calling this API.
CNcomment: ���øýӿ���Ҫ���ȴ�������ͨ�� CNend
\param[in] Venc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstAttr Pointer to the attributes of a VENC channel CNcomment: pstAttr ��ű���ͨ�����Ե�ָ�� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_NULL_PTR The pointer is null. CNcomment: ָ��Ϊ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_SetAttr(HI_HANDLE hVenc,const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief Obtains the attributes of a VENC channel. CNcomment: ��ȡ����ͨ������ CNend
\attention \n
You must create a VENC channel before calling this API.
CNcomment: ���øýӿ���Ҫ���ȴ�������ͨ�� CNend
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstAttr Encoding channel attribute CNcomment: pstAttr ����ͨ������ CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\retval ::HI_ERR_VENC_NULL_PTR The pointer is null. CNcomment: ָ��Ϊ�� CNend
\see \n 
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_GetAttr(HI_HANDLE hVenc, HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief Applies for I frames. CNcomment: ����I֡ CNend
\attention \n
The video encoder encodes an I frame as soon as possible after you call this API.\n
You can call this API when you set up a video call or fix errors.\n
If you call this API repeatedly in a short period, I frames may be not generated each time.\n
CNcomment: ���øýӿں󣬱������ᾡ������һ��I֡��.\n
�˽ӿ�һ�����ڿ��ӵ绰������ͨ�������ʹ���ָ�.\n
�˽ӿ�ֻ��"���������"��������һ��I֡��������ڶ�ʱ���ڶ�ε��ô˽ӿڣ���ô���ܱ�֤ÿ�ε��ö��ܶ�Ӧ�����һ��I֡��.\n CNend
\param[in] hVencChn Handle of a VENC channel CNcomment: hVencChn ����ͨ����� CNend
\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_NO_INIT The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_RequestIFrame(HI_HANDLE hVencChn);



/** 
\brief Input frame to VENC. CNcomment: ���������֡ CNend
\attention \n
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstFrameinfo Frame information struct CNcomment: ֡��Ϣ���� CNend
\retval ::HI_SUCCESS                      Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST       No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_INVALID_PARA        The video source is invalid. CNcomment: ��ƵԴ���� CNend
\retval ::HI_ERR_VENC_NO_INIT             The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_QueueFrame(HI_HANDLE hVenc, HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo);


/** 
\brief release frame from VENC. CNcomment: ���������֡ CNend
\attention \n
\param[in] hVenc Handle of a VENC channel CNcomment: hVenc ����ͨ����� CNend
\param[in] pstFrameinfo Frame information struct CNcomment: ֡��Ϣ���� CNend
\retval ::HI_SUCCESS                       Success CNcomment: �ɹ� CNend
\retval ::HI_ERR_VENC_CHN_NOT_EXIST        No VENC channel handle exists. CNcomment: ����ͨ����������� CNend
\retval ::HI_ERR_VENC_INVALID_PARA         The video source is invalid. CNcomment: ��ƵԴ���� CNend
\retval ::HI_ERR_VENC_NO_INIT              The video encoder is not initialized. CNcomment: ������δ��ʼ�� CNend
\see \n
N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_VENC_DequeueFrame(HI_HANDLE hVenc, HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo);

/** @} */  /** <!-- ==== API Declaration End ==== */
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif//__HI_UNF_VENC_H__

