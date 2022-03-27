/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-22 14:17:21
 * @Description: file content
 */
#ifndef _PSK_LED
#define _PSK_LED
#include "main.h"

enum led_smooth
{
	STEEP,		  // ͻ��
	SMOOTH_ALL,	  // �𽥽���/��������
	SMOOTH_DIM,	  // �𽥽�������(���߻�ͻ��)
	SMOOTH_LIGHT, // ����������(���ͻ�ͻ��)
};
#define LED_TOTAL 8

static GPIO_TypeDef *LED_IO[LED_TOTAL] = {LED0_GPIO_Port, LED1_GPIO_Port, LED2_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED_B_GPIO_Port, LED_R_GPIO_Port, LED_G_GPIO_Port};
static uint16_t LED_PIN[LED_TOTAL] = {LED0_Pin, LED1_Pin, LED2_Pin, LED6_Pin, LED7_Pin, LED_B_Pin, LED_R_Pin, LED_G_Pin};

void led_set_rgb(uint8_t r, uint8_t g, uint8_t b);
void led_set_mode(uint8_t led_n, enum led_smooth mode);
void led_set_light(uint8_t led_n, uint8_t light);

/**
 * @brief : ÿ��һ��ʱ��ִ��һ��, ����ģʽʵ��led���Ƚ���
 * @param   {*}
 * @return  {*}
 */
void led_smooth_change_handle(void);
/**
 * @brief : ����һ����ʱ����, ����100�����һ��pwm����
 * @param   {*}
 * @return  {*}
 */
void led_soft_pwm_handle(void);

#endif
