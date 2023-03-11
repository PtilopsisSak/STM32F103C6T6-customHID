# 基于 STM32F103C6T6 的一个 usbhid 复合设备的工程模板

依靠 32 模拟成自定义 hid 设备, 目前实现了鼠标, 键盘, 触摸屏, 实现了数据接收, 一端点复合设备

### 如何从头开始实现, 教程

首先这个是基于CubeMx的, 需要配置基础USB相关配置, 

1. 选择HID设备即可, 两种都行, 以Custom HID为例

2. CubeMx中配置一些基础设置, 比如设备名称以及VID, PID等描述

3. 改电脑轮询间隔

   ```c
   // USB_DEVICE\Target\usbd_conf.h
   // 单位为ms, 最小1ms轮询, 可以在CubeMx中找到配置
   #define CUSTOM_HID_FS_BINTERVAL 0x1
   ```

4. 输出缓冲

   ```c
   // USB_DEVICE\Target\usbd_conf.h
   // 建议64Byte, 最大为64
   #define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE 64
   ```

5. 设备描述

   ```c
   // USB_DEVICE\App\usbd_desc.c
   #define USBD_VID     6666                                        // 生产商ID
   #define USBD_LANGID_STRING     1033                              // 不知道
   #define USBD_MANUFACTURER_STRING     "NJUST 6003-Ptisak LAB INC" // 生产商名字
   #define USBD_PID_FS     23333                                    // 产品ID, 每个产品唯一
   #define USBD_PRODUCT_STRING_FS     "Ptisak Pia !(o `~')/''"      // 产品名字
   #define USBD_CONFIGURATION_STRING_FS     "PSK INF"               // 可以改
   #define USBD_INTERFACE_STRING_FS     "PSK HID INTERFACE"         // 可以改
   ```

6. 设备描述符

   ```c
   // USB_DEVICE\App\usbd_custom_hid_if.c
   // 该部分比较重要, 该部分内容告诉电脑自己有哪些上报数据以及每位对应的作用, 数组长度最大255
   __ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
       {
           /* USER CODE BEGIN 0 */
       // 略
           /* USER CODE END 0 */
           0xC0 /*     END_COLLECTION	             */
   };
   ```

7. 设备描述符大小

   ```c
   // USB_DEVICE\Target\usbd_conf.h
   // 该部分为上方数组的大小, 必须完全匹配, 最大255
   #define USBD_CUSTOM_HID_REPORT_DESC_SIZE 251
   ```

8. 了解发送函数

   ```c
   // USB_DEVICE\App\usbd_custom_hid_if.c
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
   ```

9. 了解接收中断

   ```c
   // Middlewares\ST\STM32_USB_Device_Library\Class\CustomHID\Src\usbd_customhid.c
   /**
    * @brief  USBD_CUSTOM_HID_DataOut
    *         handle data OUT Stage
    * @param  pdev: device instance
    * @param  epnum: endpoint index
    * @retval status
    */
   static uint8_t USBD_CUSTOM_HID_DataOut(USBD_HandleTypeDef *pdev,
                                          uint8_t epnum)
   {
   
     USBD_CUSTOM_HID_HandleTypeDef *hhid = (USBD_CUSTOM_HID_HandleTypeDef *)pdev->pClassData;
   
     ((USBD_CUSTOM_HID_ItfTypeDef *)pdev->pUserData)->OutEvent(hhid->Report_buf[0], hhid->Report_buf[1]);
   
     USBD_LL_PrepareReceive(pdev, CUSTOM_HID_EPOUT_ADDR, hhid->Report_buf,
                            USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
   // 自己的函数, hid_dev\psk_hid.c 接管
     extern void hid_rx_iqr(uint8_t rx_data[64]);
     hid_rx_iqr(hhid->Report_buf);
   // End
     return USBD_OK;
   }
   ```

10. 

#### 注意

改了文件, 用 cubemx 生成工程前请先备份 Middlewares 和 USB_DEVICE 这两个文件夹
生成完用备份的替换掉生成后的

#### 如何使用

引用头文件

```c
#include "psk_hid.h"
```

准备一个 5ms 定时器发送四个数据, 最好来一个稍大于 1ms 的定时器分开发送, 因为电脑接收数据包最短 1ms 轮询

(可以只发送想要用的几个)

我开了一个 1.25ms 的定时器, 分了四次执行发送数据包的代码

```c
void TIM1_IRQ(void)
{
  if (LL_TIM_IsActiveFlag_UPDATE(TIM1) == SET)
  {
    LL_TIM_ClearFlag_UPDATE(TIM1); // 1.25 ms
    static uint8_t i;
    switch (i)
    {
    case 0:
      send_keyboard_data();
      break;
    case 1:
      send_custom_control_data();
      break;
    case 2:
      send_touch_data();
      break;
    default:
      send_mouse_data();
    }
    i = (i + 1) % 4;
  }
}
```

初始化(可以只初始化几个)

```c
  mouse_init();
  keyboard_init();
  custom_init();
  touch_init();
```

开始愉快的玩耍吧

```c
void shutdown(void)
{
  keyboard_press_sp_key(LEFT_GUI, 2);
  keyboard_press_char('x', 2);
  keyboard_delay(100);
  keyboard_press_sp_key(LEFT_GUI, 2);
  keyboard_press_char('x', 2);
  keyboard_delay(50);
  keyboard_press_str("uuuuuuuuuuuuuuuuuuu\n", 1);
}
mouse_move(100, 100);
custom_press_key(VOL_DOWN, 1);
keyboard_press_str("hello world", 1);
touch_set_pos(666, 666);
touch_set_time(100);
```

#### 关于USB数据接收

数据接收中断回调函数在psk_hid.c里, 目前接收了键盘的三个指示灯

#### 更详细的使用见四个头文件

```c
#include "mouse.h"
#include "keyboard.h"
#include "touch_screen.h"
#include "custom_control.h"
```

#### 自定义

找到 usbd_desc.c, 修改部分代码 65 行左右

```c
#define USBD_VID     6666                                        // 生产商ID
#define USBD_LANGID_STRING     1033                              // 不知道
#define USBD_MANUFACTURER_STRING     "NJUST 6003-Ptisak LAB INC" // 生产商名字
#define USBD_PID_FS     23333                                    // 产品ID, 每个产品唯一, 自己修改
#define USBD_PRODUCT_STRING_FS     "Ptisak Pia !(o `~')/''"      // 产品名字
#define USBD_CONFIGURATION_STRING_FS     "PSK INF"               // 可以改
#define USBD_INTERFACE_STRING_FS     "PSK HID INTERFACE"         // 可以改
```

改设备描述符(不建议, 因为改了后可能每个设备的报告 ID 要改)



#### 不同芯片可按照上方教程改, 只需要hid_dev中的文件就行了(键盘还需要lwrb.c, 鼠标可选pid.c)

开始咕咕咕