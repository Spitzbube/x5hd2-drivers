
#ifndef __HI_DRV_AENC_H__
#define __HI_DRV_AENC_H__

//#include "hi_drv_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32   AENC_DRV_ModInit(HI_VOID);
HI_VOID  AENC_DRV_ModExit(HI_VOID);
HI_S32   AENC_DRV_Proc(struct seq_file *p, HI_VOID *v);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif//__HI_DRV_AENC_H__

