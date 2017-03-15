/*
 * uart.c
 *
 *  Created on: 13 Mar 2017
 *      Author: s1243303
 */
#include "uart.h"
#include "MK70F12.h"


uart_init(uint32_t clk_hz, uint32_t baud) {
	uint16_t sbr, brfa;
	uint8_t temp_reg;
	// Enable clock for PORTF where the UART0 pins sit
	SIM_SCGC5 |= SIM_SCGC5_PORTF_MASK;
	// Enable clock for UART0
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	// set correct pin muxing
	//enable UART0_RX on pin PTF18
	//(see page 275 of Tower manual for the pin alternatives )
	PORTF_PCR18 = PORT_PCR_MUX(4); // UART is ALT4 function for this pin
   	// Enable UART0_RX function on PTF17
	PORTF_PCR17 = PORT_PCR_MUX(4); // UART is ALT4 function for this pin

	// disable receiver and transmitter when setting options
    UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
    /* Set the default operation configuration:  8-bit mode, no parity:
     * 7		6			5 		4		3		2		1		0
     * LOOPS	UARTSWAI	RSRC	MODE	WAKE	ILT		PE		PT
     * MODE: 0 = 8bit; 1 = 9bit
     * PE (Parity Enable): 1=enable, 0=disable
     * God knows what the rest of the options are. Let's disable them!
    */
    UART_C1_REG(UART0_BASE_PTR) = 0;

    //
    sbr = (uint16_t)((clk_hz)/(baud * 16));
    // save previous value of BDH_REG with the SBR value cleared
    temp_reg = UART_BDH_REG(UART0_BASE_PTR) & ~(UART_BDH_SBR(0x1F));
    UART_BDL_REG(UART0_BASE_PTR) = UART_BDL_SBR(sbr);
    UART_BDH_REG(UART0_BASE_PTR) = temp_reg | UART_BDH_SBR(sbr);
    // calculate the fraction from: baud_rate = Fclk/(16*(SBR+BRFA/32))
    brfa = (uint16_t) (2*(clk_hz-16*sbr*baud)/sbr);
    // save previous value of C4 with BRFA cleared
    temp_reg = (UART_C4_REG(UART0_BASE_PTR) & ~UART_C4_BRFA(0x1F));
    UART_C4_REG(UART0_BASE_PTR) = temp_reg |  UART_C4_BRFA(brfa);

}



// toggle the correct uart0_C2 register bit
void uart_rx_set_enable_flag(uint8_t enable) {
	if (enable)
		UART0_C2 |= RX_ENABLE_BIT;
	else
		UART0_C2 &= ~RX_ENABLE_BIT;
}

void uart_tx_set_enable_flag(uint8_t enable) {
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


