/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 16:22:02
 * @Description: file content
 */
#ifndef _MOUSE_H
#define _MOUSE_H
#include "main.h"
#include "usbd_custom_hid_if.h"
// #include "usb_device.h"

// extern USBD_HandleTypeDef hUsbDeviceFS;

// extern uint8_t USBD_HID_SendReport(USBD_HandleTypeDef *pdev,
//                                    uint8_t *report,
//                                    uint16_t len);
extern int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);
extern int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len);

#define USING_PID

typedef struct
{
  uint8_t report_id; //报告ID
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
  char is_ok;
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
 * @param   {*}
 * @return  {*}
 */
void send_mouse_data(void);

void mouse_init(void);

/**
 * @brief : 连续执行的函数体, 设置开启后每发送一遍执行一次
 * @param   {*}
 * @return  {*}
 */
void continue_function(void);
/**
 * @brief : 连击
 * @param   {*}
 * @return  {*}
 * @param {enum mouse_key} key 按键
 * @param {int8_t} time 连点间隔(为几次报告的间隔)
 */
void set_continue_click(enum mouse_key key, int8_t time);
/**
 * @brief : 点击
 * @param   {*}
 * @return  {*}
 * @param {enum mouse_key} key
 * @param {int8_t} time 发几次报告后松开, 0 立刻松开, -1, 一直按住
 */
void set_click(enum mouse_key key, int8_t time);
/**
 * @brief : 连续执行的函数开启标志
 * @param   {*}
 * @return  {*}
 * @param {uint8_t} s 0, 关闭, 1 开启
 */
void set_continue_function(uint8_t s);
void mouse_cmd(int argc, char **argv);
void rand_reset(void);

#endif
