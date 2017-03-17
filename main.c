/*
 * Bare metal template created by Harry Wagstaff
 * Based on Freescale Codewarrior Bareboard project template
 * Edited by Stan Manilov
 */

#include "MK70F12.h"

#include "led.h"
#include "button.h"
#include "uart.h"
#include "fpu.h"

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
	SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(0) | SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(1);
	MCG_C1 = MCG_C1_CLKS(2);

	led_init();
	btn_init();
	uart_init(FCLK, BAUD);
	fpu_init();
}

void main()
{
	int state;
	// int i;
	// char buffer[1];

	state = 4;
	while(1) {
		int timer;
		if (btn_single_pulse(BTN1)){
			if (state != 4) led_off(state); //if all not already off
			state = (state == 4) ? 4 : state + 1;
			led_on(state);
		} else if (btn_single_pulse(BTN0)) {
			if (state != 4) led_off(state);
			state = (state == 0) ? 0 : state - 1;
			led_on(state);
		}
		//improvised debouncer until figure out interrupts
		timer = 1000;
		while(timer--) ;
		// if (btn_get(BTN0) == BTN_DOWN) {
		// 	led_on(LED_RED);
		// 	timer = 0;
		// }
		// else {
		// 	timer = 1;
		// 	led_off(LED_RED);
		// }
		// // echo
		// if (uart_getchar(buffer)) {
		// 	uart_putchar(buffer);
		// }
		// uart_write("test", 4);
	}
}
// cyclic / non saturating counter
// state = 4;
// while(1) {
// 	if (btn_single_pulse(BTN1)){
// 		if (state != 4) led_off(state);
// 		state = (state + 1) % 5;
// 		if (state != 4) led_on(state);
// 	} else if (btn_single_pulse(BTN0)) {
// 		if (state != 4) led_off(state);
// 		state = (state) ? (state - 1) % 5 : 4;
// 		if (state != 4) led_on(state);
// 	}
// }
