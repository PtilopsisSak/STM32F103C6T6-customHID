/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-20 13:47:57
 * @Description: file content
 */
#include "psk_switch.h"
uint8_t switch_data;
void scan_switch(void)
{
	static uint16_t i;
	switch_data = 0;
	for (i = 0; i < SWITCH_TOTAL; i++)
	{
		switch_data <<= 1;
		switch_data += HAL_GPIO_ReadPin(SWITCH_IO[i], SWITCH_PIN[i]);
	}
}
