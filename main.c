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
#include <stdbool.h>
#define FCLK 50000000
#define BAUD 115200
#define NO_FILTER -1
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

	fpu_init();
	led_init();
	btn_init();
	uart_init(FCLK, BAUD);
	uart_interrupt_enable();
	btn_interrupt_enable();
}

int get_current_filter();
int8_t filter(fltType*, int8_t, int8_t);


int main() {
	int8_t filter_id;
	int8_t data;
	fltType* flt = flt_create();
	while(1) {
		filter_id = get_current_filter();
		if (uart_getsigned(&data)) {
			if (filter_id != NO_FILTER)
				data = filter(flt, data, filter_id);
		uart_putsigned(data);
		}
	}
	return 0;
}


int saturating_counter(int8_t value, int8_t increment, int8_t min, int8_t max) {
	if (value + increment > max)
		return max;
	else if (value + increment < min)
		return min;
	else
		return value + increment;
}

int get_current_filter() {
	// filter_id >= 0 means that some filter 0 to 3 is enabled
	// filter_id == -1 means filter is disabled
	// the program starts with filter disabled
	static int8_t filter_id = -1;
	if (btn_single_pulse(BTN0)){
		led_off(filter_id);
		filter_id = saturating_counter(filter_id, 1, -1, 3);
		led_on(filter_id);
	} else if (btn_single_pulse(BTN1)) {
		led_off(filter_id);
		filter_id = saturating_counter(filter_id, -1, -1, 3);
		led_on(filter_id);
	}
	return filter_id;
}

int8_t filter(fltType* filterObject, int8_t input, int8_t filter_id) {
		float float_val = ((float) input) /128.0f;
			// select_filter just chooses the correct index of an array
			// to use one of 4 filter coefficient tables
		flt_writeInput(filterObject, float_val, select_filter(filter_id));
		float_val = flt_readOutput(filterObject);
		input = (int8_t) (float_val* 128.0f);
		return input;
}
