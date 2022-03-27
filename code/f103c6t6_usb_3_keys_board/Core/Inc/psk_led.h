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
	STEEP,		  // 突变
	SMOOTH_ALL,	  // 逐渐降低/升高亮度
	SMOOTH_DIM,	  // 逐渐降低亮度(升高会突变)
	SMOOTH_LIGHT, // 逐渐升高亮度(降低会突变)
};
#define LED_TOTAL 8

static GPIO_TypeDef *LED_IO[LED_TOTAL] = {LED0_GPIO_Port, LED1_GPIO_Port, LED2_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED_B_GPIO_Port, LED_R_GPIO_Port, LED_G_GPIO_Port};
static uint16_t LED_PIN[LED_TOTAL] = {LED0_Pin, LED1_Pin, LED2_Pin, LED6_Pin, LED7_Pin, LED_B_Pin, LED_R_Pin, LED_G_Pin};

void led_set_rgb(uint8_t r, uint8_t g, uint8_t b);
void led_set_mode(uint8_t led_n, enum led_smooth mode);
void led_set_light(uint8_t led_n, uint8_t light);

/**
 * @brief : 每隔一段时间执行一次, 根据模式实现led亮度渐变
 * @param   {*}
 * @return  {*}
 */
void led_smooth_change_handle(void);
/**
 * @brief : 放在一个定时器里, 调用100次完成一个pwm周期
 * @param   {*}
 * @return  {*}
 */
void led_soft_pwm_handle(void);

#endif
