/*
 * @Author: Ptisak
 * @Date: 2022-04-19 08:40:35
 * @LastEditors: Ptisak
 * @LastEditTime: 2023-03-11 18:21:33
 * @Version: 1.0
 */
#include "touch_screen.h"
#include "stdlib.h"

touch_inf ttouch_inf;
touch_buff ttouch_buff;
// touch_buff ttouch_buff_last;
static int con_index;

void touch_init(void)
{
    memset(&ttouch_buff, 0X00, sizeof(ttouch_buff));
    ttouch_buff.report_id = 0x04;
    // memset(&ttouch_buff_last, 0X00, sizeof(ttouch_buff));
    touch_set_size(1920, 1080);
}

void send_touch_data(void)
{
    static uint8_t k;
    k = 0;
    if (ttouch_inf.continue_function)
    {
        touch_continue_function();
    }
    if (ttouch_inf.release < 0)
    {
        ttouch_buff.touch_flag = 1;
    }
    else if (ttouch_inf.release > 0)
    {
        ttouch_buff.touch_flag = 1;
        ttouch_inf.release--;
    }
    else if (ttouch_buff.touch_flag == 1)
    {
        k = 1;
        ttouch_buff.touch_flag = 0;
    }
    if (ttouch_buff.touch_flag || k != 0)
    {
        MY_USB_HID_SEND_REPORT((uint8_t *)&ttouch_buff, sizeof(ttouch_buff));
    }
}

void touch_set_size(uint16_t x, uint16_t y)
{
    ttouch_inf.x_max = x;
    ttouch_inf.y_max = y;
    ttouch_inf.x_scale = 4095.f / x;
    ttouch_inf.y_scale = 4095.f / y;
}
void touch_set_time(int16_t times_ms)
{
    if (times_ms > 0)
    {
        times_ms /= SEND_DELAY;
    }
    ttouch_inf.release = times_ms;
}
void touch_set_pos(uint16_t x, uint16_t y)
{
    // srand(HAL_GetTick());
    ttouch_buff.x = (uint16_t)((x)*ttouch_inf.x_scale);
    ttouch_buff.y = (uint16_t)((y)*ttouch_inf.y_scale);
}
void touch_set_continue_function(int8_t s)
{
    con_index = 0;
    ttouch_inf.continue_function = !!s;
}

__weak void touch_continue_function(void)
{
    if (con_index == 0)
    {
        touch_set_time(-1);
        touch_set_pos(1009, 802);
    }
    else if (con_index == 2)
    {
        touch_set_time(-1);
        touch_set_pos(801, 781);
    }
    else
    {
        touch_set_time(0);
    }
    con_index = (con_index + 1) % 4;
}

// float get_rand(void)
// {
//     return (rand() % 100) / 100.f;
// }
#if USING_SHELL
void touch_cmd(int argc, char **argv)
{
    static int32_t a, b, c;
    if (argc < 2)
    {
        rt_kprintf("Error\n");
        return;
    }
    if (!strcmp(argv[1], "down"))
    {
        touch_set_time(-1);
        return;
    }
    else if (!strcmp(argv[1], "up"))
    {
        touch_set_time(0);
        return;
    }
    else if (!strcmp(argv[1], "pos"))
    {
        if (argc < 4)
        {
            rt_kprintf("Error\n");
            return;
        }
        sscanf(argv[2], "%d", &a);
        sscanf(argv[3], "%d", &b);
        ;
        //_sscanf(argv[4], "%d", &c);

        touch_set_pos((uint16_t)(a), (uint16_t)(b));
        return;
    }
    else if (!strcmp(argv[1], "tap"))
    {
        c = 13;
        if (argc == 4)
        {
            sscanf(argv[2], "%d", &a);
            sscanf(argv[3], "%d", &b);
        }
        else if (argc == 5)
        {
            sscanf(argv[2], "%d", &a);
            sscanf(argv[3], "%d", &b);
            sscanf(argv[4], "%d", &c);
        }
        else
        {
            rt_kprintf("Error\n");
            return;
        }
        touch_set_pos((uint16_t)(a), (uint16_t)(b));
        touch_set_time(c);
        return;
    }
    else if (!strcmp(argv[1], "size"))
    {
        if (argc < 4)
        {
            rt_kprintf("Error\n");
            return;
        }
        sscanf(argv[2], "%d", &a);
        sscanf(argv[3], "%d", &b);
        // rt_kprintf("touch size\n");
        touch_set_size((uint16_t)(a), (uint16_t)(b));
        return;
    }
    return;
}
// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, touch, touch_cmd, test);// FINSH_FUNCTION_EXPORT_ALIAS(mouse_cmd, __cmd_mouse, mouse);

// FINSH_FUNCTION_EXPORT_ALIAS(touch_cmd, __cmd_touch, touch screen);
#endif
