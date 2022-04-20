# 基于 STM32F103C6T6 的一个 usbhid 复合设备的工程模板

依靠 32 模拟成自定义 hid 设备, 目前实现了鼠标, 键盘, 触摸屏, 实现了数据接收

#### 注意

用 cubemx 生成工程前请先备份 Middlewares 和 USB_DEVICE 这两个文件夹
生成完用备份的替换掉生成后的

#### 如何使用

引用头文件

```c
#include "psk_hid.h"
```

准备一个 5ms 定时器发送四个数据, 最好来一个稍大于 1ms 的定时器分开发送, 因为电脑接收数据包最短 1ms 轮询

(可以只发送想要用的几个)

我开了一个 1.25ms 的定时器, 分了四次执行发送数据包的代码, 可以把丢包率降到最低

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
```

#### 自定义

找到 usbd_desc.c, 修改部分代码 65 行左右

```c
#define USBD_VID     6666                                        // 生产商ID
#define USBD_LANGID_STRING     1033                              // 不知道
#define USBD_MANUFACTURER_STRING     "NJUST 6003-Ptisak LAB INC" // 生产商名字
#define USBD_PID_FS     23333                                    // 产品ID, 每个产品唯一, 最好自己修改
#define USBD_PRODUCT_STRING_FS     "Ptisak Pia !(o `~')/''"      // 产品名字
#define USBD_CONFIGURATION_STRING_FS     "PSK INF"               // 配置字段, 可以改
#define USBD_INTERFACE_STRING_FS     "PSK HID INTERFACE"         // 可以改
```

改设备描述符(不建议, 因为改了后可能每个设备的报告 ID 要改)
usbd_custom_hid_if.c , 91 行
CUSTOM_HID_ReportDesc_FS <- 这个是设备描述符数组
USBD_CUSTOM_HID_REPORT_DESC_SIZE <- 这个是长度, 必须和设备描述符数组长度匹配
