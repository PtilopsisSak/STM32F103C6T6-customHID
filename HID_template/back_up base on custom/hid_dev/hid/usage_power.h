/**
  ******************************************************************************
  * @file    usage_power.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2018-01-31
  * @brief   USB Human Interface Device Class
  *          Power Device Usage Page definitions
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
#ifndef __HID_USAGE_POWER_H_
#define __HID_USAGE_POWER_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_POWER_DEVICE     HID_ITEM_1(0x0, GLOBAL, 0x84)

#define HID_USAGE_PS_INAME              HID_USAGE_1(0x01)
#define HID_USAGE_PS_PRESENT_STATUS     HID_USAGE_1(0x02)
#define HID_USAGE_PS_CHANGED_STATUS     HID_USAGE_1(0x03)
#define HID_USAGE_PS_UPS                HID_USAGE_1(0x04)
#define HID_USAGE_PS_POWER_SUPPLY       HID_USAGE_1(0x05)
#define HID_USAGE_PS_PERIPHERAL         HID_USAGE_1(0x06)
#define HID_USAGE_PS_BATTERY_SYSTEM     HID_USAGE_1(0x10)
#define HID_USAGE_PS_BATTERY_SYSTEM_ID  HID_USAGE_1(0x11)
#define HID_USAGE_PS_BATTERY            HID_USAGE_1(0x12)
#define HID_USAGE_PS_BATTERY_ID         HID_USAGE_1(0x13)
#define HID_USAGE_PS_CHARGER            HID_USAGE_1(0x14)
#define HID_USAGE_PS_CHARGER_ID         HID_USAGE_1(0x15)
#define HID_USAGE_PS_POWER_CONVERTER    HID_USAGE_1(0x16)
#define HID_USAGE_PS_POWER_CONVERTER_ID HID_USAGE_1(0x16)
#define HID_USAGE_PS_OUTLET_SYSTEM      HID_USAGE_1(0x18)
#define HID_USAGE_PS_OUTLET_SYSTEM_ID   HID_USAGE_1(0x19)
#define HID_USAGE_PS_INPUT              HID_USAGE_1(0x1A)
#define HID_USAGE_PS_INPUT_ID           HID_USAGE_1(0x1B)
#define HID_USAGE_PS_OUTPUT             HID_USAGE_1(0x1C)
#define HID_USAGE_PS_OUTPUT_ID          HID_USAGE_1(0x1D)
#define HID_USAGE_PS_FLOW               HID_USAGE_1(0x1E)
#define HID_USAGE_PS_FLOW_ID            HID_USAGE_1(0x1F)
#define HID_USAGE_PS_OUTLET             HID_USAGE_1(0x20)
#define HID_USAGE_PS_OUTLET_ID          HID_USAGE_1(0x21)
#define HID_USAGE_PS_GANG               HID_USAGE_1(0x22)
#define HID_USAGE_PS_GANG_ID            HID_USAGE_1(0x23)
#define HID_USAGE_PS_POWER_SUMMARY      HID_USAGE_1(0x24)
#define HID_USAGE_PS_POWER_SUMMARY_ID   HID_USAGE_1(0x25)
#define HID_USAGE_PS_VOLTAGE            HID_USAGE_1(0x30)
#define HID_USAGE_PS_CURRENT            HID_USAGE_1(0x31)
#define HID_USAGE_PS_FREQUENCY          HID_USAGE_1(0x32)
#define HID_USAGE_PS_APPARENT_POWER     HID_USAGE_1(0x33)
#define HID_USAGE_PS_ACTIVE_POWER       HID_USAGE_1(0x34)
#define HID_USAGE_PS_TEMPERATURE        HID_USAGE_1(0x36)
#define HID_USAGE_PS_CONFIGVOLTAGE      HID_USAGE_1(0x40)
#define HID_USAGE_PS_CONFIGCURRENT      HID_USAGE_1(0x41)
#define HID_USAGE_PS_CONFIGFREQ         HID_USAGE_1(0x42)
#define HID_USAGE_PS_CONFIGAPP_POWER    HID_USAGE_1(0x43)
#define HID_USAGE_PS_CONFIGACT_POWER    HID_USAGE_1(0x44)
#define HID_USAGE_PS_CONFIGTEMPERATURE  HID_USAGE_1(0x46)
#define HID_USAGE_PS_SWITCHONCTRL       HID_USAGE_1(0x50)
#define HID_USAGE_PS_SWITCHOFFCTRL      HID_USAGE_1(0x51)
#define HID_USAGE_PS_TOGGLECTRL         HID_USAGE_1(0x52)
#define HID_USAGE_PS_PRESENT            HID_USAGE_1(0x60)
#define HID_USAGE_PS_GOOD               HID_USAGE_1(0x61)
#define HID_USAGE_PS_OVERLOAD           HID_USAGE_1(0x65)
#define HID_USAGE_PS_OVERCHARGED        HID_USAGE_1(0x66)
#define HID_USAGE_PS_OVERTEMP           HID_USAGE_1(0x67)
#define HID_USAGE_PS_RESERVED           HID_USAGE_1(0x6A)
#define HID_USAGE_PS_SWITCH_ON_OFF      HID_USAGE_1(0x6B)
#define HID_USAGE_PS_SWITCHABLE         HID_USAGE_1(0x6C)
#define HID_USAGE_PS_USED               HID_USAGE_1(0x6D)
#define HID_USAGE_PS_BOOST              HID_USAGE_1(0x6E)
#define HID_USAGE_PS_BUCK               HID_USAGE_1(0x6F)

#define HID_USAGE_PAGE_BATTERY_SYSTEM   HID_ITEM_1(0x0, GLOBAL, 0x85)

#define HID_USAGE_BS_OUTPUT_CONNECTION  HID_USAGE_1(0x16)
#define HID_USAGE_BS_CHARGER_CONNECTION HID_USAGE_1(0x17)
#define HID_USAGE_BS_BATTERY_INSERTION  HID_USAGE_1(0x18)
#define HID_USAGE_BS_CHARGING_INDICATOR HID_USAGE_1(0x1D)
#define HID_USAGE_BS_CAPACITY_MODE      HID_USAGE_1(0x2C)
#define HID_USAGE_BS_DESIGN_CAP         HID_USAGE_1(0x83)
#define HID_USAGE_BS_REMAINING_CAP      HID_USAGE_1(0x66)
#define HID_USAGE_BS_FULLCHARGE_CAP     HID_USAGE_1(0x67)
#define HID_USAGE_BS_BATTERY_PRESENT    HID_USAGE_1(0xD1)
#define HID_USAGE_BS_TERM_CHARGE        HID_USAGE_1(0x40)
#define HID_USAGE_BS_TERM_DISCHARGE     HID_USAGE_1(0x41)
#define HID_USAGE_BS_BELOW_REMCAPLIMIT  HID_USAGE_1(0x42)
#define HID_USAGE_BS_CHARGING           HID_USAGE_1(0x44)
#define HID_USAGE_BS_DISCHARGING        HID_USAGE_1(0x45)
#define HID_USAGE_BS_FULLY_CHARGED      HID_USAGE_1(0x46)
#define HID_USAGE_BS_FULLY_DISCHARGED   HID_USAGE_1(0x47)
#define HID_USAGE_BS_INHIBIT_CHARGE     HID_USAGE_1(0xC0)

#endif /* __HID_USAGE_POWER_H_ */
