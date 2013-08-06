/******************************************************************************
Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_debug.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : Common debugging macro definition
Function List :
History       :
******************************************************************************/
#ifndef __HI_DEBUG_H__
#define __HI_DEBUG_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_module.h"

//#undef HI_DEBUG
#define HI_DEBUG

#ifdef __OS_LINUX__
#ifdef __KERNEL__
    #define HI_PRINT printk
#else
#include <stdio.h>
    #define HI_PRINT printf
#endif /* end of __KERNEL__ */
#else  /* __OS_ECOS__ */
#define HI_PRINT printf
#endif /* end of __OS_LINUX__ */

#ifdef __KERNEL__
    #define HI_PANIC printk
#else
    #define HI_PANIC printf
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup     HI_DEBUG */
/** @{ */  /** <!-- [HI_DEBUG] */


/**Default level of the output debugging information*/
/**CNcomment: Ĭ�ϵĵ�����Ϣ�������*/
#define HI_LOG_LEVEL_DEFAULT HI_LOG_LEVEL_ERROR

/**Level of the output debugging information*/
/**CNcomment: ������Ϣ�������*/
typedef enum hiLOG_LEVEL_E
{
    HI_LOG_LEVEL_FATAL   = 0,     /**<Fatal error. It indicates that a critical problem occurs in the system. Therefore, you must pay attention to it.*/
                                  /**<CNcomment: ��������, ���������Ҫ�ر��ע��һ����ִ���������ϵͳ�������ش����� */
    HI_LOG_LEVEL_ERROR   = 1,     /**<Major error. It indicates that a major problem occurs in the system and the system cannot run.*/
                                  /**<CNcomment: һ�����, һ����ִ���������ϵͳ�����˱Ƚϴ�����⣬�������������� */
    HI_LOG_LEVEL_WARNING = 2,     /**<Warning. It indicates that a minor problem occurs in the system, but the system still can run properly.*/
                                  /**<CNcomment: �澯��Ϣ, һ����ִ�����Ϣ����ϵͳ���ܳ������⣬���ǻ��ܼ������� */
    HI_LOG_LEVEL_INFO    = 3,     /**<Message. It is used to prompt users. Users can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: ��ʾ��Ϣ, һ����Ϊ�����û���������ڶ�λ�����ʱ����Դ򿪣�һ������½���ر� */
    HI_LOG_LEVEL_DBG     = 4,     /**<Debug. It is used to prompt developers. Developers can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: ��ʾ��Ϣ, һ����Ϊ������Ա����������趨�Ĵ�ӡ����һ������½���ر� */

    HI_LOG_LEVEL_BUTT
} HI_LOG_LEVEL_E;

/** @} */

/**Just only for fatal level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_TRACE_LEVEL_FATAL    (0)
/**Just only for error level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_TRACE_LEVEL_ERROR    (1)
/**Just only for warning level print. */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_TRACE_LEVEL_WARN     (2)
/**Just only for info level print.    */   /**CNcomment: Ϊ�˴�ӡ��Ϣ������ƶ��ĺ��ӡ���� */
#define HI_TRACE_LEVEL_INFO     (3)
/**Just only for debug level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_TRACE_LEVEL_DBG      (4)

#ifndef CFG_HI_LOG_LEVEL
#define CFG_HI_LOG_LEVEL         (HI_TRACE_LEVEL_INFO)
#endif


/**Just only debug output,MUST BE NOT calling it. */
/**CNcomment: ���������Ϣ�ӿڣ����Ƽ�ֱ�ӵ��ô˽ӿ� */
extern HI_VOID HI_LogOut(HI_U32 u32Level, HI_MOD_ID_E enModId,
            HI_U8 *pFuncName, HI_U32 u32LineNum, const char *format, ...);

#define PRINT_FMT ("[%d %s-%s]:%s[%d]:%s", TimeMs, DebugLevelName[u32Level],\
                g_pLogConfigInfo[enModId].ModName,\
                pFuncName, u32LineNum, log_str)

#ifdef HI_DEBUG

#define HI_TRACE(level, module_id, fmt...)                      \
    do{                                                         \
        HI_LogOut(level, module_id, (HI_U8*)__FUNCTION__,__LINE__,fmt);  \
    }while(0)

#define HI_ASSERT(expr)                                     \
    do{                                                     \
        if (!(expr)) {                                      \
            HI_PANIC("\nASSERT failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
                __FILE__,__FUNCTION__, __LINE__, #expr);    \
        }                                                   \
    }while(0)


#define HI_ASSERT_RET(expr)                                     \
    do{                                                         \
        if (!(expr)) {                                          \
            HI_PRINT("\n<%s %d>: ASSERT Failure{" #expr "}\n",  \
                          __FUNCTION__, __LINE__);              \
            return HI_FAILURE;                                  \
        }                                                       \
    }while(0)

#define HI_DEBUG_LOG(fmt...) \
            HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_SYS, fmt)




/**Supported for debug output to serial/network/u-disk. */
/**CNcomment: ����ģ����Ҫ�������º�������������Ϣ������������ڡ����ڡ�U�̴洢�� */
#if defined(ANDROID)
#include <utils/Log.h>
#define HI_INFO_PRINT( module_id, fmt...)  ALOGV(fmt)
#define HI_DBG_PRINT(  module_id, fmt...)  ALOGD(fmt)
#define HI_WARN_PRINT( module_id, fmt...)  ALOGI(fmt)
#define HI_ERR_PRINT(  module_id, fmt...)  ALOGE(fmt)
#define HI_FATAL_PRINT(module_id, fmt...)  ALOGE(fmt)

#else

/**Just only reserve the fatal level output. */
/**CNcomment: �������������ĵ�����Ϣ */
#if (CFG_HI_LOG_LEVEL == HI_TRACE_LEVEL_FATAL)
#define HI_FATAL_PRINT(module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_FATAL,    module_id, fmt)
#define HI_ERR_PRINT(  module_id, fmt...)
#define HI_WARN_PRINT( module_id, fmt...)
#define HI_INFO_PRINT( module_id, fmt...)
#define HI_DBG_PRINT(  module_id, fmt...)
/**Just only reserve the fatal/error level output. */
/**CNcomment: �������������ĺʹ��󼶱�ĵ�����Ϣ */
#elif (CFG_HI_LOG_LEVEL == HI_TRACE_LEVEL_ERROR)
#define HI_FATAL_PRINT(module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_FATAL,    module_id, fmt)
#define HI_ERR_PRINT(  module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_ERROR,    module_id, fmt)
#define HI_WARN_PRINT( module_id, fmt...)
#define HI_INFO_PRINT( module_id, fmt...)
#define HI_DBG_PRINT(  module_id, fmt...)
/**Just only reserve the fatal/error/warning level output. */
/**CNcomment: �������������ġ�����ġ����漶��ĵ�����Ϣ */
#elif (CFG_HI_LOG_LEVEL == HI_TRACE_LEVEL_WARN)
#define HI_FATAL_PRINT(module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_FATAL,    module_id, fmt)
#define HI_ERR_PRINT(  module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_ERROR,    module_id, fmt)
#define HI_WARN_PRINT( module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_WARN,     module_id, fmt)
#define HI_INFO_PRINT( module_id, fmt...)
#define HI_DBG_PRINT(  module_id, fmt...)
/**Just only reserve the fatal/error/warning/info level output. */
/**CNcomment: �������������ġ�����ġ��������Ϣ����ĵ�����Ϣ */
#elif (CFG_HI_LOG_LEVEL == HI_TRACE_LEVEL_INFO)
#define HI_FATAL_PRINT(module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_FATAL,    module_id, fmt)
#define HI_ERR_PRINT(  module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_ERROR,    module_id, fmt)
#define HI_WARN_PRINT( module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_WARN,     module_id, fmt)
#define HI_INFO_PRINT( module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_INFO,     module_id, fmt)
#define HI_DBG_PRINT(  module_id, fmt...)
#else
/**Reserve all the levels output. */
/**CNcomment: �������м��������Ϣ */
#define HI_FATAL_PRINT(module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_FATAL,    module_id, fmt)
#define HI_ERR_PRINT(  module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_ERROR,    module_id, fmt)
#define HI_WARN_PRINT( module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_WARN,     module_id, fmt)
#define HI_INFO_PRINT( module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_INFO,     module_id, fmt)
#define HI_DBG_PRINT(  module_id, fmt...)   HI_TRACE(HI_TRACE_LEVEL_DBG,      module_id, fmt)
#endif

#endif


#else
#define HI_TRACE(level, module_id, fmt...)
#define HI_ASSERT(expr)
#define HI_ASSERT_RET(expr)
#define HI_DEBUG_LOG(fmt...)
#endif

/** @} */  /** <!-- ==== Structure Definition End ==== */


#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#define VERSION_STRING ("SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["__DATE__", "__TIME__"]")

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HI_DEBUG_H__ */


