#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "MK70F12.h"
#define NVIC_IDX(irq) (irq / 32)
#define NVIC_IPR_REG(irq) (irq / 4)
#define NVIC_BIT(irq) (1 << (irq % 32))


// uart2 nvic iser  is nviciser1
/* Initialise PIT. Set up the interrupts but do not start requesting them
* To start the interval, need to call pit_start() to enable timer countdown.
* This avoids interrrupts firing when the application is not ready yet.
*/
extern void pit_init();

/**
* Start PIT timer countdown at the end of which interrupts are be fired
*/
extern void pit_start();

#endif // INTERRUPTS_H_
