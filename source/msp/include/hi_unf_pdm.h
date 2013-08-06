/******************************************************************************

  Copyright (C), 2011-2021, HiSilicon Technologies Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_pdm.h
  Version       : Initial Draft
  Author        : HiSilicon multimedia software group
  Created       : 2011-xx-xx
  Description   : hi_unf_pdm.h header file
  History       :
  1.Date        : 2011/xx/xx
    Author      : 
    Modification: This file is created.

******************************************************************************/

#ifndef __HI_UNF_PDM_H__
#define __HI_UNF_PDM_H__

#include "hi_unf_common.h"
#include "hi_unf_mce.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      PDM */
/** @{ */  /** <!-- [PDM] */

/**Defines the base config parameter*/
/** CNcomment:基本配置参数结构体*/
typedef struct hiUNF_PDM_DISP_PARAM_S
{
    HI_UNF_ENC_FMT_E            enFormat;           /**<Format*//**<CNcomment: 制式*/
    HI_U32                      u32Brightness;      /**<Brightness*//**<CNcomment: 亮度*/ 
    HI_U32                      u32Contrast;        /**<Contrast*//**<CNcomment: 对比度*/ 
    HI_U32                      u32Saturation;      /**<Saturation*//**<CNcomment: 饱和度*/
    HI_U32                      u32HuePlus;         /**<HuePlus*//**<CNcomment: 色度*/
    HI_BOOL                     bGammaEnable;       /**<Is Gamma enable*//**<CNcomment: 是否使能gamma*/   
    HI_UNF_DISP_BG_COLOR_S      stBgColor;          /**<Background Color*//**<CNcomment: 背景色*/
    HI_UNF_DISP_INTF_S          stIntf[HI_UNF_DISP_INTF_TYPE_BUTT];     /**<configuration of display interface*//**<CNcomment: 显示接口配置*/
    HI_UNF_DISP_TIMING_S        stDispTiming;       /**<Display timeing*//**<CNcomment: 显示时序*/
	
    HIGO_PF_E                   enPixelFormat;      /**<Pixel format*//**<CNcomment: 像素格式*/
    HI_U32                      u32DisplayWidth;    /**<Width of the display buffer of a graphics layer.*//**<CNcomment: 图层的显示buffer宽度*/
    HI_U32                      u32DisplayHeight;   /**<Height of the display buffer of a graphics layer.*//**<CNcomment: 图形的显示buffer高度*/
    HI_U32                      u32ScreenXpos;      /**<X position of a graphics layer on the screen.*//**<CNcomment: 图层在屏幕上的X坐标*/
    HI_U32                      u32ScreenYpos;      /**<Y position of a graphics layer on the screen*//**<CNcomment: 图层在屏幕上的Y坐标*/
    HI_U32                      u32ScreenWidth;     /**<Width of a graphics layer on the screen*//**<CNcomment: 图层在屏幕上的宽度*/
    HI_U32                      u32ScreenHeight;    /**<Height of a graphics layer on the screen*//**<CNcomment: 图层在屏幕上的高度*/
	
    HI_UNF_DISP_ASPECT_RATIO_S  stAspectRatio;      /**<The device aspect ratio*//**<CNcomment: 设备宽高比*/
}HI_UNF_PDM_DISP_PARAM_S;


typedef enum hiUNF_PDM_BASEPARAM_TYPE_E
{
    HI_UNF_PDM_BASEPARAM_DISP0 = 0,     /*HI_UNF_PDM_DISP_PARAM_S * */
    HI_UNF_PDM_BASEPARAM_DISP1,         /*HI_UNF_PDM_DISP_PARAM_S * */
    HI_UNF_PDM_BASEPARAM_SOUND = 10,

    HI_UNF_PDM_BASEPARAM_BUTT
}HI_UNF_PDM_BASEPARAM_TYPE_E;
/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      PDM */
/** @{ */  /** <!-- [PDM] */
/** 
\brief Obtains the basic configuration information.  CNcomment:获取BASE配置区信息 CNend
\attention \n
N/A
\param[in]  pstBaseParam   Pointer to the basic parameters.  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_GetBaseParam(HI_UNF_PDM_BASEPARAM_TYPE_E enType, HI_VOID *pData);


/** 
\brief Modifies the basic configuration information.  CNcomment:更新BASE配置区信息 CNend
\attention \n
N/A
\param[in]  pstBaseParam Pointer to the basic parameters.  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_WRITE      Write flash pation error. CNcomment:写Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_ERASE      Erase flash pation error. CNcomment:擦除Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_UpdateBaseParam(HI_UNF_PDM_BASEPARAM_TYPE_E enType, HI_VOID *pData);

/** 
\brief Obtains the basic configuration information from the flash memory.  
CNcomment:获取LOGO配置区信息 CNend
\attention \n
N/A
\param[in]  pstLogoParam   Pointer to the logo parameter  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_GetLogoParam(HI_UNF_MCE_LOGO_PARAM_S *pstLogoParam);

/** 
\brief Modifies the configuration of the logo parameter.  CNcomment:更新LOGO配置区信息 CNend
\attention \n
Update logo parameter, you must invoke this function befor update data of logo
\CNcomment:更新logo参数，在更新logo内容前必须先调用此函数 CNend
\param[in]  pstLogoParam   Pointer to the logo parameter  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_WRITE      Write flash pation error. CNcomment:写Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_ERASE      Erase flash pation error. CNcomment:擦除Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_UpdateLogoParam(HI_UNF_MCE_LOGO_PARAM_S *pstLogoParam);


/** 
\brief Obtains the logo data from the flash memory. CNcomment:获取LOGO内容区信息 CNend
\attention \n
N/A
\param[in]  pu8Content Pointer to the logo data that is written from the flash memory CNcomment:内容buf指针 CNend
\param[in]  u32Size  Size of the logo data to be written  CNcomment:内容长度 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_GetLogoContent(HI_U8 *pu8Content, HI_U32 u32Size);


/** 
\brief Modifies the logo data.  CNcomment:更新LOGO内容区信息 CNend
\attention \n
Update data in logo partition, You must invoke HI_UNF_PDM_UpdateLogoParam to update logo parameter before invoke this function
\CNcomment:更新logo内容，在此函数之前必须先调用HI_UNF_PDM_UpdateLogoParam函数更新logo参数 CNend
\param[in]  pu8Content   Pointer to the logo data that is read from the flash memory  CNcomment:内容buf指针 CNend
\param[in]  u32Size   Size of the logo data to be read  CNcomment:内容长度 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_WRITE      Write flash pation error. CNcomment:写Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_ERASE      Erase flash pation error. CNcomment:擦除Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_UpdateLogoContent(HI_U8 *pu8Content, HI_U32 u32Size);

/** 
\brief Obtains the playing configuration information.  CNcomment:获取PLAY配置区信息 CNend
\attention \n
N/A
\param[in]  pstPlayParam   Playing configuration information  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_GetPlayParam(HI_UNF_MCE_PLAY_PARAM_S *pstPlayParam);

/** 
\brief   Modifies the playing configuration information.  CNcomment:更新PLAY配置区信息 CNend
\attention \n 
Update play parameter, you must invoke this function befor update data of play
\CNcomment:更新play参数，在更新play内容前必须先调用此函数 CNend
\param[in]  pstPlayParam  Playing configuration information  CNcomment:参数指针 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_WRITE      Write flash pation error. CNcomment:写Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_ERASE      Erase flash pation error. CNcomment:擦除Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_UpdatePlayParam(HI_UNF_MCE_PLAY_PARAM_S *pstPlayParam);

/** 
\brief Obtains the data being playing from the flash memory.  CNcomment:获取PLAY内容区信息 CNend
\attention \n
N/A
\param[in]  pu8Content Pointer to the data that is read from the flash memory  CNcomment:内容buf指针 CNend
\param[in]  u32Size  Size of the data being played that is read from the flash memory  CNcomment:内容长度 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_GetPlayContent(HI_U8 *pu8Content, HI_U32 u32Size);


/** 
\brief Updates the playing data part. CNcomment:更新PLAY内容区信息 CNend
\attention \n
Update data in play partition, You must invoke HI_UNF_PDM_UpdatePlayParam to update plat parameter before invoke this function
\CNcomment:更新play内容，在此函数之前必须先调用HI_UNF_PDM_UpdatePlayParam函数更新play参数 CNend
\param[in]  pu8Content  Pointer to the data that is written to the flash memroy  CNcomment:内容buf指针 CNend
\param[in]  u32Size  Size of the data being played  CNcomment:内容长度 CNend
\retval ::HI_SUCCESS       Success. CNcomment:成功 CNend
\retval :: HI_ERR_PDM_PTR_NULL      Pointer is null. CNcomment:空指针 CNend
\retval :: HI_ERR_PDM_GET_MTDINFO_ERR      Get flash pation infomation error. CNcomment:获取Flash分区信息失败 CNend
\retval :: HI_ERR_PDM_MTD_OPEN      Open flash pation error. CNcomment:打开Flash分区失败 CNend
\retval :: HI_ERR_PDM_MEM_ALLC      Alloc memory error. CNcomment:分配内存失败 CNend
\retval :: HI_ERR_PDM_MTD_READ      Read flash pation error. CNcomment:读取Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_WRITE      Write flash pation error. CNcomment:写Flash分区失败 CNend
\retval :: HI_ERR_PDM_MTD_ERASE      Erase flash pation error. CNcomment:擦除Flash分区失败 CNend
\retval :: HI_ERR_PDM_INVALID_OPT      The operation is invalid. CNcomment:无效操作 CNend
\see \n
N/A
*/
HI_S32  HI_UNF_PDM_UpdatePlayContent(HI_U8 *pu8Content, HI_U32 u32Size);

/** @} */  /*! <!-- API declaration end */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif




