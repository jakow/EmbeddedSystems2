# DSP filtering
Welcome to the manual! This manual explains how the code works and is laid out.

## Main
The `main.c` contains the `__init_hardware()` procedure that runs on reset and the following:
1. Initialise the Floating Point Unit
2. Initialise the LED driver
3. Initialise the button driver
4. Initialise the driver
5. Enable button interrupts.

The `main` of the file creates a filter and then enters a loop which polls for new UART data. `uart_getsigned(&data)` puts data into `data` buffer and returns `true` only if there was some data present in the buffer. If a filter is selected, the data is filtered and then the value is sent back with `uart_putsigned(&data)`.


## Buttons

To use buttons, a few things had to be done. First of all, the clock gates to the button GPIO ports must be enabled. This is done by writing to `SIM_SCGC5` mask. According to docs (K70 manual page 219), this has to be done before any code that enables the gated chip functions.

Then we configure button pins as GPIOs, by changing the value of Port Control Register (PCR) multiplexer bits (`PORT_PCR_MUX`). According to the Freescale Tower manual, button 0 is pin 0 on PORTD, and button 1 is pin 26 on PORTE.   

Finally, to set the GPIO pin direction as input, we clear the corresponding flag in PDDR (pin data direction register) of PORTD and PORTE.
### Button interrupts
Button interrupts are used to toggle between filters, as opposed to polling. The buttons are configured to fire interrupts when buttons are released after being pressed. Because the buttons are *active low*, this happens on the *rising edge* on the pin.

To enable button interrupts, the following steps are taken. First, the appropriate index into the NVIC table is calculated using macros. According to K70 Manual, the index is essentially `floor(IRQ / 32)` where `IRQ` is the interrupt source number taken from Table 3-4 of the manual. For PORTD and PORTE this is NVIC2. Then the appropriate bit positions (`BTN*_NVIC_BIT`) in the vector are also calculated. To enable interrupts, write set the bit flag in the Interrupt Set Enable Register (ISER) of the particular NVIC index.

Lastly, to configure interrupt behaviour of the pin, Port Control Registers (PCR) of PORTD and PORTE must be updated. The IRQC field of PCR dictates what event triggers the interrupt. In this case, it is the rising edge, which is mapped to value of `b1001` (or `0x9`) in the IRQC.


### Button API
`BTN0` is the *up* button, `BTN1` is the *down* button. Pass the button IDs to functions below.

`int btn_get(int btn_id)` get the current state of the button. 1 if button is pressed, if button released

`int btn_single_pulse(int btn_id)` a stateful function that can be used for polling for button state. When called repeatedly, it will output 1 whenever there was a falling edge detected.

## UART
The UART module


### UART API

`uart_getsigned(int8_t* num)` and `uart_putsigned(int8_t* num)` are the functions actually used in the code for receiving and sending signed characters. Signed integers are used instead of chars because the tests performed have shown that a plain `char` is unsigned by default, and tricky conversions are avoided this way.

The other functions were used for debugging. `uart_getchar(char* ch)` and `uart_putchar(char* ch)` allow to read and write individual characters from the serial port, and `uart_read`, `uart_write`, and `uart_write_n` can be used to read and write null-terminated strings.

## FPU
For power considerations, ARM Cortex M4 disables floating point by default, so we enable coprocessors 10 and 11 which support the ARMv7-M Floating Point extension

## DSP

The filter taken from Micromodeler DSP app has been changed slightly. Because the filters are all 4<sup>th</sup>-order IIR filters, the algorithm is always the same, only the coefficients change. For this reason, the `flt_filterBlock` function was modified to include a `flt_coefficients` parameter which points to the array of filter coefficients. This way, the type of filter can be changed by passing a different coefficient table to the `flt_filterBlock` function.
