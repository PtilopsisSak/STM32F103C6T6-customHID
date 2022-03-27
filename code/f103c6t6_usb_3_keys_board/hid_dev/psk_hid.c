/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-23 17:49:24
 * @Description: file content
 */
#include "psk_hid.h"

#include "usb_device.h"
#include "keyboard.h"

static uint8_t data[64];

void hid_rx_iqr(uint8_t rx_data[64])
{
	memcpy(data, rx_data, 64);
	if (data[0] == 0x01)
	{ // keyboard input
		memcpy((uint8_t *)&keyboard_led_state, data + 1, 1);
	}
}
