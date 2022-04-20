/**
  ******************************************************************************
  * @file    usage_desktop.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2020-09-21
  * @brief   USB Human Interface Device Class
  *          Telephony Usage Page definitions
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
#ifndef __HID_USAGE_TELEPHONY_H_
#define __HID_USAGE_TELEPHONY_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_TELEPHONY        HID_ITEM_1(0x0, GLOBAL, 0x0B)

#define HID_USAGE_TP_PHONE              HID_USAGE_1(0x01)
#define HID_USAGE_TP_ANSWERING_MACHINE  HID_USAGE_1(0x02)
#define HID_USAGE_TP_DUAL_MODE_PHONE    HID_USAGE_2(0x014B)

#define HID_USAGE_TP_MESSAGE_CTRLS      HID_USAGE_1(0x03)
#define HID_USAGE_TP_HANDSET            HID_USAGE_1(0x04)
#define HID_USAGE_TP_HEADSET            HID_USAGE_1(0x05)
#define HID_USAGE_TP_KEY_PAD            HID_USAGE_1(0x06)

#define HID_USAGE_TP_HOOK_SWITCH        HID_USAGE_1(0x20)
#define HID_USAGE_TP_FLASH              HID_USAGE_1(0x21)
#define HID_USAGE_TP_FEATURE            HID_USAGE_1(0x22)
#define HID_USAGE_TP_HOLD               HID_USAGE_1(0x23)
#define HID_USAGE_TP_REDIAL             HID_USAGE_1(0x24)
#define HID_USAGE_TP_TRANSFER           HID_USAGE_1(0x25)
#define HID_USAGE_TP_DROP               HID_USAGE_1(0x26)
#define HID_USAGE_TP_PARK               HID_USAGE_1(0x27)
#define HID_USAGE_TP_ALT_FUNCTION       HID_USAGE_1(0x29)

#define HID_USAGE_TP_RING_ENABLE        HID_USAGE_1(0x2D)

#define HID_USAGE_TP_HOST_CTRL          HID_USAGE_1(0xF0)
#define HID_USAGE_TP_HOST_AVAIL         HID_USAGE_1(0xF1)
#define HID_USAGE_TP_HOST_CALL_ACTIVE   HID_USAGE_1(0xF2)
#define HID_USAGE_TP_ACT_HANDSET_AUDIO  HID_USAGE_1(0xF3)
#define HID_USAGE_TP_RING_TYPE          HID_USAGE_1(0xF4)

#define HID_USAGE_TP_STOP_RING_TONE     HID_USAGE_1(0xF8)
#define HID_USAGE_TP_PSTN_RING_TONE     HID_USAGE_1(0xF9)
#define HID_USAGE_TP_HOST_RING_TONE     HID_USAGE_1(0xFA)

#endif /* __HID_USAGE_TELEPHONY_H_ */
