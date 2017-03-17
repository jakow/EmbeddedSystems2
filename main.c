/*
 * Bare metal template created by Harry Wagstaff
 * Based on Freescale Codewarrior Bareboard project template
 * Edited by Stan Manilov
 */
#include "MK70F12.h"
#include <stdio.h>
#include "led.h"
#include "button.h"
#include "uart.h"
#include "fpu.h"
#include "dsp.h"
#include "interrupts.h"

#define FCLK 50000000
#define BAUD 115200
// __init_hardware is called by the Freescale __thumb_startup function (see
// vectors.c)
void __init_hardware()
{
	// Disable the Watchdog module. This module is designed to reset
	// the board in case it crashes for some reason. We don't need it,
	// so we disable it here.
	WDOG_UNLOCK = 0xC520;
	WDOG_UNLOCK = 0xD928;
	WDOG_STCTRLH = 0xD2;

	// Configure the MCG - set up clock dividers on
	SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(0) |
		SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(1);
	MCG_C1 = MCG_C1_CLKS(2);

	led_init();
	btn_init();
	uart_init(FCLK, BAUD);
	fpu_init();
	uart2_interrupt_enable();
}



int main()
{
	int filter_id;
	int timer;
	unsigned char charval;
	float floatval;
	char buffer[16];
	// create a filter
	fltType* filter = flt_create();

	// filter_id < 4 means that some filter 0 to 3 is enabled
	// filter_id == 4 means filter is disabled
	filter_id = 4;
	while(1) {
		// if (btn_single_pulse(BTN1)){
		// 	if (filter_id != 4) led_off(filter_id);
		// 	filter_id = (filter_id == 4) ? 4 : filter_id + 1;
		// 	led_on(filter_id);
		// } else if (btn_single_pulse(BTN0)) {
		// 	if (filter_id) led_off(filter_id);
		// 	filter_id = (filter_id == 0) ? 0 : filter_id - 1;
		// 	led_on(filter_id);
		// }
		//improvised debouncer until figure out interrupts
		// timer = 1000;
		// while(timer--);
		// if (uart_getchar(&charval)) {
		// 	floatval = dsp_chartofloat(charval); // conver to +/- 1 float
		// 	if (filter_id < 4) {
		// 		flt_writeInput(filter, floatval, select_filter(filter_id));
		// 		floatval = flt_readOutput(filter);
		// 	}
		// 	charval = dsp_floattochar(floatval);
		// 	uart_putchar(&charval);
		// 	// uart_write((unsigned char*) buffer, 4);
		// }
	}
}
