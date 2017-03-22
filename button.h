/*
 * button.h
 *
 *  Created on: 10 Mar 2017
 *      Author: s1243303
 */
#include "interrupts.h"
#include "MK70F12.h"
#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#define BTN_UP 0
#define BTN_DOWN 1

#define BTN0 0
#define BTN1 1

// IRQs from table 86 in K70 manual
// Button 0 is PORTD bit 0
#define BTN0_BIT	(1 << 0)
#define PORTD_IRQ 90

// Button 1 is PORTE bit 26
#define BTN1_BIT	(1 << 26)
#define PORTE_IRQ 91

// PORTD and PORTE have the same NVIC idx (2) and the same IPR register
#define BTN_NVIC_IDX NVIC_IDX(PORTD_IRQ)
#define BTN_NVIC_IPR NVIC_IPR_REG(PORTD_IRQ)
#define PORTD_NVIC_ISER NVIC_ISER(NVIC_IDX(PORTD_IRQ))
#define PORTE_NVIC_ISER NVIC_ISER(NVIC_IDX(PORTE_IRQ))
#define PORTD_NVIC_ICPR NVIC_ICPR(NVIC_IDX(PORTD_IRQ))
#define PORTE_NVIC_ICPR NVIC_ICPR(NVIC_IDX(PORTE_IRQ))
// the interrupt vector bits for button 0 and 1
#define BTN0_NVIC_BIT NVIC_BIT(PORTD_IRQ)
#define BTN1_NVIC_BIT NVIC_BIT(PORTE_IRQ)

extern void btn_init();
extern void btn_interrupt_enable();
extern int btn_get(int btn_id);
extern int btn_single_pulse(int btn_id);


#endif /* SRC_BUTTON_H_ */
