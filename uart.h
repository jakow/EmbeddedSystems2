/*
 * uart.h
 *
 *  Created on: 13 Mar 2017
 *      Author: s1243303
 */

#ifndef UART_H_
#define UART_H_

#include "MK70F12.h"
#include "interrupts.h"
#include "k70_bool.h"

#define TX_ENABLE_BIT (1 << 3)
#define RX_ENABLE_BIT (1 << 2)
#define RX_INT_ENABLE_BIT (1 << 5)
#define TX_INT_ENABLE_BIT (1 << 7)
#define TX_INT_COMPL_ENABLE_BIT (1 << 6)

#define UART2_IRQ 49
#define UART2_IDX NVIC_IDX(UART2_IRQ)
#define UART2_NVIC_BIT NVIC_BIT(UART2_IRQ)
#define UART2_NVIC_ISER NVIC_ISER_REG(NVIC_BASE_PTR, NVIC_IDX(UART2_IRQ))

extern void uart_init(uint32_t clk_khz, uint32_t baud);

extern bool uart_getchar(unsigned char* ch);

extern void uart_putchar(unsigned char* ch);

extern void uart_read(unsigned char* buffer, unsigned int count);

extern void uart_write(unsigned char* buffer);

extern void uart_write_n(unsigned char* buffer, unsigned int n);

#endif /* UART_H_ */
