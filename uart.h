/*
 * uart.h
 *
 *  Created on: 13 Mar 2017
 *      Author: s1243303
 */

#ifndef UART_H_
#define UART_H_

#include "MK70F12.h"

#define TX_ENABLE_BIT (1 << 3)
#define RX_ENABLE_BIT (1 << 2)
#define RX_INT_ENABLE_BIT (1 << 5)
#define TX_INT_ENABLE_BIT (1 << 7)
#define TX_INT_COMPL_ENABLE_BIT (1 << 6)

static void (*uart_handlers[4]) (void);
static int num_uart_handlers = 0;
extern void uart0_rx_tx_handler();

extern void uart_init(uint32_t clk_khz, uint32_t baud);


extern void uart_rx_set_enable_flag(uint8_t enable);

extern void uart_tx_set_enable_flag(uint8_t enable);

extern char* uart_read();

extern void uart_write(char* buffer); 

#endif /* UART_H_ */
