#include "interrupts.h"
#include "MK70F12.h"




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
