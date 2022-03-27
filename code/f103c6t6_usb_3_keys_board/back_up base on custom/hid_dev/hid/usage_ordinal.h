/**
  ******************************************************************************
  * @file    usage_ordinal.h
  * @author  Benedek Kupper
  * @version 0.1
  * @date    2020-04-02
  * @brief   USB Human Interface Device Class
  *          Ordinal Usage Page definitions
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
#ifndef __HID_USAGE_ORDINAL_H_
#define __HID_USAGE_ORDINAL_H_
#include <hid/report.h>

#define HID_USAGE_PAGE_ORDINAL          HID_ITEM_1(0x0, GLOBAL, 0x0A)

#define HID_USAGE_ORD_INST(VAL)         HID_USAGE_1(VAL)

#endif /* __HID_USAGE_ORDINAL_H_ */
