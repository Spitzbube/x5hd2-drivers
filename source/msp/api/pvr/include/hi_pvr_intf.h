/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_pvr_intf.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/10
  Description   : hi_pvr_intf.c header file
  History       :
  1.Date        : 2008/04/10
    Author      : q46153
    Modification: Created file

******************************************************************************/

#ifndef __HI_PVR_INTF_H__
#define __HI_PVR_INTF_H__

#include "hi_pvr_priv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

/* do event call back function                                              */
extern HI_VOID PVR_Intf_DoEventCallback(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E enEventType, HI_S32 s32EnvetValue);

HI_S32 PVRIntfInitEvent(HI_VOID);
HI_VOID PVRIntfDeInitEvent(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI_PVR_INTF_H__ */
