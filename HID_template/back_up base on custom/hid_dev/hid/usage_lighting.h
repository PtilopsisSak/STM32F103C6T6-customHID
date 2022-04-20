/**
  ******************************************************************************
  * @file    usage_lighting.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-01-31
  * @brief   USB Human Interface Device Class
  *          Lighting and Illumination Usage Page definitions
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
#ifndef __HID_USAGE_LIGHITNG_H_
#define __HID_USAGE_LIGHITNG_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_LIGHTING                 HID_ITEM_1(0x0, GLOBAL, 0x59)

#define HID_USAGE_LI_LAMPARRAY                  HID_USAGE_1(0x01)

#define HID_USAGE_LI_LA_ATTR_REPORT             HID_USAGE_1(0x02)
#define HID_USAGE_LI_LAMPCOUNT                  HID_USAGE_1(0x03)
#define HID_USAGE_LI_BOUNDINGBOX_X              HID_USAGE_1(0x04) /* In micrometers */
#define HID_USAGE_LI_BOUNDINGBOX_Y              HID_USAGE_1(0x05) /* In micrometers */
#define HID_USAGE_LI_BOUNDINGBOX_Z              HID_USAGE_1(0x06) /* In micrometers */
#define HID_USAGE_LI_LA_KIND                    HID_USAGE_1(0x07)
typedef enum {
    LampArrayKindKeyboard = 1,
    LampArrayKindMouse,
    LampArrayKindGameController,
    LampArrayKindPeripheral,
    LampArrayKindScene,
    LampArrayKindNotification,
    LampArrayKindChassis,
    LampArrayKindWearable,
    LampArrayKindFurniture,
    LampArrayKindArt,
}LampArrayKind_t;
#define HID_USAGE_LI_MIN_UPDATE_INTERVAL        HID_USAGE_1(0x08) /* In microseconds */

#define HID_USAGE_LI_LAMP_ATTR_REQ_REPORT       HID_USAGE_1(0x20)
#define HID_USAGE_LI_LAMPID                     HID_USAGE_1(0x21)

#define HID_USAGE_LI_LAMP_ATTR_RESP_REPORT      HID_USAGE_1(0x22)
#define HID_USAGE_LI_POSITION_X                 HID_USAGE_1(0x23) /* In micrometers */
#define HID_USAGE_LI_POSITION_Y                 HID_USAGE_1(0x24) /* In micrometers */
#define HID_USAGE_LI_POSITION_Z                 HID_USAGE_1(0x25) /* In micrometers */
#define HID_USAGE_LI_LAMP_PURPOSES              HID_USAGE_1(0x26)
typedef enum {
    LampPurposeControl = 0x01,
    LampPurposeAccent = 0x02,
    LampPurposeBranding = 0x04,
    LampPurposeStatus = 0x08,
    LampPurposeIllumination = 0x10,
    LampPurposePresentation = 0x20,
}LampPurpose_t;
#define HID_USAGE_LI_UPDATE_LATENCY             HID_USAGE_1(0x27) /* In microseconds */
#define HID_USAGE_LI_RED_LEVEL_COUNT            HID_USAGE_1(0x28)
#define HID_USAGE_LI_GREEN_LEVEL_COUNT          HID_USAGE_1(0x29)
#define HID_USAGE_LI_BLUE_LEVEL_COUNT           HID_USAGE_1(0x2A)
#define HID_USAGE_LI_INTENSITY_LEVEL_COUNT      HID_USAGE_1(0x2B)
#define HID_USAGE_LI_PROGRAMMABLE               HID_USAGE_1(0x2C)

#define HID_USAGE_LI_LAMP_MULTI_UPDATE_REPORT   HID_USAGE_1(0x50)
#define HID_USAGE_LI_RED_UPDATE_CHANNEL         HID_USAGE_1(0x51)
#define HID_USAGE_LI_GREEN_UPDATE_CHANNEL       HID_USAGE_1(0x52)
#define HID_USAGE_LI_BLUE_UPDATE_CHANNEL        HID_USAGE_1(0x53)
#define HID_USAGE_LI_INTENSITY_UPDATE_CHANNEL   HID_USAGE_1(0x54)
#define HID_USAGE_LI_LAMP_UPDATE_FLAGS          HID_USAGE_1(0x55)
typedef enum {
    LampUpdateComplete = 0x01,
}LampUpdateFlags_t;

#define HID_USAGE_LI_LAMP_RANGE_UPDATE_REPORT   HID_USAGE_1(0x60)
#define HID_USAGE_LI_LAMPID_START               HID_USAGE_1(0x61)
#define HID_USAGE_LI_LAMPID_END                 HID_USAGE_1(0x62)

#define HID_USAGE_LI_LA_CTRL_REPORT             HID_USAGE_1(0x70)
#define HID_USAGE_LI_AUTONOMOUS_MODE            HID_USAGE_1(0x71)

#endif /* __HID_USAGE_LIGHITNG_H_ */
