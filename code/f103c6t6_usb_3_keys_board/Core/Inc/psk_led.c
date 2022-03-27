/*
 * @Author: Ptisak
 * @Date: 2022-03-19 09:59:20
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-20 13:53:01
 * @Description: file content
 */
#include "psk_led.h"
uint8_t led_array[LED_TOTAL];
uint8_t led_set[LED_TOTAL];
uint8_t led_flag[LED_TOTAL];

void led_soft_pwm_handle(void)
{
	static uint8_t i;
	static uint8_t times = 1;
	static uint8_t LED_stat[LED_TOTAL] = {0};
	times++;
	if (times > 100)
	{
		times = 1;
		for (i = 0; i < LED_TOTAL; i++)
		{
			if (led_array[i] > 1)
			{
				HAL_GPIO_WritePin(LED_IO[i], LED_PIN[i], RESET);
				LED_stat[i] = 1;
			}
			else
			{
				HAL_GPIO_WritePin(LED_IO[i], LED_PIN[i], SET);
				LED_stat[i] = 0;
			}
		}
	}
	else
	{
		for (i = 0; i < LED_TOTAL; i++)
		{
			if (LED_stat[i] && led_array[i] <= times)
			{
				HAL_GPIO_WritePin(LED_IO[i], LED_PIN[i], SET);
				LED_stat[i] = 0;
			}
		}
	}
}

void led_smooth_change_handle(void)
{
	static uint8_t i;
	for (i = 0; i < LED_TOTAL; i++)
	{
		// led_array[i] -= 1;
		switch (led_flag[i])
		{
		case SMOOTH_ALL: // 逐渐降低/升高亮度
			if (led_set[i] == led_array[i])
			{
				// led_array[i] = 0;
			}
			else if (led_set[i] > led_array[i])
			{
				led_array[i]++;
			}
			else
			{
				led_array[i]--;
			}

			break;
		case SMOOTH_LIGHT: // 逐渐升高亮度(降低会突变)
			if (led_array[i] < 100)
			{
				led_array[i]++;
			}
			if (led_set[i] < led_array[i])
			{
				led_array[i] = led_set[i];
				led_set[i] = 100;
			}
			break;
		case SMOOTH_DIM: // 逐渐降低亮度(升高会突变)
			if (led_array[i] > 0)
			{
				led_array[i]--;
			}
			if (led_set[i] > led_array[i])
			{
				led_array[i] = led_set[i];
				led_set[i] = 0;
			}
			break;
		case STEEP:
			led_array[i] = led_set[i];
			break;
		}
	}
}

void led_set_light(uint8_t led_n, uint8_t light)
{
	if (light>100){
		light = 200 - light;
	}
	led_set[led_n] = light;
}
void led_set_mode(uint8_t led_n, enum led_smooth mode)
{
	led_flag[led_n] = mode;
}
void led_set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	led_set_light(6, r);
	led_set_light(7, g);
	led_set_light(5, b);
	// led_set[6] = r;
	// led_set[7] = g;
	// led_set[5] = b;
}