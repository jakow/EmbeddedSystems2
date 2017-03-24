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

typedef uint8_t bool;

/**
 *
 */
extern void uart_init(uint32_t clk_hz, uint32_t baud);

extern bool uart_getchar(char* ch);

extern void uart_putchar(char ch);

extern bool uart_getsigned(int8_t* num);

extern void uart_putsigned(int8_t num);

extern void uart_read(char* buffer, unsigned int count);

extern void uart_write(char* buffer);

extern void uart_write_n(char* buffer, unsigned int n);

#endif /* UART_H_ */
