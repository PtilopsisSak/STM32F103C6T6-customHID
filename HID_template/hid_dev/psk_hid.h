/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2023-03-11 19:43:22
 * @Description: file content
 */
#ifndef _PSK_HID
#define _PSK_HID

#define SEND_DELAY 5

#define KEYBOARD_WITH_LWRB
#define MOUSE_USING_PID

#include "main.h"

void MY_USB_HID_SEND_REPORT(uint8_t *report, uint16_t len);

#include "usbd_custom_hid_if.h"

#include "mouse.h"
#include "keyboard.h"
#include "touch_screen.h"
#include "custom_control.h"
#endif
