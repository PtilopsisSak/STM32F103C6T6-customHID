/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2023-03-11 16:00:43
 * @Description: file content
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include "main.h"
#include "psk_hid.h"

#ifdef KEYBOARD_WITH_LWRB
#include "lwrb.h"
#define COMMAND_SIZE 99
#else
#warning "No using command buff, DELAY using HAL_Delay() instead"
#endif

#define USING_SHELL 0


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
  LEFT_CTRL = 0,
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
  uint8_t report_id; //����ID
  uint8_t special_key;
  uint8_t reserve;
  uint8_t keys[6];
  /*����ֻ����ǰ9���ֽ�*/
  uint8_t key_reserve;
  int8_t special_key_release_times[8];
  int8_t keys_release_times[7];
} keyboard_buff;

extern keyboard_buff tkeyboard_buff;

typedef struct
{
  uint8_t send_ok;
} keyboard_state_t;

struct keyboard_led_state_t
{
  uint8_t NUM_LOCK : 1;
  uint8_t CAPS_LOCK : 1;
  uint8_t SCROLL_LOCK : 1;
  uint8_t reserve : 5;
};

extern struct keyboard_led_state_t keyboard_led_state;

extern keyboard_state_t keyboard_state;

void send_keyboard_data(void);

void keyboard_init(void);
/**
 * @brief : �ڲ�����, ��Ȼ�ⲿҲ���þ�����
 */
void add_special_code(enum keyboard_sp_key k, int8_t reprot_times);
void add_key_code(uint8_t k, int8_t reprot_times);
void kbd_write_command(int8_t a, int8_t b, int8_t c);


/**
 * @brief : ����ģʽ
 */

/**
 * @brief : ��ʱ, �� SEND_DELAY �й�, ��С��ʱΪ SEND_DELAY
 * @note  : keyboard_delay(300); ���̰�������������ʱ300ms����������İ�������
 * @param {int16_t} time_ms
 */
void keyboard_delay(int16_t time_ms);
/**
 * @brief : ���¼����ϵ��ַ�, ����ASCIIȫ֧��, ��֧�� �Ʊ�� ���з�, ���Զ���SHIFT
 * @note  : keyboard_press_char('a', 3); keyboard_press_char('\t', -1);
 * @param {char} a
 * @param {int8_t} reprot_times *SEND_DELAY ms���ɿ�(�첽), -1 һֱ����
 */
void keyboard_press_char(char a, int8_t reprot_times);
/**
 * @brief : ���¿��Ƽ�, ctrl, shift, alt gui, �� enum keyboard_sp_key
 * @note  : keyboard_press_sp_key(LEFT_GUI, 3);
 * @param {enum keyboard_sp_key} k
 * @param {int8_t} reprot_times *SEND_DELAY ms���ɿ�(�첽), -1 һֱ����
 */
void keyboard_press_sp_key(enum keyboard_sp_key k, int8_t reprot_times);
/**
 * @brief : ����ָ����ֵ, ���ּ�enum keyboard_key
 * @note  : keyboard_press_key_code(Keyboard_Return_ENTER, 6);
 * @param {uint8_t} k
 * @param {int8_t} reprot_times *SEND_DELAY ms���ɿ�(�첽), -1 һֱ����
 */
void keyboard_press_key_code(uint8_t k, int8_t reprot_times);
/**
 * @brief : ����С�����ϵ��ַ�, ע��NUM_lock, ֧�� ���з�
 * @note  : keyboard_press_keypad_char('8', 6);
 * @param {char} a
 * @param {int8_t} reprot_times *SEND_DELAY ms���ɿ�(�첽), -1 һֱ����
 */
void keyboard_press_keypad_char(char a, int8_t reprot_times);
/**
 * @brief : ���ַ���, ����ASCIIȫ֧��, ��֧�� �Ʊ�� tab ���з� enter
 * @note  : keyboard_press_str("aB 1~`\n\t+8$", 3);
 * @param {char} *s
 * @param {int16_t} time_ms 0:��췢��(�����ͬʱ��), >0:����һ������time_ms
 */
void keyboard_press_str(char *s, int16_t time_ms);

#if USING_SHELL
void keyboard_cmd(int argc, char **argv);
void pstr(int argc, char **argv);
void press(int argc, char **argv);
#endif

#endif
