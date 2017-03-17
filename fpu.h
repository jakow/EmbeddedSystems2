/*
 * uart.h
 *
 *  Created on: 15 Mar 2017
 *      Author: s1690540
 */

 #ifndef FPU_H_
 #define FPU_H_

 #include "MK70F12.h"

 //init FPU - coprocessor enable flags
 inline void fpu_init() {
   SCB_CPACR |= SCB_CPACR_CP10_MASK | SCB_CPACR_CP11_MASK;
 }

 #endif
