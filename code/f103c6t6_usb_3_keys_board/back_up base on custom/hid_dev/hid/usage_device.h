/**
  ******************************************************************************
  * @file    usage_device.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2020-04-02
  * @brief   USB Human Interface Device Class
  *          Generic Device Usage Page definitions
  *
  * Copyright (c) 2020 Benedek Kupper
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
#ifndef __HID_USAGE_DEVICE_H_
#define __HID_USAGE_DEVICE_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_DEVICE       HID_ITEM_1(0x0, GLOBAL, 0x06)

#define HID_USAGE_DEV_BKGND_CTRLS   HID_USAGE_1(0x01)

#define HID_USAGE_DEV_BATTERY_STR   HID_USAGE_1(0x20)

#define HID_USAGE_DEV_SW_VER        HID_USAGE_1(0x2A)
#define HID_USAGE_DEV_PROT_VER      HID_USAGE_1(0x2B)
#define HID_USAGE_DEV_HW_VER        HID_USAGE_1(0x2C)
#define HID_USAGE_DEV_MAJOR         HID_USAGE_1(0x2D)
#define HID_USAGE_DEV_MINOR         HID_USAGE_1(0x2E)
#define HID_USAGE_DEV_REVISION      HID_USAGE_1(0x2F)

#define HID_USAGE_DEV_HANDEDNESS    HID_USAGE_1(0x30)
#define HID_USAGE_DEV_HAND_EITHER   HID_USAGE_1(0x31)
#define HID_USAGE_DEV_HAND_LEFT     HID_USAGE_1(0x32)
#define HID_USAGE_DEV_HAND_RIGHT    HID_USAGE_1(0x33)
#define HID_USAGE_DEV_HAND_BOTH     HID_USAGE_1(0x34)

#endif /* __HID_USAGE_DEVICE_H_ */
