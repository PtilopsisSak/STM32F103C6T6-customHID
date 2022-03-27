/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *
  *          ===================================================================
  *                                HID Class  Description
  *          ===================================================================
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application
  *
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *
  *
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_HID_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_HID_Private_Defines
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_HID_Private_Macros
  * @{
  */
/**
  * @}
  */




/** @defgroup USBD_HID_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_Init(USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit(USBD_HandleTypeDef *pdev,
                                uint8_t cfgidx);

static uint8_t  USBD_HID_Setup(USBD_HandleTypeDef *pdev,
                               USBD_SetupReqTypedef *req);

static uint8_t  *USBD_HID_GetFSCfgDesc(uint16_t *length);

static uint8_t  *USBD_HID_GetHSCfgDesc(uint16_t *length);

static uint8_t  *USBD_HID_GetOtherSpeedCfgDesc(uint16_t *length);

static uint8_t  *USBD_HID_GetDeviceQualifierDesc(uint16_t *length);

static uint8_t  USBD_HID_DataIn(USBD_HandleTypeDef *pdev, uint8_t epnum);
/**
  * @}
  */

/** @defgroup USBD_HID_Private_Variables
  * @{
  */

USBD_ClassTypeDef  USBD_HID =
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,
  USBD_HID_GetHSCfgDesc,
  USBD_HID_GetFSCfgDesc,
  USBD_HID_GetOtherSpeedCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};

/* USB HID device FS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgFSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */
};

/* USB HID device HS Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgHSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_HS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */
};

/* USB HID device Other Speed Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_OtherSpeedCfgDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval */
  /* 34 */
};


/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[USB_HID_DESC_SIZ]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE] __ALIGN_END =
    {

        //-------------���̲��ֱ���������----------------
        //��ʾ��;ҳΪͨ�������豸
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)

        //��ʾ��;Ϊ����
        0x09, 0x06, // USAGE (Keyboard)

        //��ʾӦ�ü��ϣ�����Ҫ��END_COLLECTION����������������END_COLLECTION
        0xa1, 0x01, // COLLECTION (Application)

        //����ID������ID 0�Ǳ����ģ�
        0x85, 0x01, // Report ID (1)

        //��ʾ��;ҳΪ����
        0x05, 0x07, //   USAGE_PAGE (Keyboard)

        //��;��Сֵ������Ϊ��ctrl��
        0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
                    //��;���ֵ������Ϊ��GUI������window��
        0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
                    //�߼���СֵΪ0
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
                    //�߼����ֵΪ1
        0x25, 0x01, //   LOGICAL_MAXIMUM (1)
                    //�����С��������ֶεĿ�ȣ�Ϊ1bit������ǰ����߼���СֵΪ0���߼����ֵΪ1
        0x75, 0x01, //   REPORT_SIZE (1)
                    //����ĸ���Ϊ8�����ܹ���8��bits
        0x95, 0x08, //   REPORT_COUNT (8)
                    //�����ã�������ֵ������ֵ�����������һ�㱨�����ֵ��
                    //������ƶ��������򱨸����ֵ����ʾ����ƶ�����
        0x81, 0x02, //   INPUT (Data,Var,Abs)
                    //�������⼸��������һ�������õ��ֶΣ��ܹ�Ϊ8��bits��ÿ��bit��ʾһ������
                    //�ֱ����ctrl������GUI������8��bits�պù���һ���ֽڣ���λ�ڱ���ĵ�һ���ֽڡ�
                    //�������λ����bit-0��Ӧ����ctrl����������ص����ݸ�λΪ1�����ʾ��ctrl�������£�
                    //������ctrl��û�а��¡����λ����bit-7��ʾ��GUI���İ���������м�ļ���λ��
                    //��Ҫ����HIDЭ���й涨����;ҳ��HID Usage Tables����ȷ��������ͨ��������ʾ
                    //�����������ctrl��shift��del����

        //���������ݶθ���Ϊ1
        0x95, 0x01, //   REPORT_COUNT (1)
                    //ÿ���γ���Ϊ8bits
        0x75, 0x08, //   REPORT_SIZE (8)
                    //�����ã�������ֵ������ֵ
        0x81, 0x03, //   INPUT (Cnst,Var,Abs)

        //������8��bit�ǳ������豸���뷵��0

        //���������ݶθ���Ϊ5
        0x95, 0x05, //   REPORT_COUNT (5)
                    //ÿ���δ�СΪ1bit
        0x75, 0x01, //   REPORT_SIZE (1)
                    //��;��LED�����������Ƽ����ϵ�LED�õģ���������˵�����������
        0x05, 0x08, //   USAGE_PAGE (LEDs)
                    //��;��Сֵ��Num Lock�������ּ�������
        0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
                    //��;���ֵ��Kana�������ʲô����Ҳ�����^_^
        0x29, 0x05, //   USAGE_MAXIMUM (Kana)
                    //��ǰ����˵������ֶ�������õģ���������LED��������ֵ������ֵ��
                    // 1��ʾ������0��ʾ����
        0x91, 0x02, //   OUTPUT (Data,Var,Abs)

        //���������ݶθ���Ϊ1
        0x95, 0x01, //   REPORT_COUNT (1)
                    //ÿ���δ�СΪ3bits
        0x75, 0x03, //   REPORT_SIZE (3)
                    //����ã�������ֵ������
        0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
                    //����Ҫ���ֽڶ��룬��ǰ�����LED��ֻ����5��bit��
                    //���Ժ�����Ҫ����3������bit������Ϊ������

        //�������Ϊ6
        0x95, 0x06, //   REPORT_COUNT (6)
                    //ÿ���δ�СΪ8bits
        0x75, 0x08, //   REPORT_SIZE (8)
                    //�߼���Сֵ0
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
                    //�߼����ֵ255
        0x25, 0xFF, //   LOGICAL_MAXIMUM (255)
                    //��;ҳΪ����
        0x05, 0x07, //   USAGE_PAGE (Keyboard)
                    //ʹ����СֵΪ0
        0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
                    //ʹ�����ֵΪ0x65
        0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
                    //�����ã����������飬����ֵ
        0x81, 0x00, //   INPUT (Data,Ary,Abs)
                    //���϶�����6��8bit������飬ÿ��8bit����һ���ֽڣ�������ʾһ�����������Կ���ͬʱ
                    //��6���������¡�û�а�������ʱ��ȫ������0��������µļ�̫�࣬���¼���ɨ��ϵͳ
                    //�޷����ְ���ʱ����ȫ������0x01����6��0x01�������һ�������£�����6���ֽ��еĵ�һ
                    //���ֽ�Ϊ��Ӧ�ļ�ֵ�������ֵ�ο�HID Usage Tables����������������£����1��2����
                    //�ֽڷֱ�Ϊ��Ӧ�ļ�ֵ���Դ����ơ�

        //�ؼ��ϣ�������Ķ�Ӧ
        0xc0, // END_COLLECTION

        //-----------------------��겿�ֱ���������----------------------------
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x02, // USAGE (Mouse)
        0xa1, 0x01, // COLLECTION (Application)
        0x85, 0x02, // ����ID (2)
        0x09, 0x01, //   USAGE (Pointer)
        0xa1, 0x00, //   COLLECTION (Physical)
        0x05, 0x09, //     USAGE_PAGE (Button)
        0x19, 0x01, //     USAGE_MINIMUM (Button 1)
        0x29, 0x03, //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00, //     LOGICAL_MINIMUM (0)
        0x25, 0x01, //     LOGICAL_MAXIMUM (1)
        0x95, 0x03, //     REPORT_COUNT (3)
        0x75, 0x01, //     REPORT_SIZE (1)
        0x81, 0x02, //     INPUT (Data,Var,Abs)
        0x95, 0x01, //     REPORT_COUNT (1)
        0x75, 0x05, //     REPORT_SIZE (5)
        0x81, 0x03, //     INPUT (Cnst,Var,Abs)
        0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30, //     USAGE (X)
        0x09, 0x31, //     USAGE (Y)
        0x09, 0x38, //     USAGE (Wheel)
        0x15, 0x81, //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
        0x75, 0x08, //     REPORT_SIZE (8)
        0x95, 0x03, //     REPORT_COUNT (3)
        0x81, 0x06, //     INPUT (Data,Var,Rel)
        0xc0,       //   END_COLLECTION
        0xc0,       // END_COLLECTION

        // 0x05, 0x0d,       // USAGE_PAGE (Digitizers)
        // 0x09, 0x04,       // USAGE (Touch Screen)
        // 0xa1, 0x01,       // COLLECTION (Application)
        // 0x85, 0x04,       // ����ID (4)
        // 0x09, 0x22,       //   USAGE (Finger)
        // 0xa1, 0x00,       //   COLLECTION (Physical)
        // 0x09, 0x42,       //     USAGE (Tip Switch)
        // 0x15, 0x00,       //     LOGICAL_MINIMUM (0)
        // 0x25, 0x01,       //     LOGICAL_MAXIMUM (1)
        // 0x75, 0x01,       //     REPORT_SIZE (1)
        // 0x95, 0x01,       //     REPORT_COUNT (1)
        // 0x81, 0x02,       //     INPUT (Data,Var,Abs)
        // 0x75, 0x07,       //     REPORT_SIZE (7)
        // 0x95, 0x01,       //     REPORT_COUNT (1)
        // 0x81, 0x03,       //     INPUT (Cnst,Var,Abs)
        // 0x05, 0x01,       //     USAGE_PAGE (Generic Desktop)
        // 0x09, 0x30,       //     USAGE (X)
        // 0x75, 0x10,       //     REPORT_SIZE (16)
        // 0x95, 0x01,       //     REPORT_COUNT (1)
        // 0x15, 0x00,       //     LOGICAL_MINIMUM (0)
        // 0x26, 0xff, 0x0f, //     LOGICAL_MAXIMUM (4095)
        // 0x35, 0x00,       //     PHYSICAL_MINIMUM (0)
        // 0x46, 0xff, 0x0f, //     PHYSICAL_MAXIMUM (4095)
        // 0x81, 0x02,       //     INPUT (Data,Var,Abs)
        // 0x09, 0x31,       //     USAGE (Y)
        // 0x95, 0x01,       //     REPORT_COUNT (1)
        // 0x75, 0x10,       //     REPORT_SIZE (16)
        // 0x15, 0x00,       //     LOGICAL_MINIMUM (0)
        // 0x26, 0xff, 0x0f, //     LOGICAL_MAXIMUM (4095)
        // 0x35, 0x00,       //     PHYSICAL_MINIMUM (0)
        // 0x46, 0xff, 0x0f, //     PHYSICAL_MAXIMUM (4095)
        // 0x81, 0x02,       //     INPUT (Data,Var,Abs)
        // 0xc0,             // END_COLLECTION
        // 0xc0,

        0x05, 0x0C, // 0   	GLOBAL_USAGE_PAGE(Consumer)
        0x09, 0x01, // 2   	LOCAL_USAGE(	Consumer Control 	)
        0xA1, 0x01, // 4   	MAIN_COLLECTION(Applicatior)
        0x85, 0x05, // 6   	GLOBAL_REPORT_ID(5)
        0xA1, 0x00, // 8   	MAIN_COLLECTION(Physical)
        0x09, 0xE9, // 10  	LOCAL_USAGE(	Volume Increment 	)
        0x09, 0xEA, // 12  	LOCAL_USAGE(	Volume Decrement 	)
        0x09, 0xE2, // 14  	LOCAL_USAGE(	Mute 	)
        0x09, 0xCD, // 16  	LOCAL_USAGE(	Play/Pause 	)
        0x35, 0x00, // 18  	GLOBAL_PHYSICAL_MINIMUM(0)
        0x45, 0x07, // 20  	GLOBAL_PHYSICAL_MAXIMUM(7)
        0x15, 0x00, // 22  	GLOBAL_LOGICAL_MINIMUM(0)
        0x25, 0x01, // 24  	GLOBAL_LOCAL_MAXIMUM(1)
        0x75, 0x01, // 26  	GLOBAL_REPORT_SIZE(1)
        0x95, 0x04, // 28  	GLOBAL_REPORT_COUNT(4)
        0x81, 0x02, // 30  	MAIN_INPUT(data var absolute NoWrap linear PreferredState NoNullPosition NonVolatile )	Input 0.4
        0x75, 0x01, // 32  	GLOBAL_REPORT_SIZE(1)
        0x95, 0x04, // 34  	GLOBAL_REPORT_COUNT(4)
        0x81, 0x01, // 36  	MAIN_INPUT(const array absolute NoWrap linear PreferredState NoNullPosition NonVolatile )	Input 1.0
        0xC0,       // 38  	MAIN_COLLECTION_END
        0xC0,       // 39  	MAIN_COLLECTION_END

        0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
        0x15, 0x00,       // LOGICAL_MINIMUM (0)
        0x09, 0x04,       // USAGE (Joystick)
        0xa1, 0x01,       // COLLECTION (Application)
        0x85, 0x06,       // ����ID (2)
        0x05, 0x02,       //   USAGE_PAGE (Simulation Controls)
        0x09, 0xbb,       //   USAGE (Throttle)
        0x15, 0x81,       //   LOGICAL_MINIMUM (-127)
        0x25, 0x7f,       //   LOGICAL_MAXIMUM (127)
        0x75, 0x08,       //   REPORT_SIZE (8)
        0x95, 0x01,       //   REPORT_COUNT (1)
        0x81, 0x02,       //   INPUT (Data,Var,Abs)
        0x05, 0x01,       //   USAGE_PAGE (Generic Desktop)
        0x09, 0x01,       //   USAGE (Pointer)
        0xa1, 0x00,       //   COLLECTION (Physical)
        0x09, 0x30,       //     USAGE (X)
        0x09, 0x31,       //     USAGE (Y)
        0x95, 0x02,       //     REPORT_COUNT (2)
        0x81, 0x02,       //     INPUT (Data,Var,Abs)
        0xc0,             //   END_COLLECTION
        0x09, 0x39,       //   USAGE (Hat switch)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x25, 0x03,       //   LOGICAL_MAXIMUM (3)
        0x35, 0x00,       //   PHYSICAL_MINIMUM (0)
        0x46, 0x0e, 0x01, //   PHYSICAL_MAXIMUM (270)
        0x65, 0x14,       //   UNIT (Eng Rot:Angular Pos)
        0x75, 0x04,       //   REPORT_SIZE (4)
        0x95, 0x01,       //   REPORT_COUNT (1)
        0x81, 0x02,       //   INPUT (Data,Var,Abs)
        0x05, 0x09,       //   USAGE_PAGE (Button)
        0x19, 0x01,       //   USAGE_MINIMUM (Button 1)
        0x29, 0x04,       //   USAGE_MAXIMUM (Button 4)
        0x15, 0x00,       //   LOGICAL_MINIMUM (0)
        0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,       //   REPORT_SIZE (1)
        0x95, 0x04,       //   REPORT_COUNT (4)
        0x55, 0x00,       //   UNIT_EXPONENT (0)
        0x65, 0x00,       //   UNIT (None)
        0x81, 0x02,       //   INPUT (Data,Var,Abs)
        0xc0              // END_COLLECTION

};

/**
  * @}
  */

/** @defgroup USBD_HID_Private_Functions
  * @{
  */

/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /* Open EP IN */
  USBD_LL_OpenEP(pdev, HID_EPIN_ADDR, USBD_EP_TYPE_INTR, HID_EPIN_SIZE);
  pdev->ep_in[HID_EPIN_ADDR & 0xFU].is_used = 1U;

  pdev->pClassData = USBD_malloc(sizeof(USBD_HID_HandleTypeDef));

  if (pdev->pClassData == NULL)
  {
    return USBD_FAIL;
  }

  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;

  return USBD_OK;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit(USBD_HandleTypeDef *pdev,
                                uint8_t cfgidx)
{
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev, HID_EPIN_ADDR);
  pdev->ep_in[HID_EPIN_ADDR & 0xFU].is_used = 0U;

  /* FRee allocated memory */
  if (pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  }

  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup(USBD_HandleTypeDef *pdev,
                               USBD_SetupReqTypedef *req)
{
  USBD_HID_HandleTypeDef *hhid = (USBD_HID_HandleTypeDef *) pdev->pClassData;
  uint16_t len = 0U;
  uint8_t *pbuf = NULL;
  uint16_t status_info = 0U;
  USBD_StatusTypeDef ret = USBD_OK;

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
    case USB_REQ_TYPE_CLASS :
      switch (req->bRequest)
      {
        case HID_REQ_SET_PROTOCOL:
          hhid->Protocol = (uint8_t)(req->wValue);
          break;

        case HID_REQ_GET_PROTOCOL:
          USBD_CtlSendData(pdev, (uint8_t *)(void *)&hhid->Protocol, 1U);
          break;

        case HID_REQ_SET_IDLE:
          hhid->IdleState = (uint8_t)(req->wValue >> 8);
          break;

        case HID_REQ_GET_IDLE:
          USBD_CtlSendData(pdev, (uint8_t *)(void *)&hhid->IdleState, 1U);
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;
    case USB_REQ_TYPE_STANDARD:
      switch (req->bRequest)
      {
        case USB_REQ_GET_STATUS:
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            USBD_CtlSendData(pdev, (uint8_t *)(void *)&status_info, 2U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_GET_DESCRIPTOR:
          if (req->wValue >> 8 == HID_REPORT_DESC)
          {
            len = MIN(HID_MOUSE_REPORT_DESC_SIZE, req->wLength);
            pbuf = HID_MOUSE_ReportDesc;
          }
          else if (req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
          {
            pbuf = USBD_HID_Desc;
            len = MIN(USB_HID_DESC_SIZ, req->wLength);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
            break;
          }
          USBD_CtlSendData(pdev, pbuf, len);
          break;

        case USB_REQ_GET_INTERFACE :
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            USBD_CtlSendData(pdev, (uint8_t *)(void *)&hhid->AltSetting, 1U);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        case USB_REQ_SET_INTERFACE :
          if (pdev->dev_state == USBD_STATE_CONFIGURED)
          {
            hhid->AltSetting = (uint8_t)(req->wValue);
          }
          else
          {
            USBD_CtlError(pdev, req);
            ret = USBD_FAIL;
          }
          break;

        default:
          USBD_CtlError(pdev, req);
          ret = USBD_FAIL;
          break;
      }
      break;

    default:
      USBD_CtlError(pdev, req);
      ret = USBD_FAIL;
      break;
  }

  return ret;
}

/**
  * @brief  USBD_HID_SendReport
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport(USBD_HandleTypeDef  *pdev,
                            uint8_t *report,
                            uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef *)pdev->pClassData;

  if (pdev->dev_state == USBD_STATE_CONFIGURED)
  {
    if (hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit(pdev,
                       HID_EPIN_ADDR,
                       report,
                       len);
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetPollingInterval
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval(USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0U;

  /* HIGH-speed endpoints */
  if (pdev->dev_speed == USBD_SPEED_HIGH)
  {
    /* Sets the data transfer polling interval for high speed transfers.
     Values between 1..16 are allowed. Values correspond to interval
     of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1U << (HID_HS_BINTERVAL - 1U))) / 8U);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }

  return ((uint32_t)(polling_interval));
}

/**
  * @brief  USBD_HID_GetCfgFSDesc
  *         return FS configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetFSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_HID_CfgFSDesc);
  return USBD_HID_CfgFSDesc;
}

/**
  * @brief  USBD_HID_GetCfgHSDesc
  *         return HS configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetHSCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_HID_CfgHSDesc);
  return USBD_HID_CfgHSDesc;
}

/**
  * @brief  USBD_HID_GetOtherSpeedCfgDesc
  *         return other speed configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetOtherSpeedCfgDesc(uint16_t *length)
{
  *length = sizeof(USBD_HID_OtherSpeedCfgDesc);
  return USBD_HID_OtherSpeedCfgDesc;
}

/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn(USBD_HandleTypeDef *pdev,
                                uint8_t epnum)
{

  /* Ensure that the FIFO is empty before a new transfer, this condition could
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  return USBD_OK;
}


/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t  *USBD_HID_GetDeviceQualifierDesc(uint16_t *length)
{
  *length = sizeof(USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
