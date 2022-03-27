/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 16:25:58
 * @Description: file content
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "main.h"
#include "usbd_custom_hid_if.h"
#include "string.h"

enum keyboard_key
{
  Keyboard_Return_ENTER = 0x28,
  Keyboard_ESCAPE = 0x29,
  Keyboard_Backspace = 0x2A,
  Keyboard_Tab = 0x2B,
  Keyboard_Spacebar = 0x2C,

  Keyboard_F1_112____4_101_104 = 0x3A,
  Keyboard_F2_113____4_101_104 = 0x3B,
  Keyboard_F3_114____4_101_104 = 0x3C,
  Keyboard_F4_115____4_101_104 = 0x3D,
  Keyboard_F5_116____4_101_104 = 0x3E,
  Keyboard_F6_117____4_101_104 = 0x3F,
  Keyboard_F7_118____4_101_104 = 0x40,
  Keyboard_F8_119____4_101_104 = 0x41,
  Keyboard_F9_120____4_101_104 = 0x42,
  Keyboard_F10_121____4_101_104 = 0x43,
  Keyboard_F11_122____101_104 = 0x44,
  Keyboard_F12_123____101_104 = 0x45,
  Keyboard_PrintScreen1_124____101_104 = 0x46,
  Keyboard_Scroll_Lock11_125____4_101_104 = 0x47,
  Keyboard_Pause1_126____101_104 = 0x48,
  Keyboard_Insert1_75____101_104 = 0x49,
  Keyboard_Home1_80____101_104 = 0x4A,
  Keyboard_PageUp1_85____101_104 = 0x4B,
  Keyboard_Delete_Forward1_14_76____101_104 = 0x4C,
  Keyboard_End1_81____101_104 = 0x4D,
  Keyboard_PageDown1_86____101_104 = 0x4E,
  Keyboard_RightArrow1_89____101_104 = 0x4F,
  Keyboard_LeftArrow1_79____101_104 = 0x50,
  Keyboard_DownArrow1_84____101_104 = 0x51,
  Keyboard_UpArrow1_83____101_104 = 0x52,
  Keypad_Num_Lock_and_Clear11_90____101_104 = 0x53,
};
enum keyboard_sp_key
{
  LEFT_CTRL=0,
  LEFT_SHIFT,
  LEFT_ALT,
  LEFT_GUI,
  RIGHT_CTRL,
  RIGHT_SHIFT,
  RIGHT_ALT,
  RIGHT_GUI
};
typedef struct
{
  uint8_t report_id; //报告ID
  uint8_t special_key;
  uint8_t reserve;
  uint8_t keys[6];
  /*报文只发送前9个字节*/
  uint8_t key_reserve;
  int8_t special_key_release_times[8];
  int8_t keys_release_times[7];
} keyboard_buff;

extern keyboard_buff tkeyboard_buff;

typedef struct
{
  /* data */
  char is_ok;
  uint8_t send_ok;
} keyboard_state_t;

#define USING_PID

extern keyboard_state_t keyboard_state;

void send_keyboard_data(void);

void keyboard_init(void);

/**
 * @brief : 添加键值, 按下指定按键
 * @param   {*}
 * @return  {*}
 * @param {uint8_t} k, 部分按键见 enum keyboard_key
 * @param {int8_t} times
 */
void add_key_code(uint8_t k, int8_t times);
/**
 * @brief : 添加字符按键, 按下指定按键
 * @param   {*}
 * @return  {*}
 * @param {char} a
 * @param {int8_t} time
 */
void add_char_code(char a, int8_t time);
void press_str(char *s);
/**
 * @brief : 添加特殊按键, 见enum keyboard_sp_key
 * @param   {*}
 * @return  {*}
 * @param {uint8_t} k
 * @param {int8_t} times
 */
void add_special_code(enum keyboard_sp_key k, int8_t times);
void keyboard_cmd(int argc, char **argv);
void pstr(int argc, char **argv);
void press(int argc, char **argv);

#endif
