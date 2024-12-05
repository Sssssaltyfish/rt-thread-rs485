/*
 * rs485_dev_cfg.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-12-05     qiyongzhong       first version
 */

#ifndef __RS485_DEV_CFG_H__
#define __RS485_DEV_CFG_H__

#include <drv_common.h>

//rs485-device-name, serial-device-name, baudrate, parity(0~2), control-pin, send-level(0~1)
#define RS485_DEV_CFG_TABLE {                               \
    {"rs485-1", "uart1",    9600,   0,  GET_PIN(C, 9),  1}, \
    {"rs485-2", "uart2",    9600,   0,  GET_PIN(B, 6),  1}, \
    {"rs485-3", "uart3",    115200, 0,  -1,             1}, \
}

#endif
