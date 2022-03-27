/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 11:29:15
 * @Description: file content
 */
#ifndef _CUSTOM_CONTROL_H
#define _CUSTOM_CONTROL_H
#include "main.h"
#include "usb_device.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

extern uint8_t USBD_HID_SendReport(USBD_HandleTypeDef *pdev,
                                   uint8_t *report,
                                   uint16_t len);

enum custom_key
{
  VOL_UP,
  VOL_DOWN,
  MUTE,
  PAUSE_PLAY
};

typedef struct
{
  uint8_t report_id; //报告ID
  uint8_t special_key;
  /*报文只发送前2个字节*/
  uint8_t key_reserve;
  int8_t special_key_release_times[8];
} custom_buff_t;

extern custom_buff_t custom_buff;

void send_custom_control_data(void);
void custom_control_init(void);
/**
 * @brief : 添加按键, 见 enum custom_key
 * @param   {*}
 * @return  {*}
 * @param {enum custom_key} k
 * @param {int8_t} times
 */
void add_custom_control(enum custom_key k, int8_t times);

#endif
