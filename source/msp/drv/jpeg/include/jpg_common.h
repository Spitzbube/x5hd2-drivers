/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : jpg_common.h
Version		    : Initial Draft
Author		    : 
Created		    : 2013/03/26
Description	    : 
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/03/26		    y00181162  		                	
******************************************************************************/


#ifndef __HI_JPE_COMMON_H__
#define __HI_JPE_COMMON_H__



/*********************************add include here******************************/



/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ******************************/
    #define HI_S40V200_VERSION
    //#define HI_3716CV200_VERSION

    /**===================================================================
                     S40V200 
       ===================================================================**/
    /** �жϺ� **/
	#define S40V200_JPGD0_IRQ_NUM             (97 + 32)
	/** �Ĵ�������ַ **/
	#define S40V200_JPGD0_REG_BASEADDR        0xf8c40000
	/**  
	 ** ����ʱ�ӼĴ�������ַ��JPEGʱ�ӼĴ���Ҫƫ�ƣ���CRG
	 ** �������Ҫ������λ����
	 **/
	#define S40V200_JPGD0_CRG_REG_PHYADDR     (0xf8a22000 + 0X7C)
	
    #define S40V200_JPGD1_IRQ_NUM             (98 + 32) 
    #define S40V200_JPGD1_REG_BASEADDR        0xf8c50000
    #define S40V200_JPGD1_CRG_REG_PHYADDR     (0xf8a22000 + 0x80)


	#define S40V200_JPG_CLOCK_SELECT          0x100
	#define S40V200_JPG_CLOCK_ON              0x1
    #define S40V200_JPG_CLOCK_OFF             0xFFFFFFFE
	
    #define S40V200_JPG_RESET_REG_VALUE       0x10
	#define S40V200_JPG_UNRESET_REG_VALUE     0xFFFFFFEF


    /**===================================================================
                     3716CV200
       ===================================================================**/
	#define HI3716CV200_JPGD0_IRQ_NUM             (97 + 32)
	#define HI3716CV200_JPGD0_REG_BASEADDR        0xf8c40000
	#define HI3716CV200_JPGD0_CRG_REG_PHYADDR     (0xf8a22000 + 0X7C)
	
    #define HI3716CV200_JPGD1_IRQ_NUM             (98 + 32) 
    #define HI3716CV200_JPGD1_REG_BASEADDR        0xf8c50000
    #define HI3716CV200_JPGD1_CRG_REG_PHYADDR     (0xf8a22000 + 0x80)

    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      [31:10]   ����
      [9:8]     ʱ��ѡ��
                00: 250MHz;
                01: 300MHz;
                10: 200MHZ;
                11: reserved;
      [7:5]     ����
      [4]       ��λ����(jpeg�Ĵ�������ĸ�λ�Ѿ�û�����ˣ��߽ӵ��ô�)
                0: ����λ
                1: ��λ
      [3:1]     ����
      [0]       ʱ���ſ�
                0:�ض�
                1:��

      ++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	#define HI3716CV200_JPG_CLOCK_SELECT          0x100        /** ʱ��Ƶ��ѡ��,�����300MHz **/
	#define HI3716CV200_JPG_CLOCK_ON              0x1          /** ��ʱ�ӣ���������      **/
    #define HI3716CV200_JPG_CLOCK_OFF             0xFFFFFFFE  /** �ر�ʱ�ӣ����������      **/
	
    #define HI3716CV200_JPG_RESET_REG_VALUE       0x10         /** ��λ����������          **/
	#define HI3716CV200_JPG_UNRESET_REG_VALUE     0xFFFFFFEF  /** ����λ�����������        **/

	



	
    /** �Ĵ������� **/
    #define JPG_REG_LENGTH                 0x64F             /** <64K  **/



    #define X5_JPG_REG_INTSTATUSOFFSET        0x100
    #define X5_JPG_REG_INTMASKOFFSET          0x104


    /*************************** Structure Definition ****************************/

	/**
	 **HI_CHIP_VERSION_V300 = MV300 or X6V300 use this
	 **HI_CHIP_VERSION_V200 = MV200 or X6V200 use this
	 **/
	typedef enum 
	{
	    HI_JPEG_CLOCK_V1,   /** 3716C 3716H**/
	    HI_JPEG_CLOCK_V2,   /** 3716M  **/
	    HI_JPEG_CLOCK_V3,   /** 3712---X6 **/
	    HI_JPEG_CLOCK_BUTT,
	    
	}HI_JPEG_CLOCK_TYPE;

    /********************** Global Variable declaration **************************/



    /******************************* API declaration *****************************/




#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPE_COMMON_H__ */
