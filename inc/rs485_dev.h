/*
 * rs485_dev.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2024-12-05     qiyongzhong       first version
 */

#ifndef __RS485_DEV_H__
#define __RS485_DEV_H__

#include <rtdevice.h>

#define RS485_CTRL_CFG              0
#define RS485_CTRL_SET_TMO          1
#define RS485_CTRL_BREAK_RECV       2
#define RS485_CTRL_SEND_THEN_RECV   3

typedef struct{
    const char *rs485;//rs485 device name
    const char *serial;//serial device name
    int baudrate;//baudrate of communication
    int parity;//parity bit, 0~2, 0 - none, 1 - odd, 2 - even
    int pin;//mode contrle pin
    int level;//send mode level
}rs485_dev_cfg_t;

typedef struct{
    int baudrate;
    int databits;
    int parity;
    int stopbits;
}rs485_dev_cfg_param_t;

typedef struct{
    int ack_tmo_ms;
    int byte_tmo_ms;
}rs485_dev_tmo_param_t;

typedef struct{
    void *sbuf;
    int slen;
    void *rbuf;
    int rlen;
}rs485_dev_send_then_recv_param_t;

typedef struct
{
    struct rt_device parent;
    rs485_inst_t *hinst;
}rs485_dev_t;

#endif
