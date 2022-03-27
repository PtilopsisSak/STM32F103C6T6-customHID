/**
  ******************************************************************************
  * @file    usage_consumer.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-11-18
  * @brief   USB Human Interface Device Class
  *          Consumer Usage Page definitions
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
#ifndef __HID_USAGE_CONSUMER_H_
#define __HID_USAGE_CONSUMER_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_CONSUMER         HID_ITEM_1(0x0, GLOBAL, 0x0C)

#define HID_USAGE_CMR_CONSUMER_CTRL     HID_USAGE_1(0x01)
#define HID_USAGE_CMR_NUM_KEYPAD        HID_USAGE_1(0x02)
#define HID_USAGE_CMR_PROG_BUTTONS      HID_USAGE_1(0x03)
#define HID_USAGE_CMR_MICROPHONE        HID_USAGE_1(0x04)
#define HID_USAGE_CMR_HEADPHONE         HID_USAGE_1(0x05)
#define HID_USAGE_CMR_GRAPHIC_EQ        HID_USAGE_1(0x06)

/* General controls */
#define HID_USAGE_CMR_POWER             HID_USAGE_1(0x30)
#define HID_USAGE_CMR_RESET             HID_USAGE_1(0x31)
#define HID_USAGE_CMR_SLEEP             HID_USAGE_1(0x32)
#define HID_USAGE_CMR_SLEEP_AFTER       HID_USAGE_1(0x33)
#define HID_USAGE_CMR_SLEEP_MODE        HID_USAGE_1(0x34)
#define HID_USAGE_CMR_ILLUMINATION      HID_USAGE_1(0x35)
#define HID_USAGE_CMR_FUNCTION_BUTTONS  HID_USAGE_1(0x36)

/* Menu controls */
#define HID_USAGE_CMR_MENU              HID_USAGE_1(0x40)
#define HID_USAGE_CMR_MENU_PICK         HID_USAGE_1(0x41)
#define HID_USAGE_CMR_MENU_UP           HID_USAGE_1(0x42)
#define HID_USAGE_CMR_MENU_DOWN         HID_USAGE_1(0x43)
#define HID_USAGE_CMR_MENU_LEFT         HID_USAGE_1(0x44)
#define HID_USAGE_CMR_MENU_RIGHT        HID_USAGE_1(0x45)
#define HID_USAGE_CMR_MENU_ESC          HID_USAGE_1(0x46)
#define HID_USAGE_CMR_MENU_VALUE_INC    HID_USAGE_1(0x47)
#define HID_USAGE_CMR_MENU_VALUE_DEC    HID_USAGE_1(0x48)

/* Transport controls */
#define HID_USAGE_CMR_PLAY              HID_USAGE_1(0xB0)
#define HID_USAGE_CMR_PAUSE             HID_USAGE_1(0xB1)
#define HID_USAGE_CMR_PLAY_PAUSE        HID_USAGE_1(0xCD)
#define HID_USAGE_CMR_PLAY_SKIP         HID_USAGE_1(0xCE)
#define HID_USAGE_CMR_RECORD            HID_USAGE_1(0xB2)
#define HID_USAGE_CMR_FFWD              HID_USAGE_1(0xB3)
#define HID_USAGE_CMR_REWIND            HID_USAGE_1(0xB4)
#define HID_USAGE_CMR_SCAN_NEXT         HID_USAGE_1(0xB5)
#define HID_USAGE_CMR_SCAN_PREV         HID_USAGE_1(0xB6)
#define HID_USAGE_CMR_STOP              HID_USAGE_1(0xB7)
#define HID_USAGE_CMR_EJECT             HID_USAGE_1(0xB8)
#define HID_USAGE_CMR_STOP_EJECT        HID_USAGE_1(0xCC)
#define HID_USAGE_CMR_SHUFFLE           HID_USAGE_1(0xB9)
#define HID_USAGE_CMR_REPEAT            HID_USAGE_1(0xBC)

/* Audio controls */
#define HID_USAGE_CMR_VOLUME            HID_USAGE_1(0xE0)
#define HID_USAGE_CMR_VOLUME_INC        HID_USAGE_1(0xE9)
#define HID_USAGE_CMR_VOLUME_DEC        HID_USAGE_1(0xEA)
#define HID_USAGE_CMR_BALANCE           HID_USAGE_1(0xE1)
#define HID_USAGE_CMR_BALANCE_RIGHT     HID_USAGE_2(0x0150)
#define HID_USAGE_CMR_BALANCE_LEFT      HID_USAGE_2(0x0151)
#define HID_USAGE_CMR_MUTE              HID_USAGE_1(0xE2)
#define HID_USAGE_CMR_BASS              HID_USAGE_1(0xE3)
#define HID_USAGE_CMR_BASS_INC          HID_USAGE_2(0x0152)
#define HID_USAGE_CMR_BASS_DEC          HID_USAGE_2(0x0153)
#define HID_USAGE_CMR_TREBLE            HID_USAGE_1(0xE4)
#define HID_USAGE_CMR_TREBLE_INC        HID_USAGE_2(0x0154)
#define HID_USAGE_CMR_TREBLE_DEC        HID_USAGE_2(0x0155)
#define HID_USAGE_CMR_BASS_BOOST        HID_USAGE_1(0xE5)


#endif /* __HID_USAGE_CONSUMER_H_ */
