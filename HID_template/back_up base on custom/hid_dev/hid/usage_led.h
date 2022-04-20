/**
  ******************************************************************************
  * @file    usage_led.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-01-31
  * @brief   USB Human Interface Device Class
  *          LED Usage Page definitions
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
#ifndef __HID_USAGE_LED_H_
#define __HID_USAGE_LED_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_LED          HID_ITEM_1(0x0, GLOBAL, 0x08)

/* General device indicators */
#define HID_USAGE_LED_POWER         HID_USAGE_1(0x06)
#define HID_USAGE_LED_BATTERY_OP    HID_USAGE_1(0x1B)
#define HID_USAGE_LED_BATTERY_OK    HID_USAGE_1(0x1C)
#define HID_USAGE_LED_BATTERY_LOW   HID_USAGE_1(0x1D)
#define HID_USAGE_LED_STANDBY       HID_USAGE_1(0x27)
#define HID_USAGE_LED_ONLINE        HID_USAGE_1(0x2A)
#define HID_USAGE_LED_OFFLINE       HID_USAGE_1(0x2B)
#define HID_USAGE_LED_BUSY          HID_USAGE_1(0x2C)
#define HID_USAGE_LED_READY         HID_USAGE_1(0x2D)
#define HID_USAGE_LED_ERROR         HID_USAGE_1(0x39)
#define HID_USAGE_LED_SUSPEND       HID_USAGE_1(0x4C)
#define HID_USAGE_LED_EXT_POWERED   HID_USAGE_1(0x4D)

#define HID_USAGE_LED_SELECTED              HID_USAGE_1(0x3A)
#define HID_USAGE_LED_IN_USE                HID_USAGE_1(0x3B)
#define HID_USAGE_LED_MULTI_MODE            HID_USAGE_1(0x3C)
#define HID_USAGE_LED_MODE_ON               HID_USAGE_1(0x3D)
#define HID_USAGE_LED_MODE_FLASH            HID_USAGE_1(0x3E)
#define HID_USAGE_LED_MODE_SLOW_BLINK       HID_USAGE_1(0x3F)
#define HID_USAGE_LED_MODE_FAST_BLINK       HID_USAGE_1(0x40)
#define HID_USAGE_LED_MODE_OFF              HID_USAGE_1(0x41)
#define HID_USAGE_LED_TIME_FLASH_ON         HID_USAGE_1(0x42)
#define HID_USAGE_LED_TIME_SLOW_BLINK_ON    HID_USAGE_1(0x43)
#define HID_USAGE_LED_TIME_SLOW_BLINK_OFF   HID_USAGE_1(0x44)
#define HID_USAGE_LED_TIME_FAST_BLINK_ON    HID_USAGE_1(0x45)
#define HID_USAGE_LED_TIME_FAST_BLINK_OFF   HID_USAGE_1(0x46)
#define HID_USAGE_LED_COLOR                 HID_USAGE_1(0x47)
#define HID_USAGE_LED_COLOR_RED             HID_USAGE_1(0x48)
#define HID_USAGE_LED_COLOR_GREEN           HID_USAGE_1(0x49)
#define HID_USAGE_LED_COLOR_AMBER           HID_USAGE_1(0x4A)

/* Keyboard indicators */
#define HID_USAGE_LED_NUMLOCK       HID_USAGE_1(0x01)
#define HID_USAGE_LED_CAPSLOCK      HID_USAGE_1(0x02)
#define HID_USAGE_LED_SCROLLLOCK    HID_USAGE_1(0x03)

/* Consumer indicators */
#define HID_USAGE_LED_MUTE          HID_USAGE_1(0x09)
#define HID_USAGE_LED_CAMERA_ON     HID_USAGE_1(0x28)
#define HID_USAGE_LED_CAMERA_OFF    HID_USAGE_1(0x29)

/* Telephony indicators */
#define HID_USAGE_LED_MICROPHONE    HID_USAGE_1(0x21)

/* Media transport indicators */
#define HID_USAGE_LED_FORWARD       HID_USAGE_1(0x31)
#define HID_USAGE_LED_REVERSE       HID_USAGE_1(0x32)
#define HID_USAGE_LED_STOP          HID_USAGE_1(0x33)
#define HID_USAGE_LED_REWIND        HID_USAGE_1(0x34)
#define HID_USAGE_LED_FFWD          HID_USAGE_1(0x35)
#define HID_USAGE_LED_PLAY          HID_USAGE_1(0x36)
#define HID_USAGE_LED_PAUSE         HID_USAGE_1(0x37)


#endif /* __HID_USAGE_LED_H_ */
