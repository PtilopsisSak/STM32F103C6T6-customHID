/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-22 14:17:05
 * @Description: file content
 */
#ifndef _PSK_PS
#define _PSK_PS

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "lwrb.h"
#define USART_RINGBUFF_SIZE 200

extern uint8_t USART_RINGBUFF[USART_RINGBUFF_SIZE];
extern uint8_t USART_TX_BUF_PS[200];
extern lwrb_t usart_lwrb;
extern uint8_t usart_recv_it_buff;
extern uint8_t ps_getc(char *ch, unsigned short len);
extern void ps_putc(char *ch, unsigned short len);
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

extern void ps_init(void);

#define _DEBUG_
/*------------------DEBUG DEFINE BEGIN------------------------*/
#ifdef _DEBUG_
#define ps(...) ps_putc((char *)USART_TX_BUF_PS, (unsigned short)sprintf((char *)USART_TX_BUF_PS+1, __VA_ARGS__));
#else
#define ps(...)
#endif

#endif
