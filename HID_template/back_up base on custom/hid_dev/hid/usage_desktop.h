/**
  ******************************************************************************
  * @file    usage_desktop.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-01-31
  * @brief   USB Human Interface Device Class
  *          Desktop Usage Page definitions
  *
  * Copyright (c) 2018 Benedek Kupper
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */
#ifndef __HID_USAGE_DESKTOP_H_
#define __HID_USAGE_DESKTOP_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_DESKTOP          HID_ITEM_1(0x0, GLOBAL, 0x01)

#define HID_USAGE_DT_POINTER            HID_USAGE_1(0x01)
#define HID_USAGE_DT_MOUSE              HID_USAGE_1(0x02)
#define HID_USAGE_DT_JOYSTICK           HID_USAGE_1(0x04)
#define HID_USAGE_DT_GAMEPAD            HID_USAGE_1(0x05)
#define HID_USAGE_DT_KEYBOARD           HID_USAGE_1(0x06)
#define HID_USAGE_DT_KEYPAD             HID_USAGE_1(0x07)
#define HID_USAGE_DT_MULTI_AXIS_CTRL    HID_USAGE_1(0x08)

#define HID_USAGE_DT_X                  HID_USAGE_1(0x30)
#define HID_USAGE_DT_Y                  HID_USAGE_1(0x31)
#define HID_USAGE_DT_Z                  HID_USAGE_1(0x32)
#define HID_USAGE_DT_RX                 HID_USAGE_1(0x33)
#define HID_USAGE_DT_RY                 HID_USAGE_1(0x34)
#define HID_USAGE_DT_RZ                 HID_USAGE_1(0x35)
#define HID_USAGE_DT_WHEEL              HID_USAGE_1(0x38)
#define HID_USAGE_DT_MOTION_WAKEUP      HID_USAGE_1(0x3C)

#define HID_USAGE_DT_RESOLUTION_MULT    HID_USAGE_1(0x48)

#define HID_USAGE_DT_SYS_CTRL           HID_USAGE_1(0x80)
#define HID_USAGE_DT_SYS_POWER_DOWN     HID_USAGE_1(0x81)
#define HID_USAGE_DT_SYS_SLEEP          HID_USAGE_1(0x82)
#define HID_USAGE_DT_SYS_WAKEUP         HID_USAGE_1(0x83)


#endif /* __HID_USAGE_DESKTOP_H_ */
