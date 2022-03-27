/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-22 13:48:46
 * @Description: file content
 */
#ifndef _CUSTOM_CONTROL_H
#define _CUSTOM_CONTROL_H
#include "main.h"
#include "usbd_custom_hid_if.h"

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

/**
 * @brief : 用户控制设备初始化
 * @param   {*}
 * @return  {*}
 */
void custom_init(void);
/**
 * @brief : 添加按键, 见 enum custom_key
 * @param   {*}
 * @return  {*}
 * @param {enum custom_key} k
 * @param {int8_t} times
 */
void custom_press_key(enum custom_key k, int8_t times);

#endif
