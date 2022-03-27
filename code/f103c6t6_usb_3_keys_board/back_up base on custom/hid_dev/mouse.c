#include "mouse.h"
#ifdef USING_PID
#include "pid.h"
#include "stdlib.h"
#include "math.h"
#endif

Mouse_buff tMouse_buff;
Mouse_buff tMouse_buff_last;

mouse_state_t mouse_state;

void mouse_init(void)
{
#ifdef USING_PID
    PID_struct_init(&pid_x, POSITION_PID, 100.f, 100.f, 0.6f, 0.0f, 0.2f);
    PID_struct_init(&pid_y, POSITION_PID, 100.f, 100.f, 0.6f, 0.0f, 0.2f);
#endif
    memset(&tMouse_buff, 0X00, sizeof(tMouse_buff));
    tMouse_buff.report_id = 0x02;
    memset(&mouse_state, 0X00, sizeof(mouse_state));
    mouse_state.is_ok = 1;
}

void send_mouse_data(void)
{
    static uint8_t i;

    if (mouse_state.continue_function)
    {
        continue_function();
    }
    if (mouse_state.x == mouse_state.cur_x && mouse_state.y == mouse_state.cur_y)
    {
        tMouse_buff.mouse_rel_x = 0;
        tMouse_buff.mouse_rel_y = 0;
    }
    else
    {

#ifdef USING_PID
        tMouse_buff.mouse_rel_x = (int8_t)pid_calc(&pid_x, mouse_state.cur_x, mouse_state.x);
        tMouse_buff.mouse_rel_y = (int8_t)pid_calc(&pid_y, mouse_state.cur_y, mouse_state.y);

        if (tMouse_buff.mouse_rel_x == 0 && tMouse_buff.mouse_rel_y == 0)
        {
            mouse_state.x = mouse_state.cur_x;
            mouse_state.y = mouse_state.cur_y;
        }
#else
        tMouse_buff.mouse_rel_x = mouse_state.x - mouse_state.cur_x;
        tMouse_buff.mouse_rel_y = mouse_state.y - mouse_state.cur_y;
#endif
        mouse_state.cur_x += tMouse_buff.mouse_rel_x;
        mouse_state.cur_y += tMouse_buff.mouse_rel_y;
    }
    for (i = 0; i < 3; i++)
    {
        if (mouse_state.key[i] > 0)
        {
            mouse_state.key[i]--;
            tMouse_buff.key |= 0x01u << i;
        }
        else if (mouse_state.key[i] < 0)
        {
            tMouse_buff.key |= 0x01u << i;
        }
        else
        {
            tMouse_buff.key &= ~(0x01u << i);
            mouse_state.key[i] = mouse_state.continue_key[i];
        }
    }
    if (memcmp(&tMouse_buff_last, &tMouse_buff, sizeof(tMouse_buff)) == 0)
    {
    }
    else
    {
        memcpy(&tMouse_buff_last, &tMouse_buff, sizeof(tMouse_buff));
        USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&tMouse_buff, sizeof(tMouse_buff));
    }
}

void set_continue_click(enum mouse_key key, int8_t time)
{
    mouse_state.continue_key[key] = (uint8_t)time;
}
void set_click(enum mouse_key key, int8_t time)
{
    mouse_state.key[key] = time;
}
void set_continue_function(uint8_t s)
{
    mouse_state.continue_function = s;
}
int randint(int a, int b)
{
    static int r;
    r = b - a;
    return ((rand() % r) + a);
}
void rand_reset(void)
{
    srand(HAL_GetTick());
}
void continue_function(void)
{
    static float deg;
    static int r;
    deg += 0.22f;
    deg += (randint(0, 10)) * 0.01f;
    if (deg > 6.283f)
    {
        deg -= 6.283f;
    }
    r = randint(60, 65);
    // r = 60;
    mouse_state.x = cos(deg) * r;
    mouse_state.y = sin(deg) * r;
}
void mouse_cmd(int argc, char **argv)
{
    static int32_t a, b;
    if (argc < 2)
    {
        rt_kprintf("Error\n");
        return;
    }
    // key = cmd_parsing(argv[1]);
    if (!strcmp(argv[1], "down"))
    {
        // rt_kprintf("touch down\n");
        // set_touch_flag(-1);
        return;
    }
    else if (!strcmp(argv[1], "up"))
    {
        // rt_kprintf("touch up\n");
        // set_touch_flag(0);
        return;
    }
    else if (!strcmp(argv[1], "move"))
    {
        if (argc < 4)
        {
            rt_kprintf("Error\n");
            return;
        }
        sscanf(argv[2], "%d", &a);
        sscanf(argv[3], "%d", &b);
        // rt_kprintf("touch pos\n");
        // set_touch_pos((uint16_t)(a), (uint16_t)(b));
        mouse_state.x += a;
        mouse_state.y += b;
        return;
    }
    else if (!strcmp(argv[1], "tap"))
    {
        // c = 13;
        if (argc == 4)
        {
            sscanf(argv[2], "%d", &a);
            sscanf(argv[3], "%d", &b);
        }
        // else if (argc == 5)
        // {
        //     sscanf(argv[2], "%d", &a);
        //     sscanf(argv[3], "%d", &b);
        //     sscanf(argv[4], "%d", &c);
        // }
        else
        {
            rt_kprintf("Error\n");
            return;
        }
        // rt_kprintf("touch tap\n");
        // set_touch_pos((uint16_t)(a), (uint16_t)(b));
        // set_touch_flag(13);
        // rt_kprintf("ok\n");
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
        // touch_set_size((uint16_t)(a), (uint16_t)(b));
        return;
    }

    // sscanf(argv[1], "%x", &key);
    return;
}

// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, mouse, mouse_cmd, test);// FINSH_FUNCTION_EXPORT_ALIAS(mouse_cmd, __cmd_mouse, mouse);
