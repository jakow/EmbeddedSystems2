/*
 * button.h
 *
 *  Created on: 10 Mar 2017
 *      Author: s1243303
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#define BTN_UP 0
#define BTN_DOWN 1


#define BTN0 0
#define BTN1 1

#define BIT_BTN0	(1 << 0)
#define BIT_BTN1	(1 << 26)

extern void btn_init();
extern int btn_get(int btn_id);
extern int btn_single_pulse(int btn_id);

#endif /* SRC_BUTTON_H_ */
