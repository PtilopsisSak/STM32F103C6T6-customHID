/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-22 14:32:11
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
  uint8_t continue_function;
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
void touch_set_time(int16_t f);
/**
 * @brief : 设置触摸的坐标
 * @param   {*}
 * @return  {*}
 * @param {uint16_t} x
 * @param {uint16_t} y
 */
void touch_set_pos(uint16_t x, uint16_t y);
/**
 * @brief : 连续执行的函数开启标志
 * @param   {*}
 * @return  {*}
 * @param {uint8_t} s 0, 关闭, 1 开启
 */
void touch_set_continue_function(uint8_t s);
/**
 * @brief : 连续执行的函数体, 设置开启后每发送一遍执行一次
 * @param   {*}
 * @return  {*}
 */
__weak void touch_continue_function(void);

#if USING_SHELL
void touch_cmd(int argc, char **argv);
#endif

#endif
