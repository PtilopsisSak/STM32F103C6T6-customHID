#include "touch_screen.h"
#include "stdlib.h"
// #include "string.h"

touch_inf ttouch_inf;
touch_buff ttouch_buff;
touch_buff ttouch_buff_last;
void touch_init(void)
{
    memset(&ttouch_buff, 0X00, sizeof(ttouch_buff));
    ttouch_buff.report_id = 0x04;
    memset(&ttouch_buff_last, 0X00, sizeof(ttouch_buff));
    ttouch_buff_last.report_id = 0x04;
    touch_set_size(1920, 1080);
}

void send_touch_data(void)
{
    static uint8_t k;
    k = 0;
    // ttouch_buff.report_id = 0x04;
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
        if (k)
        {
            // memcpy(&ttouch_buff_last, &ttouch_buff, sizeof(ttouch_buff));
        }
        USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&ttouch_buff, sizeof(ttouch_buff));
    }
}

void touch_set_size(uint16_t x, uint16_t y)
{
    ttouch_inf.x_max = x;
    ttouch_inf.y_max = y;
    ttouch_inf.x_scale = 4095.f / x;
    ttouch_inf.y_scale = 4095.f / y;
}
void set_touch_flag(int16_t f)
{
    // ttouch_buff.touch_flag = !!f;
    ttouch_inf.release = f;
}
void set_touch_pos(uint16_t x, uint16_t y)
{
    srand(HAL_GetTick());
    ttouch_buff.x = (uint16_t)((x)*ttouch_inf.x_scale);
    ttouch_buff.y = (uint16_t)((y)*ttouch_inf.y_scale);
}

// float get_rand(void)
// {
//     return (rand() % 100) / 100.f;
// }

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
        set_touch_flag(-1);
        return;
    }
    else if (!strcmp(argv[1], "up"))
    {
        set_touch_flag(0);
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

        set_touch_pos((uint16_t)(a), (uint16_t)(b));
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
        set_touch_pos((uint16_t)(a), (uint16_t)(b));
        set_touch_flag(c);
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
