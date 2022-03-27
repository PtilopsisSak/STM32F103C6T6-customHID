/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 16:26:08
 * @Description: file content
 */
#ifndef _touch_screen_H
#define _touch_screen_H
#include "main.h"
#include "usbd_custom_hid_if.h"

typedef struct
{
  uint8_t report_id; //报告ID
  uint8_t touch_flag;
  uint16_t x; // x 大端存储
  uint16_t y; // y
} touch_buff;

typedef struct
{
  float x_scale;
  float y_scale;
  uint16_t x_max;
  uint16_t y_max;
  int16_t release;
} touch_inf;
extern touch_inf ttouch_inf;
extern touch_buff ttouch_buff;

float get_rand(void);
void send_touch_data(void);
void touch_init(void);
/**
 * @brief : 设置触摸的实际最大值
 * @param   {*}
 * @return  {*}
 * @param {uint16_t} x
 * @param {uint16_t} y
 */
void touch_set_size(uint16_t x, uint16_t y);
/**
 * @brief : 设置触摸时间
 * @param   {*}
 * @return  {*}
 * @param {int16_t} f 0 松开,  >0 按下时间, -1 一直按住
 */
void set_touch_flag(int16_t f);
/**
 * @brief : 设置触摸的坐标
 * @param   {*}
 * @return  {*}
 * @param {uint16_t} x
 * @param {uint16_t} y
 */
void set_touch_pos(uint16_t x, uint16_t y);
void touch_cmd(int argc, char **argv);

#endif
