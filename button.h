/*
 * button.h
 *
 *  Created on: 10 Mar 2017
 *      Author: s1243303
 */
#include "interrupts.h"

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#define BTN_UP 0
#define BTN_DOWN 1

#define BTN0 0
#define BTN1 1
// PORTD bit 0
#define BTN0_BIT	(1 << 0)
#define BTN0_IRQ 90

// PORTE bit 0
#define BTN1_BIT	(1 << 26)
#define BTN1_IRQ 91

// button 0 and 1 have the same NVIC
#define BTN_NVIC NVIC_IDX(BTN0_IRQ)
// and the same IPR register
#define BTN_NVIC_IPR NVIC_IPR_REG(BTN0_IRQ)

extern void btn_init();
extern int btn_interrupt_enable();
extern int btn_get(int btn_id);
extern int btn_single_pulse(int btn_id);


#endif /* SRC_BUTTON_H_ */
