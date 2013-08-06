/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : common_base.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/25
  Description   : common driver moudle define
  History       :
  1.Date        : 2010/01/25
    Author      : jianglei
    Modification: Created file

******************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/seq_file.h>

#include "hi_type.h"
#include "hi_drv_log.h"
#include "drv_struct_ext.h"


#include "drv_sys_ext.h"
#include "drv_log.h"
#include "drv_proc_ext.h"
#include "drv_stat_ext.h"
#include "drv_dev_ext.h"

#include "drv_sys_ioctl.h"
#include "drv_stat_ioctl.h"

#include "drv_module.h"

#include "drv_base_ext_k.h"
#include "drv_media_mem.h"


/* Use "strings hi_xx.ko | grep "SDK_VERSION"" to get the version */
/*HI_CHAR g_ModuleVersion[160] ="SDK_VERSION:["\
    MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
    __DATE__", "__TIME__"]";
*/

#ifdef CMN_TEST_SUPPORTED
extern HI_VOID HI_DRV_TEST_Init(HI_VOID);
extern HI_VOID HI_DRV_TEST_Exit(HI_VOID);
#endif


static int __init COMMON_DRV_ModInit(void)
{
    HI_S32 ret;

#ifndef MODULE
    ret = HI_DRV_PM_ModInit();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_PM_ModInit failed:%#x!\n", ret);
        return HI_FAILURE;
    }

    ret = DRV_MMZ_ModInit();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("DRV_MMZ_ModInit failed:%#x!\n", ret);
        goto ErrorExit_MMZ;
    }
#endif

#if !defined (HI_MCE_SUPPORT) && !defined(HI_KEYLED_CT1642_KERNEL_SUPPORT)
    ret = HI_DRV_CommonInit();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_CommonInit failed:%#x!\n", ret);
        goto ErrorExit_Common;
    }
#endif

    ret = HI_DRV_PROC_Init();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_PROC_Init failed:%#x!\n", ret);
        goto ErrorExit_PROC;
    }

    ret = HI_DRV_LOG_Init();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_LOG_Init failed:%#x!\n", ret);
        goto ErrorExit_LOG;
    }

    ret = HI_DRV_SYS_Init();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_SYS_Init failed:%#x!\n", ret);
        goto ErrorExit_SYS;
    }

    ret = HI_DRV_STAT_Init();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("HI_DRV_STAT_Init failed:%#x!\n", ret);
        goto ErrorExit_STAT;
    }

    ret = MMNGR_DRV_ModInit(KMODULE_MAX_COUNT, KMODULE_MEM_MAX_COUNT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("KModuleMgr_Init failed:%#x!\n", ret);
        goto ErrorExit_Module;
    }

#ifdef CMN_TEST_SUPPORTED
    HI_DRV_TEST_Init();
#endif

#if !defined(CONFIG_SUPPORT_CA_RELEASE) && defined(MODULE)
    printk("Load hi_common.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

ErrorExit_Module:
    HI_DRV_STAT_Exit();

ErrorExit_STAT:
    HI_DRV_SYS_Exit();

ErrorExit_SYS:
    HI_DRV_LOG_Exit();

ErrorExit_LOG:
    HI_DRV_PROC_Exit();

ErrorExit_PROC:
#if !defined (HI_MCE_SUPPORT) && !defined(KEYLED_CT1642_KERNEL_SUPPORT)
    HI_DRV_CommonExit();

ErrorExit_Common:
#endif

#ifndef MODULE
    DRV_MMZ_ModExit();

ErrorExit_MMZ:
    HI_DRV_PM_ModExit();
#endif

    return HI_FAILURE;
}

#ifdef MODULE
static HI_VOID COMMON_DRV_ModExit (HI_VOID)
{
#ifdef CMN_TEST_SUPPORTED
    HI_DRV_TEST_Exit();
#endif

    MMNGR_DRV_ModExit();

    HI_DRV_STAT_Exit();

    HI_DRV_SYS_Exit();

    HI_DRV_LOG_Exit();

    HI_DRV_PROC_Exit();

#ifndef MODULE
    DRV_MMZ_ModExit();
    HI_DRV_PM_ModExit();
#endif


#if !defined (HI_MCE_SUPPORT) && !defined(HI_KEYLED_CT1642_KERNEL_SUPPORT)
    HI_DRV_CommonExit ();
#endif


#if !defined(CONFIG_SUPPORT_CA_RELEASE) && defined(MODULE)
    printk("remove hi_common.ko success.\n");
#endif

    return;
}
#endif

#ifdef MODULE
module_init(COMMON_DRV_ModInit);
module_exit(COMMON_DRV_ModExit);
#else
device_initcall(COMMON_DRV_ModInit);
#endif

MODULE_AUTHOR("HISILION");
MODULE_LICENSE("GPL");
