/*
 * uart.c
 *
 *  Created on: 13 Mar 2017
 *      Author: s1243303
 */
#include "uart.h"
#include "MK70F12.h"


void uart_init() {
	SIM_SCGC4 |= UART0_CLK_ENABLE;
}

// toggle the correct uart0_C2 register bit
void uart_rx_set_enable_flag(int enable) {
	if (enable)
		UART0_C2 |= RX_ENABLE_BIT;
	else
		UART0_C2 &= ~RX_ENABLE_BIT;
}

void uart_tx_set_enable_flag(int enable) {
	if (enable)
		UART0_C2 |= TX_ENABLE_BIT;
	else
		UART0_C2 &= ~TX_ENABLE_BIT;
}

void uart0_rx_tx_handler() {
	int i;
	// call each uart handler
	for (i = 0; i < num_uart_handlers; ++i) {
		(*uart_handlers[i])();
	}
}

void uart_read(char *buffer, unsigned int count) {
	// TODO: your task, Joel ;)
}

void uart_write(char *buffer, unsigned int count) {
	// TODO: as above
}


