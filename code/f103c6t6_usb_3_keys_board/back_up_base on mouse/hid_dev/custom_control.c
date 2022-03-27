/*
 * @Author: Ptisak
 * @Date: 2022-03-18 20:57:47
 * @LastEditors: Ptisak
 * @LastEditTime: 2022-03-21 11:17:14
 * @Description: file content
 */
#include "custom_control.h"
#include "usbd_hid.h"

custom_buff_t custom_buff;
custom_buff_t custom_buff_last;

void send_custom_control_data(void)
{
    static uint8_t i;
    static uint8_t lastsend;
    if (memcmp(&custom_buff, &custom_buff_last, 2) == 0)
    {
        // equal
    }
    else if (lastsend == 1)
    {
        USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&custom_buff, 2u);
        lastsend = 0;
    }
    else
    {
        memcpy(&custom_buff_last, &custom_buff, 2);
        USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)&custom_buff, 2u);
        lastsend = 1;
    }

    for (i = 0; i < 4; i++)
    {
        if (custom_buff.special_key_release_times[i] > 0)
        {
            custom_buff.special_key_release_times[i]--;
        }

        if (custom_buff.special_key_release_times[i] == 0)
        {
            custom_buff.special_key &= ~(0x01 << i);
        }
        else
        {
            custom_buff.special_key |= (0x01 << i);
        }
    }
}

void custom_control_init(void)
{
    memset(&custom_buff, 0X00, sizeof(custom_buff));
    memset(&custom_buff_last, 0X00, sizeof(custom_buff_last));
    custom_buff.report_id = 0x05;
}

void add_custom_control(enum custom_key k, int8_t times)
{
    if (times)
    {
        custom_buff.special_key |= (0x01 << k);
    }
    custom_buff.special_key_release_times[k] = times;
    return;
}
