#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/* Initialise PIT. Set up the interrupts but do not start requesting them
* To start the interval, need to call pit_start() to enable timer countdown.
* This avoids interrrupts firing when the application is not ready yet.
*/
extern void pit_init();

/**
* Start PIT timer countdown at the end of which interrupts are be fired
*/
extern void pit_start();

extern void uart2_interrupt_enable();

#endif // INTERRUPTS_H_
