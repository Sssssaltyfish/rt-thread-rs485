/*
 * rs485.h
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-08     qiyongzhong       first version
 * 2020-12-17     qiyongzhong       add sample
 * 2020-12-18     qiyongzhong       add rs485_send_then_recv
 * 2023-09-19     qiyongzhong       add switch delay
 * 2024-12-05     qiyongzhong       add dma-rx, int-tx, dma-tx
 * 2024-12-05     qiyongzhong       add making device
 */

#ifndef __RS485_H__
#define __RS485_H__

#include <rtconfig.h>

#ifdef __cplusplus
extern "C"
{
#endif

//#define RS485_USING_DEV             //使用RS485设备化
//#define RS485_USING_TEST            //使用测试功能
//#define RS485_USING_SAMPLE_SLAVE    //使用从机示例
//#define RS485_USING_SAMPLE_MASTER   //使用主机示例
//#define RS485_USING_DMA_RX          //使用DMA接收
//#define RS485_USING_INT_TX          //使用中断发送
//#define RS485_USING_DMA_TX          //使用DMA发送

#ifndef RS485_SW_DLY_US
#define RS485_SW_DLY_US             0    //发送引脚控制切换延时
#endif

#define RS485_TX_COMP_TMO_MAX       (3 * RT_TICK_PER_SECOND)//最大DMA传输完成超时
#define RS485_BYTE_TMO_MIN          2     //最小字节超时
#define RS485_BYTE_TMO_MAX          200   //最大字节超时

typedef struct rs485_inst rs485_inst_t;

#ifdef RS485_USING_DEV
#include <rs485_dev.h>
#endif

/* 
 * @brief   create rs485 instance dynamically
 * @param   serial      - serial device name
 * @param   baudrate    - serial baud rate
 * @param   parity      - serial parity mode
 * @param   pin         - mode contrle pin
 * @param   level       - send mode level
 * @retval  instance handle
 */
rs485_inst_t * rs485_create(const char *serial, int baudrate, int parity, int pin, int level);

/* 
 * @brief   destroy rs485 instance created dynamically
 * @param   hinst       - instance handle
 * @retval  0 - success, other - error
 */
int rs485_destroy(rs485_inst_t * hinst);

/* 
 * @brief   config rs485 params 
 * @param   hinst       - instance handle
 * @param   baudrate    - baudrate of communication
 * @param   databits    - data bits, 5~8
 * @param   parity      - parity bit, 0~2, 0 - none, 1 - odd, 2 - even
 * @param   stopbits    - stop bits, 0~1, 0 - 1 stop bit, 1 - 2 stop bits
 * @retval  0 - success, other - error
 */
int rs485_config(rs485_inst_t * hinst, int baudrate, int databits, int parity, int stopbits);

/* 
 * @brief   set wait datas timeout for receiving 
 * @param   hinst       - instance handle
 * @param   tmo_ms      - receive wait timeout, 0--no wait, <0--wait forever, >0--wait timeout, default = 0
 * @retval  0 - success, other - error
 */
int rs485_set_recv_tmo(rs485_inst_t * hinst, int tmo_ms);
 
/* 
 * @brief   set byte interval timeout for receiving
 * @param   hinst       - instance handle
 * @param   tmo_ms      - byte interval timeout, default is calculated from baudrate
 * @retval  0 - success, other - error
 */
int rs485_set_byte_tmo(rs485_inst_t * hinst, int tmo_ms);

/* 
 * @brief   open rs485 connect
 * @param   hinst       - instance handle
 * @retval  0 - success, other - error
 */
int rs485_connect(rs485_inst_t * hinst);

/* 
 * @brief   close rs485 connect
 * @param   hinst       - instance handle
 * @retval  0 - success, other - error
 */
int rs485_disconn(rs485_inst_t * hinst);

/* 
 * @brief   receive datas from rs485
 * @param   hinst       - instance handle
 * @param   buf         - buffer addr
 * @param   size        - maximum length of received datas
 * @retval  >=0 - length of received datas, <0 - error
 */
int rs485_recv(rs485_inst_t * hinst, void *buf, int size);

/* 
 * @brief   send datas to rs485
 * @param   hinst       - instance handle
 * @param   buf         - buffer addr
 * @param   size        - length of send datas
 * @retval  >=0 - length of sent datas, <0 - error
 */
int rs485_send(rs485_inst_t * hinst, const void *buf, int size);

/* 
 * @brief   break rs485 receive wait
 * @param   hinst       - instance handle
 * @retval  0 - success, other - error
 */
int rs485_break_recv(rs485_inst_t * hinst);

/* 
 * @brief   send data to rs485 and then receive response data from rs485
 * @param   hinst       - instance handle
 * @param   send_buf    - send buffer addr
 * @param   send_len    - length of send datas
 * @param   recv_buf    - recv buffer addr
 * @param   recv_size   - maximum length of received datas
 * @retval  >=0 - length of received datas, <0 - error
 */
int rs485_send_then_recv(rs485_inst_t * hinst, void *send_buf, int send_len, void *recv_buf, int recv_size);

#ifdef __cplusplus
}

#endif
#endif

