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
Hello world!

### Button interrupts
Hello world!

## UART
Hello world!

## FPU
Hello world!

## DSP

The filter taken from Micromodeler DSP app has been changed slightly. Because the filters are all 4<sup>th</sup>-order IIR filters, the algorithm is always the same, only the coefficients change. For this reason, the `flt_filterBlock` function was modified to include a `flt_coefficients` parameter which points to the array of filter coefficients. This way, the type of filter can be changed by passing a different coefficient table to the `flt_filterBlock` function.
