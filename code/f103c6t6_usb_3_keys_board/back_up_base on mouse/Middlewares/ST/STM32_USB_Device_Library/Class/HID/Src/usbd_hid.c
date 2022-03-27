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

        //-------------键盘部分报告描述符----------------
        //表示用途页为通用桌面设备
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)

        //表示用途为键盘
        0x09, 0x06, // USAGE (Keyboard)

        //表示应用集合，必须要以END_COLLECTION来结束它，见最后的END_COLLECTION
        0xa1, 0x01, // COLLECTION (Application)

        //报告ID（报告ID 0是保留的）
        0x85, 0x01, // Report ID (1)

        //表示用途页为按键
        0x05, 0x07, //   USAGE_PAGE (Keyboard)

        //用途最小值，这里为左ctrl键
        0x19, 0xe0, //   USAGE_MINIMUM (Keyboard LeftControl)
                    //用途最大值，这里为右GUI键，即window键
        0x29, 0xe7, //   USAGE_MAXIMUM (Keyboard Right GUI)
                    //逻辑最小值为0
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
                    //逻辑最大值为1
        0x25, 0x01, //   LOGICAL_MAXIMUM (1)
                    //报告大小（即这个字段的宽度）为1bit，所以前面的逻辑最小值为0，逻辑最大值为1
        0x75, 0x01, //   REPORT_SIZE (1)
                    //报告的个数为8，即总共有8个bits
        0x95, 0x08, //   REPORT_COUNT (8)
                    //输入用，变量，值，绝对值。像键盘这类一般报告绝对值，
                    //而鼠标移动这样的则报告相对值，表示鼠标移动多少
        0x81, 0x02, //   INPUT (Data,Var,Abs)
                    //上面这这几项描述了一个输入用的字段，总共为8个bits，每个bit表示一个按键
                    //分别从左ctrl键到右GUI键。这8个bits刚好构成一个字节，它位于报告的第一个字节。
                    //它的最低位，即bit-0对应着左ctrl键，如果返回的数据该位为1，则表示左ctrl键被按下，
                    //否则，左ctrl键没有按下。最高位，即bit-7表示右GUI键的按下情况。中间的几个位，
                    //需要根据HID协议中规定的用途页表（HID Usage Tables）来确定。这里通常用来表示
                    //特殊键，例如ctrl，shift，del键等

        //这样的数据段个数为1
        0x95, 0x01, //   REPORT_COUNT (1)
                    //每个段长度为8bits
        0x75, 0x08, //   REPORT_SIZE (8)
                    //输入用，常量，值，绝对值
        0x81, 0x03, //   INPUT (Cnst,Var,Abs)

        //上面这8个bit是常量，设备必须返回0

        //这样的数据段个数为5
        0x95, 0x05, //   REPORT_COUNT (5)
                    //每个段大小为1bit
        0x75, 0x01, //   REPORT_SIZE (1)
                    //用途是LED，即用来控制键盘上的LED用的，因此下面会说明它是输出用
        0x05, 0x08, //   USAGE_PAGE (LEDs)
                    //用途最小值是Num Lock，即数字键锁定灯
        0x19, 0x01, //   USAGE_MINIMUM (Num Lock)
                    //用途最大值是Kana，这个是什么灯我也不清楚^_^
        0x29, 0x05, //   USAGE_MAXIMUM (Kana)
                    //如前面所说，这个字段是输出用的，用来控制LED。变量，值，绝对值。
                    // 1表示灯亮，0表示灯灭
        0x91, 0x02, //   OUTPUT (Data,Var,Abs)

        //这样的数据段个数为1
        0x95, 0x01, //   REPORT_COUNT (1)
                    //每个段大小为3bits
        0x75, 0x03, //   REPORT_SIZE (3)
                    //输出用，常量，值，绝对
        0x91, 0x03, //   OUTPUT (Cnst,Var,Abs)
                    //由于要按字节对齐，而前面控制LED的只用了5个bit，
                    //所以后面需要附加3个不用bit，设置为常量。

        //报告个数为6
        0x95, 0x06, //   REPORT_COUNT (6)
                    //每个段大小为8bits
        0x75, 0x08, //   REPORT_SIZE (8)
                    //逻辑最小值0
        0x15, 0x00, //   LOGICAL_MINIMUM (0)
                    //逻辑最大值255
        0x25, 0xFF, //   LOGICAL_MAXIMUM (255)
                    //用途页为按键
        0x05, 0x07, //   USAGE_PAGE (Keyboard)
                    //使用最小值为0
        0x19, 0x00, //   USAGE_MINIMUM (Reserved (no event indicated))
                    //使用最大值为0x65
        0x29, 0x65, //   USAGE_MAXIMUM (Keyboard Application)
                    //输入用，变量，数组，绝对值
        0x81, 0x00, //   INPUT (Data,Ary,Abs)
                    //以上定义了6个8bit宽的数组，每个8bit（即一个字节）用来表示一个按键，所以可以同时
                    //有6个按键按下。没有按键按下时，全部返回0。如果按下的键太多，导致键盘扫描系统
                    //无法区分按键时，则全部返回0x01，即6个0x01。如果有一个键按下，则这6个字节中的第一
                    //个字节为相应的键值（具体的值参看HID Usage Tables），如果两个键按下，则第1、2两个
                    //字节分别为相应的键值，以次类推。

        //关集合，跟上面的对应
        0xc0, // END_COLLECTION

        //-----------------------鼠标部分报告描述符----------------------------
        0x05, 0x01, // USAGE_PAGE (Generic Desktop)
        0x09, 0x02, // USAGE (Mouse)
        0xa1, 0x01, // COLLECTION (Application)
        0x85, 0x02, // 报告ID (2)
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
        // 0x85, 0x04,       // 报告ID (4)
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
        0x85, 0x06,       // 报告ID (2)
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
