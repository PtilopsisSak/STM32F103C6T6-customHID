/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-04-20 14:23:45
 * @Description: file content
 */
#ifndef _touch_screen_H
#define _touch_screen_H
#include "main.h"
#include "usbd_custom_hid_if.h"
#include "psk_hid.h"
#define USING_SHELL 0
typedef struct
{
  uint8_t report_id; //����ID
  uint8_t touch_flag;
  uint16_t x; // x ��˴洢
  uint16_t y; // y
} touch_buff;

typedef struct
{
  float x_scale;
  float y_scale;
  uint16_t x_max;
  uint16_t y_max;
  int16_t release;
  uint8_t continue_function;
} touch_inf;
extern touch_inf ttouch_inf;
extern touch_buff ttouch_buff;

float get_rand(void);
void send_touch_data(void);
void touch_init(void);
/**
 * @brief : ���ô�����ʵ�����ֵ
 * @param {uint16_t} x
 * @param {uint16_t} y
 */
void touch_set_size(uint16_t x, uint16_t y);
/**
 * @brief : ���ô���ʱ��
 * @param {int16_t} times_ms 0 �ɿ�,  >5 ����ʱ��(ms���ɿ�), -1 һֱ��ס
 */
void touch_set_time(int16_t times_ms);
/**
 * @brief : ���ô���������
 * @param {uint16_t} x
 * @param {uint16_t} y
 */
void touch_set_pos(uint16_t x, uint16_t y);
/**
 * @brief : ����ִ�еĺ���������־
 * @param {uint8_t} s 0, �ر�, other ����
 */
void touch_set_continue_function(int8_t s);
/**
 * @brief : ����ִ�еĺ�����, ���ÿ�����ÿ����һ��ִ��һ��
 */
__weak void touch_continue_function(void);

#if USING_SHELL
void touch_cmd(int argc, char **argv);
#endif

#endif
