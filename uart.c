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


//Is MUXing the same thing as masking certain bits....?

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


//but num_uart_handlers == 0??? 
void uart0_rx_tx_handler() {
	int i;
	// call each uart handler
	for (i = 0; i < num_uart_handlers; ++i) {
		(*uart_handlers[i])();
	}
}

//Also which UART port are we using? Or is it arbitrary? 

char* uart_read() {
	return UART0_D; 
}

void uart_write(char *buffer) {
	UART0_D = *buffer;
}


//UART baud rate = UART module clock / (16 × (SBR[12:0] + BRFD))
//50*10^6 / 115200 /60 = 27 approximately
void uart_set_baud_rate(int rate) {
	//UART0_BDH = 0;
	UART0_BDL = 27;
}


