/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : usbd_custom_hid_if.c
 * @version        : v2.0_Cube
 * @brief          : USB Device Custom HID interface file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
 * @brief Usb device.
 * @{
 */

/** @addtogroup USBD_CUSTOM_HID
 * @{
 */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
 * @brief Private types.
 * @{
 */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
 * @brief Private defines.
 * @{
 */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
 * @brief Private macros.
 * @{
 */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
 * @brief Private variables.
 * @{
 */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
    {
        /* USER CODE BEGIN 0 */

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
                          // 0xc0              // END_COLLECTION
        /* USER CODE END 0 */
        0xC0 /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
 * @brief Public variables.
 * @{
 */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
 * @}
 */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
 * @brief Private functions declaration.
 * @{
 */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
 * @}
 */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
    {
        CUSTOM_HID_ReportDesc_FS,
        CUSTOM_HID_Init_FS,
        CUSTOM_HID_DeInit_FS,
        CUSTOM_HID_OutEvent_FS};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
 * @brief Private functions.
 * @{
 */

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
 * @brief  DeInitializes the CUSTOM HID media low layer
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
 * @brief  Manage the CUSTOM HID class events
 * @param  event_idx: Event index
 * @param  state: Event state
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
__weak int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
			// for(uint16_t i=0;i<64;i++)
			  // (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData->Report_buf[i];
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
 * @brief  Send the report to the Host
 * @param  report: The report to be sent
 * @param  len: The report length
 * @retval USBD_OK if all operations are OK else USBD_FAIL
 */
int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
