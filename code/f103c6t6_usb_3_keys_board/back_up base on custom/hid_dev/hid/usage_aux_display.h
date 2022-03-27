/**
  ******************************************************************************
  * @file    usage_aux_display.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2019-04-28
  * @brief   USB Human Interface Device Class
  *          Auxiliary Display Usage Page definitions
  *
  * Copyright (c) 2019 Benedek Kupper
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
#ifndef __HID_USAGE_AUX_DISPLAY_H_
#define __HID_USAGE_AUX_DISPLAY_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_AUX_DISPLAY          HID_ITEM_1(0x0, GLOBAL, 0x14)

#define HID_USAGE_AD_ALPHANUM_DISPLAY       HID_USAGE_1(0x01)
#define HID_USAGE_AD_AUX_DISPLAY            HID_USAGE_1(0x02)
#define HID_USAGE_AD_DISPLAY_ATTR_REPORT    HID_USAGE_1(0x20)
#define HID_USAGE_AD_ASCII_CHARSET          HID_USAGE_1(0x21)
#define HID_USAGE_AD_DATA_READ_BACK         HID_USAGE_1(0x22)
#define HID_USAGE_AD_FONT_READ_BACK         HID_USAGE_1(0x23)
#define HID_USAGE_AD_DISPLAY_CTRL_REPORT    HID_USAGE_1(0x24)
#define HID_USAGE_AD_CLEAR_DISPLAY          HID_USAGE_1(0x25)
#define HID_USAGE_AD_DISPLAY_ENABLE         HID_USAGE_1(0x26)

#define HID_USAGE_AD_SCREENSAVER_DELAY      HID_USAGE_1(0x27)
#define HID_USAGE_AD_SCREENSAVER_ENABLE     HID_USAGE_1(0x28)
#define HID_USAGE_AD_VERTICAL_SCROLL        HID_USAGE_1(0x29)
#define HID_USAGE_AD_HORIZONTAL_SCROLL      HID_USAGE_1(0x2a)
#define HID_USAGE_AD_CHAR_REPORT            HID_USAGE_1(0x2b)
#define HID_USAGE_AD_DISPLAY_DATA           HID_USAGE_1(0x2c)
#define HID_USAGE_AD_DISPLAY_STATUS         HID_USAGE_1(0x2d)
#define HID_USAGE_AD_STAT_NOT_READY         HID_USAGE_1(0x2e)
#define HID_USAGE_AD_STAT_READY             HID_USAGE_1(0x2f)
#define HID_USAGE_AD_ERR_INVALID_CHAR       HID_USAGE_1(0x30)
#define HID_USAGE_AD_ERR_FONT_DATA          HID_USAGE_1(0x31)

#define HID_USAGE_AD_ROWS                   HID_USAGE_1(0x35)
#define HID_USAGE_AD_COLUMNS                HID_USAGE_1(0x36)

#define HID_USAGE_AD_UNICODE_CHARSET        HID_USAGE_1(0x41)
#define HID_USAGE_AD_FONT_7SEGMENT          HID_USAGE_1(0x42)
#define HID_USAGE_AD_7SEGMENT_DIRECT_MAP    HID_USAGE_1(0x43)
#define HID_USAGE_AD_FONT_14SEGMENT         HID_USAGE_1(0x44)
#define HID_USAGE_AD_14SEGMENT_DIRECT_MAP   HID_USAGE_1(0x45)
#define HID_USAGE_AD_DISPLAY_BRIGHTNESS     HID_USAGE_1(0x46)
#define HID_USAGE_AD_DISPLAY_CONTRAST       HID_USAGE_1(0x47)
#define HID_USAGE_AD_CHAR_ATTR              HID_USAGE_1(0x48)
#define HID_USAGE_AD_ATTR_READ_BACK         HID_USAGE_1(0x49)
#define HID_USAGE_AD_ATTR_DATA              HID_USAGE_1(0x4a)

#endif /* __HID_USAGE_AUX_DISPLAY_H_ */
