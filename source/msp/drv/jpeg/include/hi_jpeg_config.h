/******************************************************************************

  Copyright (C), 2014-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : hi_jpeg_config.h
Version		    : Initial Draft
Author		    : 
Created		    : 2013/07/01
Description	    : this file is through set macro to select different funciton,
                  and select different platform
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/07/01		    y00181162  		    Created file      	
******************************************************************************/

 

#ifndef __HI_JPEG_CONFIG_H__
#define __HI_JPEG_CONFIG_H__


/*********************************add include here******************************/
#ifdef __KERNEL__
 #include "hi_gfx_comm_k.h"
#else
    #ifdef CONFIG_GFX_FPGA_SDK
 		#include "hi_gfx_test_comm.h"
	#else
		#include "hi_gfx_comm.h"
	#endif
#endif


/*****************************************************************************/


#ifdef __cplusplus
      #if __cplusplus
   
extern "C" 
{

      #endif
#endif /* __cplusplus */

    /***************************** Macro Definition ******************************/

	/** \addtogroup 	 JPEG CFG */
    /** @{ */  /** <!-- ��JPEG CFG�� */


    /****************************************************************************
     **���������ֺ꿪�ض�����Makefile�ж���
     ****************************************************************************/
	/** Definition of the chip version */
	/** CNcomment:оƬ���ͺ궨��,���꿪�طŵ�Makefile��ȥ CNend */
    #if 0
       #define CONFIG_CHIP_S40V200_VERSION
	   /** the chip version is 3716CV200 */
	   /** CNcomment:3716CV200оƬ */
       #define CONFIG_CHIP_3716CV200_VERSION
	   #define CONFIG_CHIP_3719CV100_VERSION
	   #define CONFIG_CHIP_3718CV100_VERSION
	   #define CONFIG_CHIP_3719MV100_A_VERSION
	   #define CONFIG_CHIP_3719MV300_VERSION
       #define CONFIG_CHIP_3712_VERSION
	   #define CONFIG_CHIP_3535_VERSION
	   #define CONFIG_CHIP_3716MV300_VERSION
	   #define CONFIG_CHIP_OTHERS_VERSION
    #endif
	/** this macro is add google function and use in android version,define in Makefile */
	/** CNcomment:��android��google�汾����jpeg-6b�У���Makefile�п��Ƹú꿪�� CNend */
	#if 0
	#define CONFIG_JPEG_ADD_GOOGLEFUNCTION
	#endif

     /****************************************************************************
      ** function marco definition no depend chip platform
	  ** CNcomment:��оƬƽ̨�޹صĺ궨��
     ****************************************************************************/
     #ifndef CONFIG_GFX_ANDROID_SDK
		/** the some function realize before the main function */
		/** CNcomment:��Щ������main����֮ǰʵ�֣�Ҳ���ǳ�������֮�����һ�� */
		#define CONFIG_JPEG_REALIZEFUNC_BEFORMAINFUNC
	 #else
	 	/** use outsize deal with stream */
		/** CNcomment:ʹ���ⲿ�����������ƣ�ͨ���ص����� */
	 	#define CONFIG_JPEG_USE_CALLBACK_STREAM
		/** use gfx mmz to alloc mem */
		/** CNcomment:ʹ���Լ���װ��MMZ�����ڴ� */
		#define CONFIG_JPEG_USE_PRIVATE_MMZ
		/** use android debug message */
		/** CNcomment:Android�汾�ĵ�����Ϣ */
		#define CONFIG_JPEG_ANDROID_DEBUG_ENABLE
     #endif

	 #ifndef CONFIG_GFX_ADVCA_RELEASE
	 /** if need proc message */
	 /** CNcomment:�Ƿ���Ҫproc��Ϣ */
     #define CONFIG_JPEG_PROC_ENABLE
	 #endif

	/** if need use soft csc to debug whether the hard csc has problem */
	/** CNcomment:ʹ�����ת������λӲ��ת���Ƿ������� */
    #define CONFIG_JPEG_SOFTCSC_ENABLE

	/** use hard idct method */
	/** CNcomment:ʹ��Ӳ����IDCT�㷨 */
    #define CONFIG_JPEG_USEHWIDCT
	
/****************************************************************************
 ** function marco definition depend chip platform
 ** CNcomment:��оƬƽ̨��صĺ궨��
 ****************************************************************************/
#ifdef CONFIG_CHIP_3716MV300_VERSION
	/** if support crop */
    /** CNcomment:�Ƿ�֧�ֲü����� */
    #define CONFIG_JPEG_OUTPUT_CROP
	/** use mmz to alloc memory */
	/** CNcomment:ʹ��mmz������ڴ� */
	#define CONFIG_JPEG_USEMMZMEM
	/** get jpeg dec time */
	/** CNcomment:��ȡjpeg�����ʱ�� */
	#define CONFIG_JPEG_GETDECTIME
	/** support motion jpeg decode */
	/** CNcomment:֧��motion jpeg ���� */
	//#define CONFIG_JPEG_MPG_DEC_ENABLE
#endif


#ifdef CONFIG_CHIP_S40V200_VERSION
	/** if support crop */
	/** CNcomment:�Ƿ�֧�ֲü����� */
    #define CONFIG_JPEG_OUTPUT_CROP
	/** use mmz to alloc memory */
	/** CNcomment:ʹ��mmz������ڴ� */
	#define CONFIG_JPEG_USEMMZMEM
	/** get jpeg dec time */
	/** CNcomment:��ȡjpeg�����ʱ�� */
	#define CONFIG_JPEG_GETDECTIME
	/** use sdk CRG write */
	/** CNcomment:ʹ��SDK��CRG���� */
	#define CONFIG_JPEG_USE_SDK_CRG_ENABLE
#endif

	
#if defined(CONFIG_CHIP_3716CV200_VERSION) || defined(CONFIG_CHIP_3719CV100_VERSION) || defined(CONFIG_CHIP_3718CV100_VERSION) || defined(CONFIG_CHIP_3719MV100_A_VERSION)
	/** if support crop */
	/** CNcomment:�Ƿ�֧�ֲü����� */
    #define CONFIG_JPEG_OUTPUT_CROP
	/** if support suspend */
	/** CNcomment:�Ƿ�֧�ִ������� */
	#define CONFIG_JPEG_SUSPEND
	/** if support jpeg hard dec to argb8888 */
	/** CNcomment:�Ƿ�֧��jpegӲ���������argb8888 */
	//#define CONFIG_JPEG_HARDDEC2ARGB /** ����汾��֧�֣������漰��stride���⣬ֱ����TDEת����� **/
	/** use mmz to alloc memory */
	/** CNcomment:ʹ��mmz������ڴ� */
	#define CONFIG_JPEG_USEMMZMEM
	/** get jpeg dec time */
	/** CNcomment:��ȡjpeg�����ʱ�� */
	#define CONFIG_JPEG_GETDECTIME
	/** the save stream buffer should 4bytes align about 3716CV200 */
	/** CNcomment:3716CV200оƬ�洢����buffer��ʼ��ַ��Ҫ4�ֽڶ��룬֮���оƬ��������bug */
	#define CONFIG_JPEG_STREAMBUF_4ALIGN
	/** support motion jpeg decode */
	/** CNcomment:֧��motion jpeg ���� */
	//#define CONFIG_JPEG_MPG_DEC_ENABLE
	/** use sdk CRG write */
	/** CNcomment:ʹ��SDK��CRG���� */
	#define CONFIG_JPEG_USE_SDK_CRG_ENABLE
#endif


#ifdef CONFIG_CHIP_3719MV300_VERSION
		/** if support crop */
		/** CNcomment:�Ƿ�֧�ֲü����� */
    	#define CONFIG_JPEG_OUTPUT_CROP
	    /** all jpeg dec output yuv420sp */
	    /** CNcomment:ͳһ�������yuv420sp */
        #define CONFIG_JPEG_OUTPUT_YUV420SP
	    /** dec jpeg file output lu pixel value sum */
	    /** CNcomment:ͳ������ֵ */
        #define CONFIG_JPEG_OUTPUT_LUPIXSUM
		/** get jpeg dec time */
	    /** CNcomment:��ȡjpeg�����ʱ�� */
	    #define CONFIG_JPEG_GETDECTIME
		/** use mmz to alloc memory */
		/** CNcomment:ʹ��mmz������ڴ� */
		#define CONFIG_JPEG_USEMMZMEM
		/** if support suspend */
		/** CNcomment:�Ƿ�֧�ִ������� */
		#define CONFIG_JPEG_SUSPEND
		/** support motion jpeg decode */
		/** CNcomment:֧��motion jpeg ���� */
		//#define CONFIG_JPEG_MPG_DEC_ENABLE
#endif



#ifdef CONFIG_CHIP_3535_VERSION
		/** if support crop */
		/** CNcomment:�Ƿ�֧�ֲü����� */
    	#define CONFIG_JPEG_OUTPUT_CROP
	    /** not output warning info */
	    /** CNcomment:������澯��Ϣ */
		#define CONFIG_JPEG_UNPRINT_WARNING
	    /** all jpeg dec output yuv420sp */
	    /** CNcomment:ͳһ�������yuv420sp */
		#define CONFIG_JPEG_OUTPUT_YUV420SP
	    /** dec jpeg file output lu pixel value sum */
	    /** CNcomment:ͳ������ֵ */
		#define CONFIG_JPEG_OUTPUT_LUPIXSUM
	    /** set mem */
	    /** CNcomment:ͨ�������ڴ�ӿ�����ȡ��Ҫ���ڴ� */
		#define CONFIG_JPEG_SETMEM
	    /** use no mmz cach */
	    /** CNcomment:ʹ�ò���cach��mmz�ڴ� */
		#define CONFIG_JPEG_NOCACHE
	    /** soft decode to calc the lu pixle sum value */
	    /** CNcomment:�Ƿ���Ҫ���ͳ������ֵ���� */
		#define CONFIG_JPEG_SFCALCLUPIXSUM
#endif

	/** use the calc default value dqt and dht value */
	/** CNcomment:ʹ�ü���õ�������͹��������ֵ��ֱ�����üĴ��� */
#ifdef CONFIG_JPEG_MPG_DEC_ENABLE
		#define CONFIG_JPEG_USE_CALC_DEFAULT_VALUE
#endif

    /****************************************************************************
     ** function marco definition use to fpga test and deal with bug by eda
	 ** CNcomment:����Ӳ���߼����Լ���λbugʹ�õĺ꿪��
     ****************************************************************************/
	/** save the scen information,use it to eda simulation */
	/** CNcomment:���ֳ�ʹ�ܣ����������õģ��ֳ����߼���EDA���� */
	//#define CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
	/** save the data to bmp picture */
	/** CNcomment:����bmpͼƬ */
    //#define CONFIG_JPEG_TEST_SAVE_BMP_PIC
    /** save yuv semi-planer data */
	/** CNcomment:����yuv semi-planer���� */
    //#define CONFIG_JPEG_TEST_SAVE_YUVSP_DATA

	/** the chip hard decode random reset test */
	/** CNcomment:�����λ��Ƭ���� */
	//#define CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
	/** test press */
	/** CNcomment:���Է�ѹ */
	//#define CONFIG_JPEG_TEST_CHIP_PRESS
	/** the ck_gt_en is open */
	/** CNcomment:ʱ���ſش� */
	//#define CONFIG_JPEG_TEST_CHIP_OPEN_CK
	/** test hard decode capa */
	/** CNcomment:����Ӳ���������� */
	//#define CONFIG_JPEG_TEST_HARD_DEC_CAPA
	/** save the scen information,use it to eda simulation */
	/** CNcomment:���Դ������ӵļ����ӿ� */
	//#define CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE

	#ifdef CONFIG_GFX_FPGA_SDK
	#define CONFIG_JPEG_FPGA_TEST_ENABLE
	#endif
	
    #ifdef CONFIG_GFX_ADVCA_RELEASE
	    /** this is not has warning message */
	    /** CNcomment:ֻ�д��ϲ����Ų����и澯��Ϣ */
        #define JPEG_TRACE( fmt,args...)
	#else
	    #ifdef __KERNEL__
		#define JPEG_TRACE               GFX_Printk
		#else
	 	#define JPEG_TRACE               GFX_Printf
		#endif
	#endif

    /** @} */  /*! <!-- Macro Definition end */

	
    /*************************** Structure Definition ****************************/
	
    /***************************  The enum of Jpeg image format  ******************/


    /********************** Global Variable declaration **************************/
    

    /******************************* API declaration *****************************/
	
	
    #ifdef __cplusplus

        #if __cplusplus



}
      
        #endif
        
   #endif /* __cplusplus */

#endif /* __HI_JPEG_CONFIG_H__*/
