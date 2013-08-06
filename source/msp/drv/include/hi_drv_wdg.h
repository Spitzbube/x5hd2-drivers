/*
 *	Generic watchdog defines. Derived from..
 *
 * Berkshire PC Watchdog Defines
 * by Ken Hollis <khollis@bitgate.com>
 *
 */

#ifndef _HI_DRV_WDG_H
#define _HI_DRV_WDG_H

#include "hi_debug.h"

#define HI_FATAL_WDG(fmt...) \
    HI_FATAL_PRINT(HI_ID_WDG, fmt)

#define HI_ERR_WDG(fmt...) \
    HI_ERR_PRINT(HI_ID_WDG, fmt)

#define HI_WARN_WDG(fmt...) \
    HI_WARN_PRINT(HI_ID_WDG, fmt)

#define HI_INFO_WDG(fmt...) \
    HI_INFO_PRINT(HI_ID_WDG, fmt)

#if    defined (CHIP_TYPE_hi3716h)  \
    || defined (CHIP_TYPE_hi3716c)  \
    || defined (CHIP_TYPE_hi3716m)	\
    || defined (CHIP_TYPE_hi3712)       
 #define HI_WDG_NUM (1)
#elif defined (CHIP_TYPE_hi3716cv200es) || defined (CHIP_TYPE_hi3716cv200)
 #define HI_WDG_NUM (3)
#else
 #error YOU MUST DEFINE  CHIP_TYPE!
#endif

HI_S32 WDG_DRV_ModInit(HI_VOID);
HI_VOID WDG_DRV_ModExit(HI_VOID);

#endif  /* ifndef _HI_DRV_WDG_H */
