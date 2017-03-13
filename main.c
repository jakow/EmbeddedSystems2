/*
 * Bare metal template created by Harry Wagstaff
 * Based on Freescale Codewarrior Bareboard project template
 * Edited by Stan Manilov
 */

#include "MK70F12.h"

#include "led.h"
#include "button.h"
#include "uart.h"
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
	uart_init();
	uart_rx_set_enable_flag(1);
	uart_tx_set_enable_flag(1);

}

void main()
{
	int timer;
	unsigned int count = 1;
	char buffer[1];
	led_on(LED_BLUE);
	led_off(LED_YELLOW);
	led_off(LED_GREEN);
	while(1)
	{
		if (btn_get(BTN0) == BTN_DOWN) {
			led_on(LED_RED);
			timer = 0;
		}
		else {
			timer = 1;
			led_off(LED_RED);
		}
		uart_read(buffer, count);
		uart_write(buffer, count);
//		}
	}
}


