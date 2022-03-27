#include "keyboard.h"

keyboard_buff tkeyboard_buff;
keyboard_buff tkeyboard_buff_last;
keyboard_state_t keyboard_state;
struct keyboard_led_state_t keyboard_led_state;

lwrb_t keyboard_command;
int8_t keyboard_command_buff[COMMAND_SIZE];

enum kbd_co
{
    WAIT,
    SET_SP,
    SET_NOR,
    SET_DELAY,
    WAIT_ZERO,
};
const uint8_t board_non_shift[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 43, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 0, 0, 0, 0, 0, 0, 52, 0, 0, 0, 0, 54, 45, 55, 56, 39, 30, 31, 32, 33, 34, 35, 36, 37, 38, 0, 51, 0, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 49, 48, 0, 0, 53, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0, 0, 0};
const uint8_t board_with_shift[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30, 52, 32, 33, 34, 36, 0, 38, 39, 37, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 0, 54, 0, 55, 56, 31, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0, 35, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 49, 48, 53, 0};
const uint8_t board_keypad[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 87, 0, 86, 99, 84, 98, 89, 90, 91, 92, 93, 94, 95, 96, 97, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void send_keyboard_data(void)
{
    static uint8_t i, t;
    static uint8_t flag, lastsend;
    static int8_t data[3];
    static int16_t delay_time;
    while (lwrb_get_full(&keyboard_command) >= 3 && data[0] != SET_DELAY)
    {
        lwrb_read(&keyboard_command, (uint8_t *)data, 3);
        switch (data[0])
        {
        case SET_SP:
            add_special_code((enum keyboard_sp_key)data[1], data[2]);
            break;
        case SET_NOR:
            add_key_code(*((uint8_t *)(data + 1)), data[2]);
            break;
        case SET_DELAY:
            delay_time = (data[1] << 8) | (data[2] & 0x00ff);
            break;
        }
    }
    if (data[0] == SET_DELAY)
    {
        delay_time -= SEND_DELAY;
        if (delay_time < 0)
        {
            data[0] = WAIT;
        }
    }

    if (memcmp(&tkeyboard_buff_last, &tkeyboard_buff, 9) == 0)
    {
        // equal
        if (lastsend)
        {
            lastsend--;
            USBD_CUSTOM_HID_SendReport_FS((uint8_t *)&tkeyboard_buff, 9u);
        }
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
    memset(&keyboard_state, 0X00, sizeof(keyboard_state));
    lwrb_init(&keyboard_command, (uint8_t *)keyboard_command_buff, COMMAND_SIZE);
}
void add_special_code(enum keyboard_sp_key k, int8_t reprot_times)
{
    if (reprot_times)
    {
        tkeyboard_buff.special_key |= (0x01 << k);
    }
    tkeyboard_buff.special_key_release_times[k] = reprot_times;
    return;
}

void add_key_code(uint8_t k, int8_t reprot_times)
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
    if (reprot_times)
    {
        *(tkeyboard_buff.keys + i) = k;
    }
    tkeyboard_buff.keys_release_times[i] = reprot_times;
    return;
}
void kbd_write_command(int8_t a, int8_t b, int8_t c)
{
    int8_t data[3] = {a, b, c};
    lwrb_write(&keyboard_command, data, 3);
}

void keyboard_delay(int16_t time_ms)
{
    kbd_write_command(SET_DELAY, time_ms >> 8, time_ms & 0x00ff);
}
void keyboard_press_sp_key(enum keyboard_sp_key k, int8_t reprot_times)
{
    kbd_write_command(SET_SP, (int8_t)k, reprot_times);
}
void keyboard_press_key_code(uint8_t k, int8_t reprot_times)
{
    kbd_write_command(SET_NOR, (int8_t)k, reprot_times);
}
void keyboard_press_char(char a, int8_t reprot_times)
{
    if (board_non_shift[a])
    {
        keyboard_press_key_code(board_non_shift[a], reprot_times);
    }
    else if (board_with_shift[a])
    {
        keyboard_press_sp_key(LEFT_SHIFT, reprot_times);
        keyboard_press_key_code(board_with_shift[a], reprot_times);
    }
}
void keyboard_press_keypad_char(char a, int8_t reprot_times)
{
    if (board_keypad[a])
    {
        keyboard_press_key_code(board_keypad[a], reprot_times);
    }
}

void keyboard_press_str(char *s, int16_t time_ms)
{
    static uint8_t lastsend;
    static uint8_t totalsend;
    uint8_t last, cur;
    if (time_ms > 0)
    {
        while (*s)
        {
            if (board_non_shift[*s])
            {
                keyboard_press_key_code(board_non_shift[*s], 1);
            }
            else if (board_with_shift[*s])
            {
                keyboard_press_sp_key(LEFT_SHIFT, 1);
                keyboard_press_key_code(board_with_shift[*s], 1);
            }
            keyboard_delay(time_ms);
        }
    }
    else
    {
        while (*s)
        {
            if (totalsend == 6 || (lastsend == *s))
            {
                totalsend = 0;
                keyboard_delay(5);
            }

            if (board_non_shift[*s])
            {
                cur = 1;
                if (last != cur)
                {
                    totalsend = 0;
                    keyboard_delay(5);
                }

                keyboard_press_key_code(board_non_shift[*s], 1);
                totalsend++;
            }
            else if (board_with_shift[*s])
            {
                totalsend++;
                cur = 2;

                if (last != cur)
                {
                    totalsend = 0;
                    keyboard_delay(5);
                }
                keyboard_press_sp_key(LEFT_SHIFT, 1);
                keyboard_press_key_code(board_with_shift[*s], 1);
            }

            last = cur;
            lastsend = *s;
            s++;
        }
    }
}

#if USING_SHELL
void press(int argc, char **argv)
{
    static uint32_t key;
    if (argc < 2)
    {
        rt_kprintf("Please input scan_code\n");
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
    keyboard_press_str(argv[1]);
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
    return;
}

// FINSH_FUNCTION_EXPORT_ALIAS(keyboard_cmd, __cmd_kb, keyboard);
// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) | SHELL_CMD_DISABLE_RETURN, kb, keyboard_cmd, test);// FINSH_FUNCTION_EXPORT_ALIAS(mouse_cmd, __cmd_mouse, mouse);
#endif
