/*
 * uart.c
 *
 *  Created on: 13 Mar 2017
 *      Author: s1243303
 */
#include "uart.h"
#include "MK70F12.h"

void uart_init(uint32_t clk_hz, uint32_t baud) {
	uint16_t sbr, brfa;
	uint8_t temp_reg;
	// Enable clock for PORTE where the UART2 pins sit
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	// Enable clock for UART2
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;;
	// set correct pin muxing
	/* enable UART2_RX on pin PORTE16
	 * (see page 275 of Tower manual for the pin alternatives )
	 */
	PORTE_PCR16 = PORT_PCR_MUX(3); // UART2 is ALT3 function for this pin*/
   	// Enable UART0_RX function on PORTE17
	PORTE_PCR17 = PORT_PCR_MUX(3); // UART is ALT3 function for this pin

	// disable receiver and transmitter when setting options
  UART2_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
    /* Set the default operation configuration:  8-bit mode, no parity:
     * 7		6			5 		4		3		2		1		0
     * LOOPS	UARTSWAI	RSRC	MODE	WAKE	ILT		PE		PT
     * MODE: 0 = 8bit; 1 = 9bit
     * PE (Parity Enable): 1=enable, 0=disable
     * God knows what the rest of the options are. Let's disable them!
    */
  UART2_C1 = 0;

    //
  sbr = (uint16_t)((clk_hz)/(baud * 16));
  // save previous value of BDH_REG with the SBR value cleared
  temp_reg = UART2_BDH & ~(UART_BDH_SBR(0x1F));
  UART2_BDL = UART_BDL_SBR(sbr);
  UART2_BDH = temp_reg | UART_BDH_SBR(sbr);
  // calculate the fraction from: baud_rate = Fclk/(16*(SBR+BRFA/32))
  brfa = (uint16_t) (2*(clk_hz-16*sbr*baud)/baud);
  // save previous value of C4 with BRFA cleared
  temp_reg = (UART2_C4 & ~UART_C4_BRFA(0x1F));
	// write the new value of brfa
  UART2_C4 = temp_reg |  UART_C4_BRFA(brfa);
  // enable receiver and transmitter
  UART2_C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;
}

/**
 * uart_getchar
 * get a character into the buffer if present
 * returns 1 if there was a character present
 * returs 0 if there was no character to be read
 */
bool uart_getchar(char* ch) {
	bool char_present = (UART2_S1 & UART_S1_RDRF_MASK) != 0;
	// check if there is a character to be read
	if (char_present) {
		// get data
		*ch = UART2_D;
	}
	return char_present;
}

void uart_putchar(char ch) {
	// wait until there is some space to write the char
	// TDRE sets when there is some space in the FIFO
    while(!(UART2_S1 & UART_S1_TDRE_MASK));
		UART2_D = ch;
}

bool uart_getsigned(int8_t* num) {
	bool num_present = (UART2_S1 & UART_S1_RDRF_MASK) != 0;
	// check if there is a character to be read
	if (num_present) {
		// get data
		*num = UART2_D;
	}
	return num_present;
}

void uart_putsigned(int8_t num) {
	while(!(UART2_S1 & UART_S1_TDRE_MASK));
	UART2_D = num;
}

void uart_read(char* buffer, unsigned int count) {
	while(count > 0) {
		while(!uart_getchar(buffer)); // wait until there is a char to be read
		count--;
	}
}
void uart_write(char *buffer) {
	// write until char array is null. Obviously very dangerous when your string
	// is not null-terminated. If not sure use uart_write_n
	while(*buffer != '\0') {
		uart_putchar(*buffer++);
	}
}
void uart_write_n(char *buffer, unsigned int n) {
	// check if done counting and char is not null
	while(n > 0 && *buffer != '\0') {
		uart_putchar(*buffer++);
		n--;
	}
}
