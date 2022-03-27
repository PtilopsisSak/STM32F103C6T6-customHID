/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 11:26:51
 * @Description: file content
 */
#ifndef _PSK_SWITCH_H
#define _PSK_SWITCH_H
#include "main.h"
#define SWITCH_TOTAL 2
static GPIO_TypeDef *SWITCH_IO[SWITCH_TOTAL] = {S0_GPIO_Port, S1_GPIO_Port};
static uint16_t SWITCH_PIN[SWITCH_TOTAL] = {S0_Pin, S1_Pin};

extern uint8_t switch_data;
void scan_switch(void);

#endif
