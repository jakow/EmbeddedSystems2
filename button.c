/*
 * button.c
 *
 *  Created on: 10 Mar 2017
 *      Author: s1243303
 */
#include "button.h"
#include "MK70F12.h"
//   pull up resistor

#define IS_GPIO  (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK)

static int btn_state[2];

void btn_interrupt_enable() {
  // set enable interrupts
	PORTD_NVIC_ISER |= BTN0_NVIC_BIT;
	PORTE_NVIC_ISER |= BTN1_NVIC_BIT;
	// clear pending interupts
	PORTD_NVIC_ICPR |= BTN0_NVIC_BIT;
	PORTE_NVIC_ICPR |= BTN1_NVIC_BIT;
  // set GPIO interrupt behaviour (IRQC)in the Port Control Register (PCR)
	PORTD_PCR0 |= PORT_PCR_IRQC(0xA); // interrupt on falling edge
	PORTE_PCR26 |= PORT_PCR_IRQC(0xA);
}

void btn_init() {
	// enable clock gates on the ports
	SIM_SCGC5 |=
			SIM_SCGC5_PORTD_MASK |
			SIM_SCGC5_PORTE_MASK;

  // set the pin multiplexer function to gpio 
	PORTD_PCR0 	= IS_GPIO;
	PORTE_PCR26 = IS_GPIO;

	// set direction
	// clear button 0 flag to set as input
	GPIOD_PDDR &= ~BTN0_BIT;
	// clear button 0 flag to set as input
	GPIOE_PDDR &= ~BTN1_BIT;
	// set default input values
	btn_state[0] = 0;
	btn_state[1] = 0;
}

// get the current value of the button. 1 - pressed, 0 - not pressed
int btn_get(int btn_id) {
	switch (btn_id) {
	case BTN0:
		return (GPIOD_PDIR & BTN0_BIT) == 0;
	case BTN1:
		return (GPIOE_PDIR & BTN1_BIT) == 0;
	default:
		return 0;

	}
}

// use this function to continuously poll if a button was pressed.
// this function returns 1 when there was a recent change of state from pressed
// to released.
//state 0: has not been pressed
//state 1: has been pressed
//returns 1 on falling edge (after pressed and released)
int btn_single_pulse(int btn_id) {
	if (!btn_get(btn_id) && btn_state[btn_id]){
		btn_state[btn_id] = 0;
		return 1;
	} else if (btn_get(btn_id)) {
		btn_state[btn_id] = 1;
		return 0;
	} else {
		return 0;
	}
}
