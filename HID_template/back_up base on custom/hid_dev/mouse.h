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
 * @brief : ��������¼�
 */
void send_mouse_data(void);

/**
 * @brief : ����ʼ��
 */
void mouse_init(void);
/**
 * @brief : ����ִ�еĺ�����, ���ÿ�����ÿ����һ��ִ��һ��
 */
__weak void mouse_continue_function(void);
/**
 * @brief : ����
 * @param {enum mouse_key} key ����
 * @param {int8_t} time ������(Ϊ���α���ļ��), 0 �ر�
 */
void mouse_set_continue_click(enum mouse_key key, int8_t time);
/**
 * @brief : ���
 * @param {enum mouse_key} key
 * @param {int8_t} time *SEND_DELAY ms���ɿ�(�첽), -1 һֱ����
 */
void mouse_set_click(enum mouse_key key, int8_t time);
/**
 * @brief : ����ִ�еĺ���������־
 * @param {uint8_t} s 0, �ر�, other ����
 */
void mouse_set_continue_function(int8_t s);
/**
 * @brief : ����ƶ�
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
