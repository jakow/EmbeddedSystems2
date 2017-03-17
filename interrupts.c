#include "interrupts.h"
#include "MK70F12.h"

#define NVIC_IDX(irq) (irq / 32)
#define NVIC_IPR_REG(irq) (irq / 4)
#define NVIC_BIT(irq) (irq % 32)
#define UART2_IRQ 49
#define UART2_IDX NVIC_IDX(UART2_IRQ)
#define UART2_NVIC_BIT NVIC_BIT(UART2_IRQ)
#define UART2_NVIC_ISER NVIC_ISER_REG(NVIC_BASE_PTR, NVIC_IDX(UART2_IRQ))
// uart2 nvic iser  is nviciser1


void pit_init() {

  PIT_MCR_REG(PIT_BASE_PTR) &= ~PIT_MCR_MDIS_MASK; // un-disable the PIT
  PIT_LDVAL0 = (uint32_t) 50000000/8000;
  PIT_TFLG0 |= PIT_TFLG_TIF_MASK; // clear current interrupt just in case
  PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK; // enable PIT interrupts
  /* interrupts will not be fired until the timer is enabled with pit_start()
  */
}

void pit_start() {
  // enable the timer
  PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
}

// UART2 vector: 0x0000_0104
void uart2_interrupt_enable() {
  // Vector:
  // IRQ: 49
  //NVIC idx: IRQ / 32 = 1ve
  UART2_NVIC_ISER |= UART2_NVIC_BIT;
  // IPR: 32 / 4 = 4
  // bit location: IRQ % 32 = 17
  // set bit 17 in nviciser1. See defines above
  UART2_NVIC_ISER |= UART2_NVIC_BIT;
  UART2_C2 |= UART_C2_RIE_MASK;

}

void button_interrupt_enable() {
  // enable button NVIC
  // set GPIO interrupt behaviour (IRQC) - falling/rising edge
  // You would need to reset the interrupt manually from the handler function
  //to indicate that it has been handled. You do that using one of the PORTx_y
  // registers. You'll figure out which one by looking at pages
  // 309-315 in the same document.
  // write a button handler
}
