/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-23 17:50:30
 * @Description: file content
 */
#include "psk_ps.h"

#include "usbd_custom_hid_if.h"

// uint8_t usart_recv_it_buff;

// lwrb_t usart_lwrb;

// uint8_t USART_RINGBUFF[USART_RINGBUFF_SIZE];
uint8_t USART_TX_BUF_PS[200] = {0x07, 0};

void ps_putc(char *ch, unsigned short len)
{
	if (len >= 63)
	{
		len = 63;
	}
	USBD_CUSTOM_HID_SendReport_FS(ch, len + 1);
}

// uint8_t ps_getc(char *ch, unsigned short len)
// {
// 	return lwrb_read(&usart_lwrb, ch, len);
// }

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	if (huart->Instance == USART1)
// 	{
// 		lwrb_write(&usart_lwrb, &usart_recv_it_buff, 1);
// 		HAL_UART_Receive_IT(huart, (uint8_t *)&usart_recv_it_buff, 1);
// 	}
// }

// void ps_init(void)
// {
// 	lwrb_init(&usart_lwrb, (uint8_t *)USART_RINGBUFF, USART_RINGBUFF_SIZE);
// }
