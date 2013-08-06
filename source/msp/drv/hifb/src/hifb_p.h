


#ifndef __HIFB_P_H__
#define __HIFB_P_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include <linux/fb.h>
#include "hifb_drv.h"
#include "hifb_drv_common.h"
#include "hifb_scrolltext.h"


#define MAX_FB  32          /* support 32 layers most, the limit is from linux fb*/


/* define the value of default set of each layer */
#define HIFB_HD_DEF_WIDTH    1280     /* unit: pixel */
#define HIFB_HD_DEF_HEIGHT   720     /* unit: pixel */
#define HIFB_HD_DEF_STRIDE   (HIFB_HD_DEF_WIDTH*4)    /* unit: byte */
#define HIFB_HD_DEF_VRAM     7200  //(0x3f48)   /* unit:KB 1280*720*4*2*/


#define HIFB_SD_DEF_WIDTH    720
#define HIFB_SD_DEF_HEIGHT   576
#define HIFB_SD_DEF_STRIDE   1440
#define HIFB_SD_DEF_VRAM     3240   //(0xca8)   /* unit:KB 720*576*4*/


#define HIFB_AD_DEF_WIDTH    720
#define HIFB_AD_DEF_HEIGHT   80
#define HIFB_AD_DEF_STRIDE   1440
#define HIFB_AD_DEF_VRAM     3240   //(0xca8)   /*unit:KB 720*576*4*/

#define HIFB_CURSOR_DEF_VRAM (64*2) /*unit is 1024Bytes,  for doudble buffer mode, we need 2 memory buffer, save cursor*/

#define HIFB_DEF_DEPTH    16      /* unit: bits */
#define HIFB_DEF_XSTART   0
#define HIFB_DEF_YSTART   0
#define HIFB_DEF_ALPHA    0xff
#define HIFB_DEF_PIXEL_FMT    HIFB_FMT_RGB565

#define HIFB_CMAP_SIZE  0x0    /*unit:KB 256*4*/

#define HIFB_IS_CLUTFMT(eFmt)  (HIFB_FMT_1BPP <= (eFmt) && (eFmt) <= HIFB_FMT_ACLUT88)
#define HIFB_ALPHA_OPAQUE    0xff
#define HIFB_ALPHA_TRANSPARENT 0x00


#define HIFB_DEFLICKER_LEVEL_MAX 5   /* support level 5 deflicker most */

#define HIFB_MAX_CURSOR_WIDTH 128
#define HIFB_MAX_CURSOR_HEIGHT 128

#define HIFB_MAX_LAYER_ID (HIFB_LAYER_ID_BUTT-1)
#define HIFB_MAX_LAYER_NUM HIFB_LAYER_ID_BUTT

typedef enum
{
	HIFB_ANTIFLICKER_NONE,	/* no antiflicker.If scan mode is progressive, hifb will set antiflicker mode to none */
	HIFB_ANTIFLICKER_TDE,	/* tde antiflicker mode, it's effect for 1buf or 2buf only */
	HIFB_ANTIFLICKER_VO,	/* vo antiflicker mode, need hardware supprot */
	HIFB_ANTIFLICKER_BUTT
} HIFB_LAYER_ANTIFLICKER_MODE_E;

#define DISPLAY_BUFFER "Display_Buffer"
#define OPTM_GFX_WBC2_BUFFER "Optm_GfxWbc2"
#define HIFB_ZME_COEF_BUFFER "Hifb_ZmeCoef"
/*only use in logo transition*/
typedef enum
{
    HIFB_STATE_LOGO_IN = 0x1,    /*boot start with logo*/
    HIFB_STATE_PUT_VSCREENINFO = 0x2, /*ioctl:FBIOPUT_VSCREENINFO*/
    HIFB_STATE_PAN_DISPLAY = 0x4, /*call function hifb_pan_display*/
    HIFB_STATE_REFRESH = 0x8, /*refresh app*/
    HIFB_STATE_BUTT
}HIFB_STATE_E;

#if 1
#define HIFB_MAX_FLIPBUF_NUM 2

/* 3D MEM INFO STRUCT*/
typedef struct
{
    HI_U32 u32StereoMemStart;
    HI_U32 u32StereoMemLen;
}HIFB_3DMEM_INFO_S;


/* 3D PAR INFO STRUCT*/
typedef struct
{
	HI_S32                 s32Depth;	
	HI_U32                 u32rightEyeAddr;     /**<  right eye address */
	HI_U32                 u32DisplayAddr[HIFB_MAX_FLIPBUF_NUM];
    HIFB_STEREO_MODE_E     enInStereoMode;
    HIFB_STEREO_MODE_E     enOutStereoMode; 	
	HIFB_RECT              st3DUpdateRect;
	HIFB_SURFACE_S         st3DSurface;
    HIFB_3DMEM_INFO_S      st3DMemInfo;
}HIFB_3D_PAR_S;


/* N3D PAR INFO STRUCT*/
typedef struct
{
	HIFB_RECT       stUpdateRect;
	HI_U32          u32DisplayAddr[HIFB_MAX_FLIPBUF_NUM];
	HIFB_SURFACE_S  stCanvasSur;        /* canvas surface allocated for user */
	HIFB_BUFFER_S   stUserBuffer;       /* backup usr's refreshing buffer data, 
											using when refresh again or refresh all*/
}HIFB_DISP_INFO_S;

typedef struct 
{    
	HI_BOOL   bModifying;
	HI_U32    u32ParamModifyMask; 
    HI_BOOL   bNeedFlip;       /* when tde blit job completed, we need to flip buffer, only using in pandisplay and 2buf*/
    HI_BOOL   bFliped;	       /* a flag to record buf has been swithed no not in vo isr, effect only in 2 buf mode*/
    HI_U32    u32IndexForInt;  /* index of screen buf*/
	HI_U32    u32BufNum;       /* count of flip buffer*/	
	HI_U32    u32ScreenAddr;   /* screen buf addr */
	HI_S32    s32RefreshHandle;/* job handle of tde blit*/
}HIFB_RTIME_INFO_S;

typedef struct
{
	HI_BOOL                         bOpen;               /* open status*/
	HI_BOOL                         bShow;               /* show status */
    HIFB_COLOR_FMT_E                enColFmt;            /* color format */
	HIFB_LAYER_BUF_E                enBufMode;           /* refresh mode*/
	HI_U32                          u32DisplayWidth;     /* width  of layer's display buffer*/
    HI_U32                          u32DisplayHeight;    /* height of layer's display buffer*/
    HI_U32                          u32ScreenWidth;      /* width  of layer's  show    area*/
    HI_U32                          u32ScreenHeight;     /* height of layer's  show    area*/
	HIFB_POINT_S                    stPos;               /* beginning position of layer*/ 
    HIFB_ALPHA_S                    stAlpha;             /* alpha attribution */
    HIFB_COLORKEYEX_S               stCkey;              /* colorkey attribution */  	
}HIFB_EXTEND_INFO_S;

typedef struct
{
	HI_U32             u32LayerID;       /* layer id */
	atomic_t           ref_count;        /* framebuffer reference count */
	HI_BOOL            bPreMul;
	HI_BOOL            bNeedAntiflicker;
	HI_U32             u32HDflevel;      /* horizontal deflicker level */
	HI_U32             u32VDflevel;      /* vertical deflicker level */
	HI_UCHAR           ucHDfcoef[HIFB_DEFLICKER_LEVEL_MAX - 1];/* horizontal deflicker coefficients */
	HI_UCHAR           ucVDfcoef[HIFB_DEFLICKER_LEVEL_MAX - 1];/* vertical deflicker coefficients */
	HIFB_LAYER_ANTIFLICKER_LEVEL_E  enAntiflickerLevel; /* antiflicker level */
	HIFB_LAYER_ANTIFLICKER_MODE_E   enAntiflickerMode; /* antiflicker mode */ 
}HIFB_BASE_INFO_S;

typedef struct
{
    /*For cursor layer, stCursor means cursor buffer, it is alloced and freed
     both by user;for general layer,stCursor means back buf*/
	HIFB_CURSOR_S stCursor; 

    /*For cursor layer,you can quary whether cursor attach to a certain layer
     for general layer, you can quary whether cursor attach to it*/
    HI_U32 bAttched;

    /*back buf is valid no not*/ 
    //HI_BOOL bValid;

    /*valid area:overlap region between attached layer and cursor layer*/
    HIFB_RECT stRectInDispBuf;

    /*the orignal position of cursor, usually is (0,0) but also has different when at margin*/	
    HIFB_POINT_S stPosInCursor;
}HIFB_CURSOR_INFO_S;


typedef struct
{   	
	HI_BOOL             bSetStereoMode;
	
	HIFB_CURSOR_INFO_S  stCursorInfo;
    HIFB_BASE_INFO_S    stBaseInfo;
    HIFB_EXTEND_INFO_S  stExtendInfo;
    
    HIFB_3D_PAR_S       st3DInfo;
    HIFB_DISP_INFO_S    stDispInfo; 

	HIFB_RTIME_INFO_S   stRunInfo;      /**run time info for N3D and 3D*/
}HIFB_PAR_S;
#endif

#if 0
typedef struct
{
    HIFB_POINT_S stPos;
    HIFB_POINT_S stStereoPos;
    HIFB_POINT_S stUserPos;
    HI_U32 u32DisplayWidth;
    HI_U32 u32DisplayHeight;
    HI_U32 u32ScreenWidth;
    HI_U32 u32ScreenHeight;
    HI_U32 u32StereoScreenWidth;
    HI_U32 u32StereoScreenHeight;
    HI_U32 u32UserScreenWidth;
    HI_U32 u32UserScreenHeight;
    HI_BOOL bPreMul;
    HI_BOOL bNeedAntiflicker;
    HIFB_LAYER_ANTIFLICKER_LEVEL_E enAntiflickerLevel; /* antiflicker level */
    HIFB_LAYER_ANTIFLICKER_MODE_E enAntiflickerMode; /* antiflicker mode */
    //HIFB_LAYER_SCALE_MODE_E enScaleMode; /* scale mode */
    HI_U32 u32VirXRes;
    HI_U32 u32VirYRes;
    HI_U32 u32XRes;
    HI_U32 u32YRes;
    HI_U32 u32MaxScreenWidth;
    HI_U32 u32MaxScreenHeight;
    HIFB_STEREO_MODE_E enEncPicFraming;
}HIFB_DISPLAY_INFO_S;

#define HIFB_MAX_ACC_RECT_NUM 100
#define HIFB_MAX_FLIPBUF_NUM 3
typedef struct 
{
    HIFB_LAYER_BUF_E enBufMode;
    HI_BOOL bNeedFlip;
    HI_BOOL bFliped;	    /* a flag to record buf has been swithed no not in vo isr, effect only in 2 buf mode*/
    HI_BOOL bRefreshed;
    HI_U32 u32IndexForInt;	/* index of screen buf*/
    HIFB_BUFFER_S stUserBuffer;
    HI_U32 u32DisplayAddr[HIFB_MAX_FLIPBUF_NUM]; /* array to record display buf addr */
    HI_U32 u32ScreenAddr;	    /* screen buf addr */
    HI_U32 u32StereoMemStart;
    HI_U32 u32StereoMemLen;
    HI_U32 u32BufNum;
    HIFB_SURFACE_S stStereoSurface;
    HI_U32 u32IntPicNum;	/* buf switch num in 2 buf mode */
    HI_U32 u32RefreshNum;	/* refresh request num in 2 buf mode */
    HIFB_RECT stUnionRect;	/* union refresh rect */
    HIFB_RECT stStereoUnionRect;
    HI_BOOL bCompNeedUpdate;
    HI_BOOL bComDirty;
    HIFB_RECT stCompUnionRect;
    HIFB_RECT stInRect;
    HI_S32 s32RefreshHandle;    /* refresh handle */
}HIFB_BUF_INFO_S;
#endif

#if 0
/* hifb private data*/
typedef struct
{
    HI_U32  u32LayerID;   /* layer id */
    HI_BOOL          bShow;         /* show status */
    HIFB_COLOR_FMT_E enColFmt;      /* color format */
    HIFB_ALPHA_S     stAlpha;         /* alpha attribution */
    HIFB_COLORKEYEX_S  stCkey;          /* colorkey attribution */
    HI_U32     u32HDflevel;      /* horizontal deflicker level */
    HI_U32     u32VDflevel;      /* vertical deflicker level */
    HI_UCHAR    ucHDfcoef[HIFB_DEFLICKER_LEVEL_MAX - 1];/* horizontal deflicker coefficients */
    HI_UCHAR    ucVDfcoef[HIFB_DEFLICKER_LEVEL_MAX - 1];/* vertical deflicker coefficients */
    HIFB_DISPLAY_INFO_S stDisplayInfo;  /* display info */
    HIFB_BUF_INFO_S stBufInfo;
    HIFB_CURSOR_INFO_S stCursorInfo;
    HI_U32 u32ParamModifyMask;
    HI_BOOL bModifying;
    HI_BOOL bCopyOSD;
    HIFB_SURFACE_S CanvasSur;       /* canvas surface */
    //HI_U32 u32CmapAddr;
    atomic_t ref_count;             /* framebuffer reference count */ 
    HI_BOOL bRefreshByDisp;
    HIFB_STEREO_WORKMODE_E enStereoMode;
    HI_BOOL bSetStereoMode;
	/*add by q00214668*/
    HI_BOOL bOpen;              /**open or not*/ 
    HI_BOOL bCompression;       /*whether the compression function was open*/ 
    HI_BOOL bCompAvailable;     /*whether the compression function was available*/
	HI_BOOL bCompNeedOpen;      /*after comp_err ,wo should open comp again*/
	struct timeval stCompTime; /*record the time that compress usr data*/
} HIFB_PAR_S;
#endif


typedef struct 
{
    struct fb_info *pstInfo;
    HI_U32    u32LayerSize;     /*u32LayerSize = fb.smem_len + cursor buf size*/
} HIFB_LAYER_S;



typedef enum 
{
    HIFB_LAYER_TYPE_HD,
    HIFB_LAYER_TYPE_SD,
    HIFB_LAYER_TYPE_AD,
    HIFB_LAYER_TYPE_CURSOR,
    HIFB_LAYER_TYPE_BUTT,    
}HIFB_LAYER_TYPE_E;


typedef struct
{
    struct fb_bitfield stRed;     /* bitfield in fb mem if true color, */
    struct fb_bitfield stGreen;   /* else only length is significant */
    struct fb_bitfield stBlue;
    struct fb_bitfield stTransp;  /* transparency	*/
} HIFB_ARGB_BITINFO_S;

/**extern for scrolltext.c*/
/* the interface to operate the chip */
extern HIFB_DRV_OPS_S s_stDrvOps;
extern HIFB_DRV_TDEOPS_S s_stDrvTdeOps;

/* to save layer id and layer size */
extern HIFB_LAYER_S s_stLayer[HIFB_MAX_LAYER_NUM];

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
extern HIFB_SCROLLTEXT_INFO_S s_stTextLayer[HIFB_LAYER_ID_BUTT];
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HIFB_P_H__ */


