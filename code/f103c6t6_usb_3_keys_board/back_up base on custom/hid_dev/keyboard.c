#include "keyboard.h"
// #include "usbd_hid.h"
// #include <rtthread.h>
// #include "string.h"
keyboard_buff tkeyboard_buff;
keyboard_buff tkeyboard_buff_last;
keyboard_state_t keyboard_state;

const uint8_t board[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 55, 0, 39, 30, 31, 32, 33, 34, 35, 36, 37, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0, 0, 0};
void press(int argc, char **argv)
{
    static uint32_t key;
    if (argc < 2)
    {
        rt_kprintf("Please input scan_code\n");
        // {
        //     sprintf((char *)USART_TX_BUF_PS, (const char *)"Please input scan_code\n");
        //     ps_putc(USART_TX_BUF_PS, t);
        // }
        return;
    }
    sscanf(argv[1], "%x", &key);
    if (key == 0)
    {
        rt_kprintf("code ERROR\n");
        return;
    }
    rt_kprintf("%d is pressd\n", key);
    add_key_code(key, 20);
    return;
}

void pstr(int argc, char **argv)
{
    if (argc < 2)
    {
        rt_kprintf("Please input str\n");
        return;
    }
    press_str(argv[1]);
}

void send_keyboard_data(void)
{
    static uint8_t i, t;
    static uint8_t flag, lastsend;
    if (memcmp(&tkeyboard_buff_last, &tkeyboard_buff, 9) == 0)
    {
        // equal
    }
    else if (lastsend == 1)
    {
        USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&tkeyboard_buff, 9u);
        lastsend = 0;
    }
    else if (lastsend == 2)
    {
        USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&tkeyboard_buff, 9u);
        lastsend = 1;
    }
    else
    {
        memcpy(&tkeyboard_buff_last, &tkeyboard_buff, 9);

        USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&tkeyboard_buff, 9u);
        lastsend = 2;
    }
    flag = 1;

    for (i = 0; i < 8; i++)
    {
        if (tkeyboard_buff.special_key_release_times[i] > 0)
        {
            tkeyboard_buff.special_key_release_times[i]--;
        }

        if (tkeyboard_buff.special_key_release_times[i] == 0)
        {
            tkeyboard_buff.special_key &= ~(0x01 << i);
        }
        else
        {
            flag = 0;
            tkeyboard_buff.special_key |= (0x01 << i);
        }
    }
    for (i = 0; i < 6; i++)
    {
        t = i;
        if (tkeyboard_buff.keys_release_times[i] > 0)
        {
            tkeyboard_buff.keys_release_times[i]--;
        }

        if (tkeyboard_buff.keys_release_times[i] == 0)
        {
            *(tkeyboard_buff.keys + i) = 0;
        }
        else
        {
            flag = 0;
        }
        while (t > 0 && tkeyboard_buff.keys_release_times[t - 1] == 0 && tkeyboard_buff.keys_release_times[t] != 0)
        {
            tkeyboard_buff.keys_release_times[t - 1] = tkeyboard_buff.keys_release_times[t];
            *(tkeyboard_buff.keys + t - 1) = *(tkeyboard_buff.keys + t);
            tkeyboard_buff.keys_release_times[t] = 0;
            *(tkeyboard_buff.keys + t) = 0;
            t--;
        }
    }
    keyboard_state.send_ok = flag;
}

void keyboard_init(void)
{
    memset(&tkeyboard_buff, 0X00, sizeof(tkeyboard_buff));
    memset(&tkeyboard_buff_last, 0X00, sizeof(tkeyboard_buff_last));
    tkeyboard_buff.report_id = 0x01;
    tkeyboard_buff_last.report_id = 0x01;
    memset(&keyboard_state, 0X00, sizeof(keyboard_state));
    keyboard_state.is_ok = 1;
}
void add_key_code(uint8_t k, int8_t times)
{
    static uint8_t i;
    if (k == 0)
    {
        return;
    }
    for (i = 0; i < 6; i++)
    {
        if (*(tkeyboard_buff.keys + i) == k)
        {
            break;
        }

        if (tkeyboard_buff.keys_release_times[i] == 0)
        {
            break;
        }
    }
    if (i == 6)
    {
        return;
    }
    if (times)
    {
        *(tkeyboard_buff.keys + i) = k;
    }
    tkeyboard_buff.keys_release_times[i] = times;
    return;
}
void add_char_code(char a, int8_t time)
{
    add_key_code(board[a], time);
}
void add_special_code(enum keyboard_sp_key k, int8_t times)
{
    if (times)
    {
        tkeyboard_buff.special_key |= (0x01 << k);
    }
    tkeyboard_buff.special_key_release_times[k] = times;
    return;
}
void keyboard_cmd(int argc, char **argv)
{
    static int32_t a, b, t;
    static char *p;
    if (argc < 2)
    {
        rt_kprintf("Error\n");
        return;
    }
    if (!strcmp(argv[1], "press"))
    {
        sscanf(argv[2], "%d", &a);
        b = 20;
        if (argc >= 4)
        {
            sscanf(argv[3], "%d", &b);
        }
        add_key_code(a, b);
        return;
    }
    else if (!strcmp(argv[1], "sp"))
    {
        t = sscanf(argv[2], "%d", &a);
        p = argv[2];
        if (t == 0)
        {
            a = 0;
            if (p[0] == 'l')
                ;
            else
            {
                a += 4;
            }
            switch (p[1])
            {
            case 'c':;
                break;
            case 's':
                a += 1;
                break;
            case 'a':
                a += 2;
                break;
            case 'g':;
                // break;
            case 'w':
                a += 3;
                break;

            default:
                return;
            }
        }

        b = 20;
        if (argc >= 4)
        {
            sscanf(argv[3], "%d", &b);
        }
        add_special_code(a, b);
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
        return;
    }
    else if (!strcmp(argv[1], "tap"))
    {
        if (argc == 4)
        {
            sscanf(argv[2], "%d", &a);
            sscanf(argv[3], "%d", &b);
        }
        else
        {
            rt_kprintf("Error\n");
            return;
        }
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
        return;
    }

    // sscanf(argv[1], "%x", &key);
    return;
}

// FINSH_FUNCTION_EXPORT_ALIAS(keyboard_cmd, __cmd_kb, keyboard);
// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, kb, keyboard_cmd, test);// FINSH_FUNCTION_EXPORT_ALIAS(mouse_cmd, __cmd_mouse, mouse);

void press_str(char *s)
{
    while (*s)
    {
        if (board[*s])
        {
            add_key_code(board[*s], 2);
            // rt_thread_mdelay(11);

            while (keyboard_state.send_ok)
            {
                rt_thread_mdelay(1);
            }
            while (!keyboard_state.send_ok)
            {
                rt_thread_mdelay(2);
            }
            if (*s == *(s + 1))
            {
                rt_thread_mdelay(32);
            }
        }
        s++;
    }
}
