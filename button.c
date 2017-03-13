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
#define IRQC_BOTH_EDGES (11 << PORT_PCR_IRQC_SHIFT)

void btn_init() {
	// enable gates on the ports
	SIM_SCGC5 |=
			SIM_SCGC5_PORTD_MASK |
			SIM_SCGC5_PORTE_MASK;


	PORTD_PCR0 	= IS_GPIO; // | IRQC_BOTH_EDGES;
	PORTE_PCR26 = IS_GPIO; //  | IRQC_BOTH_EDGES;

	// set direction
	// clear button 0 flag to set as output
	GPIOD_PDDR &= ~BIT_BTN0;
	// clear button 0 flag to set as output
	GPIOE_PDDR &= ~BIT_BTN1;
	// set default input values

}

int btn_get(int button_id) {
	switch (button_id) {
	case BTN0:
		return (GPIOD_PDIR & BIT_BTN0) == 0;
	case BTN1:
		return (GPIOE_PDIR & BIT_BTN1) == 0;
	default:
		return 0;

	}
}
