#include "multi_button.h"
#include "main.h"
#include "psk_led.h"

#include "mouse.h"
#include "math.h"
#include "keyboard.h"
#include "touch_screen.h"
#include "custom_control.h"
#include "psk_switch.h"

#ifndef _MYKEY_H
#define _MYKEY_H

Button keys[4];
uint8_t key_scan_code = 0xff;

void key_scan(void)
{
	static uint16_t j;
	static uint16_t pin[] = {KEY3_Pin, KEY2_Pin, KEY1_Pin, KEY0_Pin};
	static GPIO_TypeDef *port[] = {KEY3_GPIO_Port, KEY2_GPIO_Port, KEY1_GPIO_Port, KEY0_GPIO_Port};
	key_scan_code = 0;
	for (j = 0; j < 4; j++)
	{
		key_scan_code <<= 1;
		key_scan_code += HAL_GPIO_ReadPin(port[j], pin[j]);
	}
}
uint8_t key_read(para i)
{
	return (key_scan_code >> i) & 0x0001;
}
void key44callback(void *button)
{
	uint32_t btn_event_val, index;

	btn_event_val = get_button_event((struct Button *)button);
	index = ((struct Button *)button)->func_para;
	led_set_light(index, 100);
	if (switch_data == 0)
	{
		switch (btn_event_val)
		{
		case PRESS_DOWN:
			switch (index)
			{
			case 0:
				rand_reset();
				mouse_set_continue_function(1);
				keyboard_press_char('z', -1);
				break;
			case 1:
				keyboard_press_char('z', -1);
				break;
			case 2:
				keyboard_press_char('x', -1);
				break;
			case 3:
				custom_press_key(MUTE, -1);
				break;
			}
			break;
		case PRESS_UP:
			switch (index)
			{
			case 0:
				mouse_set_continue_function(0);
				keyboard_press_char('z', 0);
				break;
			case 1:
				keyboard_press_char('z', 0);
				break;
			case 2:
				keyboard_press_char('x', 0);
				break;
			case 3:
				custom_press_key(MUTE, 0);
				break;
			}
			break;
		}
	}
	else if (switch_data == 1)
	{
		switch (btn_event_val)
		{
		case PRESS_DOWN:
			switch (index)
			{
			case 0:
				mouse_set_continue_click(KEY_LEFT, 1);
				break;
			case 1:
				// touch_set_time(-1);
				touch_set_continue_function(1);
				break;
			case 2:
				keyboard_press_key_code(Keyboard_ESCAPE, -1);
				break;
			case 3:
				custom_press_key(MUTE, -1);
				break;
			}
			break;
		case PRESS_UP:
			switch (index)
			{
			case 0:
				mouse_set_continue_click(KEY_LEFT, 0);
				break;
			case 1:
				touch_set_time(0);
				touch_set_continue_function(0);
				break;
			case 2:
				keyboard_press_key_code(Keyboard_ESCAPE, 0);
				break;
			case 3:
				custom_press_key(MUTE, 0);
				break;
			}
			break;
		}
	}
	else if (switch_data == 2)
	{
		switch (btn_event_val)
		{
		case PRESS_DOWN:
			keyboard_press_char('b', -1);
			keyboard_press_sp_key(LEFT_CTRL, -1);
			keyboard_press_sp_key(LEFT_SHIFT, -1);
			break;
		case PRESS_UP:
			keyboard_press_char('b', 0);
			keyboard_press_sp_key(LEFT_CTRL, 0);
			keyboard_press_sp_key(LEFT_SHIFT, 0);

			break;
		case DOUBLE_CLICK:
			switch (index)
			{
			case 0:
				add_special_code(LEFT_CTRL, 3);
				keyboard_press_char('c', 3);
				break;
			case 1:
				add_special_code(LEFT_GUI, 3);
				keyboard_press_char('v', 3);
				break;
			case 2:
				add_special_code(LEFT_CTRL, 3);
				add_key_code(0x38, 3);
				break;
			case 3:
				add_special_code(LEFT_CTRL, 3);
				keyboard_press_char('x', 3);
				break;
			}

			break;
			// case DOUBLE_CLICK:
			// 	switch (index)
			// 	{
			// 	case 0:
			// 		add_special_code(LEFT_CTRL, 3);
			// 		keyboard_press_char('s', 3);
			// 		break;
			// 	case 1:
			// 		// add_special_code(LEFT_CTRL, 3);
			// 		// keyboard_press_char('v', 3);
			// 		break;
			// 	case 2:
			// 		// add_special_code(LEFT_CTRL, 3);
			// 		add_key_code(Keyboard_F7_118____4_101_104, 3);
			// 		break;
			// 	case 3:
			// 		add_special_code(LEFT_CTRL, 3);
			// 		keyboard_press_char('x', 3);
			// 		break;
			// 	}

			// 	break;
		}
	}
	else
	{
		switch (btn_event_val)
		{
		case PRESS_DOWN:
			switch (index)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
			break;
		case PRESS_UP:
			switch (index)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
			break;
		case DOUBLE_CLICK:
			switch (index)
			{
			case 0:
				add_special_code(LEFT_CTRL, 3);
				keyboard_press_char('s', 3);
				HAL_Delay(100);
				add_special_code(LEFT_ALT, 3);
				add_key_code(Keyboard_Tab, 3);
				HAL_Delay(100);
				add_key_code(Keyboard_F7_118____4_101_104, 3);
				HAL_Delay(5000);
				add_key_code(Keyboard_F8_119____4_101_104, 3);
				HAL_Delay(8000);
				add_special_code(LEFT_ALT, 3);
				add_key_code(Keyboard_Tab, 3);
				break;
			case 1:
				break;
			case 2:
				// keyboard_press_str("ptisak");
				keyboard_press_str("`1234567890-=[]\\;',./", 0);
				keyboard_press_str("~!@#$%%^&*()_ +{}|:\"<>?\n", 0);

				break;
			case 3:
				break;
			}
			break;
		}
	}
	if (index == 15)
	{
		__disable_irq();
		__NVIC_SystemReset();
	}
}
void my_button_init(void)
{
	int8_t i;
	for (i = 0; i < 4; i++)
	{
		button_init(keys + i, key_read, i);
		button_attach(keys + i, PRESS_DOWN, key44callback);
		button_attach(keys + i, PRESS_UP, key44callback);
		// button_attach(keys+i, PRESS_REPEAT, key44callback);
		button_attach(keys + i, SINGLE_CLICK, key44callback);
		button_attach(keys + i, DOUBLE_CLICK, key44callback);
		// button_attach(keys+i, LONG_PRESS_START, key44callback);
		// button_attach(keys+i, LONG_PRESS_HOLD, key44callback);
		button_start(keys + i);
	}
}

#endif
