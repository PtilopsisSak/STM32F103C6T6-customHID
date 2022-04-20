/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-04-19 16:39:38
 * @Description: file content
 */
#ifndef _MOUSE_H
#define _MOUSE_H
#include "main.h"
#include "usbd_custom_hid_if.h"

#define USING_PID

typedef struct
{
  uint8_t report_id;
  uint8_t key;
  int8_t mouse_rel_x;
  int8_t mouse_rel_y;
  int8_t mouse_rel_wheel;
} Mouse_buff;

enum mouse_key
{
  KEY_LEFT,
  KEY_RIGHT,
  KEY_WHELL
};

extern Mouse_buff tMouse_buff;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t cur_x;
  int16_t cur_y;
  int8_t key[3];
  uint8_t continue_key[3];
  uint8_t continue_function;
} mouse_state_t;

extern mouse_state_t mouse_state;

/**
 * @brief : 发送鼠标事件
 */
void send_mouse_data(void);

/**
 * @brief : 鼠标初始化
 */
void mouse_init(void);
/**
 * @brief : 连续执行的函数体, 设置开启后每发送一遍执行一次
 */
__weak void mouse_continue_function(void);
/**
 * @brief : 连击
 * @param {enum mouse_key} key 按键
 * @param {int8_t} time 连点间隔(为几次报告的间隔), 0 关闭
 */
void mouse_set_continue_click(enum mouse_key key, int8_t time);
/**
 * @brief : 点击
 * @param {enum mouse_key} key
 * @param {int8_t} time *SEND_DELAY ms后松开(异步), -1 一直按下
 */
void mouse_set_click(enum mouse_key key, int8_t time);
/**
 * @brief : 连续执行的函数开启标志
 * @param {uint8_t} s 0, 关闭, other 开启
 */
void mouse_set_continue_function(int8_t s);
/**
 * @brief : 相对移动
 * @note  :
 * @param {int16_t} x
 * @param {int16_t} y
 */
void mouse_move(int16_t x, int16_t y);

void rand_reset(void);
#if USING_SHELL
void mouse_cmd(int argc, char **argv);
#endif

#endif
