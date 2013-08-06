#ifndef __HI_DRV_VPSS_H__
#define __HI_DRV_VPSS_H__

#include "hi_type.h"
#include "hi_drv_video.h"


//================================================  �ӿڳ��� =================================================

/* ������壬���ʵ������һ�����������ڱ�ʶchan��portʱ��ֵ�Ķ���������ͬ��������-1��Ϊ��Ч�����
      1. VPSSʵ���������ֵΪʵ����������(ID)
      2. �˿ھ������ֵҪ��ʾ��������: ����ͨ���������Լ��˿ڱ����������
              = ʵ������*256 + �˿����� */
      
typedef HI_S32 VPSS_HANDLE;
#define VPSS_INVALID_HANDLE (-1)

/* �Ӷ˿ھ������ȡͨ���������˿����� */
#define PORTHANDLE_TO_VPSSID(hPort)    (hPort >> 8)
#define PORTHANDLE_TO_PORTID(hPort)    (hPort & 0xff)

#define DEF_HI_DRV_VPSS_PORT_BUFFER_MAX_NUMBER 16
#define DEF_HI_DRV_VPSS_PORT_MAX_NUMBER 3

/*ǰ����������һ֡���*/
#define DEF_HI_DRV_VPSS_LAST_FRAME_FLAG 0xffee
/*ǰ����������һ֡������*/
#define DEF_HI_DRV_VPSS_LAST_ERROR_FLAG 0xff00
//==============================================  �ӿ����ݽṹ ===============================================
/* ͨ����������Ϣ */
typedef enum
{
    HI_DRV_VPSS_HFLIP_DISABLE = 0,
    HI_DRV_VPSS_HFLIP_ENABLE,
    HI_DRV_VPSS_HFLIP_BUTT
}HI_DRV_VPSS_HFLIP_E;

typedef enum
{
    HI_DRV_VPSS_VFLIP_DISABLE = 0,
    HI_DRV_VPSS_VFLIP_ENABLE,
    HI_DRV_VPSS_VFLIP_BUTT
}HI_DRV_VPSS_VFLIP_E;

//���ÿ����û�ʹ��
typedef enum
{
    HI_DRV_VPSS_ROTATION_DISABLE = 0,
    HI_DRV_VPSS_ROTATION_90,
    HI_DRV_VPSS_ROTATION_180,
    HI_DRV_VPSS_ROTATION_270,
    HI_DRV_VPSS_ROTATION_BUTT
}HI_DRV_VPSS_ROTATION_E;

typedef enum
{
    HI_DRV_VPSS_STEREO_DISABLE = 0,
    HI_DRV_VPSS_STEREO_SIDE_BY_SIDE,
    HI_DRV_VPSS_STEREO_TOP_AND_BOTTOM,
    HI_DRV_VPSS_STEREO_TIME_INTERLACED,
    HI_DRV_VPSS_STEREO_BUTT
}HI_DRV_VPSS_STEREO_E;

typedef enum
{
    HI_DRV_VPSS_DIE_DISABLE = 0,
    HI_DRV_VPSS_DIE_AUTO,
    HI_DRV_VPSS_DIE_2FIELD,
    HI_DRV_VPSS_DIE_3FIELD,
    HI_DRV_VPSS_DIE_4FIELD,
    HI_DRV_VPSS_DIE_5FIELD,
    HI_DRV_VPSS_DIE_6FIELD,
    HI_DRV_VPSS_DIE_7FIELD,
    HI_DRV_VPSS_DIE_BUTT
}HI_DRV_VPSS_DIE_MODE_E;

typedef enum
{
    HI_DRV_VPSS_ACC_DISABLE = 0,
    HI_DRV_VPSS_ACC_LOW,    
    HI_DRV_VPSS_ACC_MIDDLE,
    HI_DRV_VPSS_ACC_HIGH,
    HI_DRV_VPSS_ACC_BUTT
}HI_DRV_VPSS_ACC_E;

typedef enum
{
    HI_DRV_VPSS_ACM_DISABLE = 0,
    HI_DRV_VPSS_ACM_BLUE,    
    HI_DRV_VPSS_ACM_GREEN,
    HI_DRV_VPSS_ACM_BG,
    HI_DRV_VPSS_ACM_SKIN,
    HI_DRV_VPSS_ACM_BUTT  
}HI_DRV_VPSS_ACM_E;

typedef enum
{
    HI_DRV_VPSS_CC_DISABLE = 0,
    HI_DRV_VPSS_CC_ENABLE,
    HI_DRV_VPSS_CC_AUTO,     
    HI_DRV_VPSS_CC_BUTT
}HI_DRV_VPSS_CC_E;

typedef enum
{
    HI_DRV_VPSS_SHARPNESS_DISABLE = 0,
    HI_DRV_VPSS_SHARPNESS_ENABLE,
    HI_DRV_VPSS_SHARPNESS_AUTO,
    HI_DRV_VPSS_SHARPNESS_BUTT
}HI_DRV_VPSS_SHARPNESS_E;

typedef enum
{
    HI_DRV_VPSS_DB_DISABLE = 0,
    HI_DRV_VPSS_DB_ENABLE,
    HI_DRV_VPSS_DB_AUTO,     
    HI_DRV_VPSS_DB_BUTT
}HI_DRV_VPSS_DB_E;

typedef enum
{
    HI_DRV_VPSS_DR_DISABLE = 0,
    HI_DRV_VPSS_DR_ENABLE,
    HI_DRV_VPSS_DR_AUTO,     
    HI_DRV_VPSS_DR_BUTT
}HI_DRV_VPSS_DR_E;

typedef enum
{
    HI_DRV_VPSS_CSC_DISABLE = 0,
    HI_DRV_VPSS_CSC_ENABLE,   
    HI_DRV_VPSS_CSC_AUTO,     
    HI_DRV_VPSS_CSC_BUTT
}HI_DRV_VPSS_CSC_E;

typedef enum
{
    HI_DRV_VPSS_FIDELITY_DISABLE = 0,
    HI_DRV_VPSS_FIDELITY_ENABLE,  
    HI_DRV_VPSS_FIDELITY_AUTO,     
    HI_DRV_VPSS_FIDELITY_BUTT
}HI_DRV_VPSS_FIDELITY_E;


typedef struct
{
    HI_DRV_VPSS_HFLIP_E  eHFlip;
    HI_DRV_VPSS_VFLIP_E  eVFlip;
    HI_DRV_VPSS_STEREO_E eStereo;
    HI_DRV_VPSS_ROTATION_E  eRotation;
    HI_DRV_VPSS_DIE_MODE_E eDEI;
    HI_DRV_VPSS_ACC_E eACC;
    HI_DRV_VPSS_ACM_E eACM;
    HI_DRV_VPSS_CC_E eCC;
    HI_DRV_VPSS_SHARPNESS_E eSharpness;
    HI_DRV_VPSS_DB_E eDB;
    HI_DRV_VPSS_DR_E eDR;

    /*���뻭��ü���Ϣ*/
    HI_RECT_S stInRect;  /* (0,0,0,0) means full imgae, not clip */
    HI_BOOL   bUseCropRect;
    HI_DRV_CROP_RECT_S stCropRect;
}HI_DRV_VPSS_PROCESS_S;

typedef struct
{
    HI_DRV_VPSS_CSC_E eCSC;
    /* �Ƿ���Ҫ�������棬���ΪTRUE������������ֱ���һ�µ��������ֱͨͨ������ָ֤���ܹ� */
    HI_DRV_VPSS_FIDELITY_E eFidelity;
}HI_DRV_VPSS_PORT_PROCESS_S;


typedef struct 
{
    /*VPSSʵ�����ȼ� */
    HI_S32  s32Priority;  /* 0��Ч��1 ~ 31Ϊ�������ȼ�����ֵԽ�����ȼ�Խ�� */

    /*����Ϊ�ɶ�̬������*/
    
    /* �Ƿ�ֻ��������һ֡���ڵ��ӳ�ģʽ����ΪTRUE������ÿ�ζ������Src buf��ֻ�����һ֡���� */
    HI_BOOL bAlwaysFlushSrc;

    /* ����(��port�޹ص�)���ã����㷨�� */
    HI_DRV_VPSS_PROCESS_S stProcCtrl;

}HI_DRV_VPSS_CFG_S;

/*
BUFFER����������ģʽ:
1.USER ALLOC AND MANAGE
    VPSS�ڲ���֡�治������ÿ��д��֡��ʱ���û��ϱ��¼� VPSS_EVENT_GET_FRMBUFFER��ȡ֡�档
                            ͼ�������ʱ�����û��ϱ��¼�VPSS_EVENT_NEW_FRAME�ͷ�֡��
2.VPSS ALLOC AND MANAGE
    VPSS�ڲ���֡��������
3.USER ALLOC AND VPSS MANAGE
    �û�����֡���һ���Է���VPSSʹ��
*/
typedef enum hiDRV_VPSS_BUFFER_TYPE_E{
    HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE = 0,
    HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE,
    HI_DRV_VPSS_BUF_USER_ALLOC_VPSS_MANAGE,
    HI_DRV_VPSS_BUF_TYPE_BUTT
}HI_DRV_VPSS_BUFFER_TYPE_E;

typedef struct hiDRV_VPSS_BUFFER_CFG_S
{
    HI_DRV_VPSS_BUFFER_TYPE_E eBufType;
    
    HI_U32 u32BufNumber;     /* bBufferNumber must be <= DEF_HI_DRV_VPSS_PORT_BUFFER_MAX_NUMBER */
    HI_U32 u32BufSize;          /* every buffer size in Byte */
    HI_U32 u32BufStride;       /* only for 'bUserAllocBuffer = TRUE' */
    HI_U32 u32BufPhyAddr[DEF_HI_DRV_VPSS_PORT_BUFFER_MAX_NUMBER]; /*128bit aligned */
}HI_DRV_VPSS_BUFLIST_CFG_S;

/* port��������Ϣ */
typedef struct
{
    /*����Ϊ�ɶ�̬������*/
    HI_DRV_COLOR_SPACE_E eDstCS;   /*���߼�ȷ��*/
    HI_DRV_VPSS_PORT_PROCESS_S stProcCtrl;

    /*display Info*/
    HI_DRV_ASPECT_RATIO_S stDispPixAR;    /**/
    HI_DRV_ASP_RAT_MODE_E eAspMode;
    HI_DRV_ASPECT_RATIO_S stCustmAR;
    
    HI_S32  s32OutputWidth;
    HI_S32  s32OutputHeight;
    
    HI_BOOL   bInterlaced;                /*���� I/P*/
    HI_RECT_S stScreen;                   /*���Դ��ڴ�С :0 0 �����ڴ�С����������*/
        
    /*����Ϊ���ɶ�̬������*/
    HI_DRV_PIX_FORMAT_E eFormat; /* Support ... */
    HI_DRV_VPSS_BUFLIST_CFG_S stBufListCfg;
    HI_U32 u32MaxFrameRate;  /* in 1/100 HZ  */
    /* ��tunnel�йص����� */
    HI_BOOL  bTunnelEnable;  /* ����Ƿ�ʹ��TUNNEL */
    HI_S32  s32SafeThr;    /* ��ȫˮ�ߣ�0~100��Ϊ���֡����ɵİٷֱ�. 0��ʾ��ʱ�ɸ��󼶣�100��ʾ��ȫ��ɲ��ܸ��� */

    
}HI_DRV_VPSS_PORT_CFG_S;


/* VPSS�û��Ŀ�������*/
typedef enum
{
    HI_DRV_VPSS_USER_COMMAND_IMAGEREADY = 0,
    HI_DRV_VPSS_USER_COMMAND_RESET,
    HI_DRV_VPSS_USER_COMMAND_CHECKALLDONE,
    HI_DRV_VPSS_USER_COMMAND_BUTT
}HI_DRV_VPSS_USER_COMMAND_E;

typedef struct
{   
    HI_U32 u32TotalBufNumber;
    HI_U32 u32FulBufNumber;  
}HI_DRV_VPSS_PORT_BUFLIST_STATE_S;

typedef enum
{
    HI_DRV_VPSS_BUFFUL_PAUSE = 0,
    HI_DRV_VPSS_BUFFUL_KEEPWORKING,
    HI_DRV_VPSS_BUFFUL_BUTT
}HI_DRV_VPSS_BUFFUL_STRATAGY_E;


/*
Դģʽ����
*/
typedef enum
{
    VPSS_SOURCE_MODE_USERACTIVE = 0,//��ģʽ
    VPSS_SOURCE_MODE_VPSSACTIVE,//��ģʽ
    VPSS_SOURCE_MODE_BUTT
}HI_DRV_VPSS_SOURCE_MODE_E;

typedef HI_S32 (*PFN_VPSS_SRC_FUNC)(VPSS_HANDLE hVPSS,HI_DRV_VIDEO_FRAME_S *pstImage);

typedef struct
{
    /*��ģʽ�²���Ϊ�����û����ã�����VPSS����*/
    PFN_VPSS_SRC_FUNC VPSS_GET_SRCIMAGE;
    PFN_VPSS_SRC_FUNC VPSS_REL_SRCIMAGE;
}HI_DRV_VPSS_SOURCE_FUNC_S;


typedef struct
{
    VPSS_HANDLE hPort; 
    HI_U32 u32StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32Size;
    HI_U32 u32Stride;
    HI_U32 u32FrmH;
    HI_U32 u32FrmW;
}HI_DRV_VPSS_FRMBUF_S;

typedef struct
{
    VPSS_HANDLE hPort; 
    HI_DRV_VIDEO_FRAME_S stFrame;
}HI_DRV_VPSS_FRMINFO_S;

/* VPSS���ϱ��¼�ö��*/
typedef enum
{   
    /*
        VPSS��������ʱ����ȡҪд��BUFʧ�ܣ��ϱ����¼�,����ṹ��HI_DRV_VPSS_BUFFUL_STRATAGY_Eָ��

        �û���ͨ��HI_DRV_VPSS_CheckPortBufListFul
                  HI_DRV_VPSS_GetPortBufListState
                  �ӿڣ���ȡʵ���ڸ�PORT��BUFFERռ�����,
        ͨ���޸�HI_DRV_VPSS_BUFFUL_STRATAGY_E�ṹ�壬���ش������
    */
    VPSS_EVENT_BUFLIST_FULL,    //HI_DRV_VPSS_BUFFUL_STRATAGY_E
    VPSS_EVENT_GET_FRMBUFFER,   //HI_DRV_VPSS_FRMBUF_S
    VPSS_EVENT_REL_FRMBUFFER,   //HI_DRV_VPSS_FRMBUF_S
    VPSS_EVENT_NEW_FRAME,        //HI_DRV_VPSS_FRMINFO_S
    VPSS_EVENT_BUTT,
}HI_DRV_VPSS_EVENT_E;

//ע���û���VPSS�����쳣����Ӧ����  
typedef HI_S32 (*PFN_VPSS_CALLBACK)(HI_HANDLE hDst, HI_DRV_VPSS_EVENT_E enEventID, HI_VOID *pstArgs);

#endif

