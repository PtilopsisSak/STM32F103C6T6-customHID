/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-04-19 16:29:35
 * @Description: file content
 */
#include "psk_hid.h"

#include "usb_device.h"

static uint8_t data[64];

/**
 * @brief :�� usbd_customhid.c USBD_CUSTOM_HID_DataOut(...)
 * @param {uint8_t} rx_data
 */
void hid_rx_iqr(uint8_t rx_data[64])
{
	memcpy(data, rx_data, 64);
	if (data[0] == 0x01) // ���̵�״̬
	{
		memcpy((uint8_t *)&keyboard_led_state, data + 1, 1);
	}
}
