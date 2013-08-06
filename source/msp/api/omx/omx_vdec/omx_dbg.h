#ifndef __OMX_DBG_H__
#define __OMX_DBG_H__

#ifdef ANDROID
#include<utils/Log.h>
#else
#define ALOGD				printf                
#define ALOGE				printf
#endif

#undef  LOG_TAG
#define LOG_TAG				"HIOMX_COMP"


#ifndef ANDROID                      // Ϊ��ʹlinux��pc-linc�����������Դ򿪣�Android������Ĭ�ϲ���
//#define DEBUG                       1
//#define DEBUG_WARN             1
//#define DEBUG_STREAM          1
#else
//#define DEBUG                       1
//#define DEBUG_WARN             1
//#define DEBUG_STREAM          1
#endif
#define DEBUG_STATE            1

#ifdef DEBUG
#define DEBUG_PRINT			       ALOGD
#else
#define DEBUG_PRINT                     
#endif

#ifdef DEBUG_WARN
#define DEBUG_PRINT_WARN		ALOGD
#else
#define DEBUG_PRINT_WARN          
#endif

#ifdef DEBUG_STREAM
#define DEBUG_PRINT_STREAM	ALOGD
#else
#define DEBUG_PRINT_STREAM       
#endif

#ifdef DEBUG_STATE
#define DEBUG_PRINT_STATE         ALOGD
#else
#define DEBUG_PRINT_STATE         
#endif

#define DEBUG_PRINT_ALWS          ALOGD
#define DEBUG_PRINT_ERROR         ALOGE


#endif //__OMX_DBG_H__
