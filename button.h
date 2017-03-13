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
//#define BTN2 2
//#define BTN3 3
//#define BTN4 4
//#define BTN5 5

//#define BIT_BTN0 	(1 << 4)
//#define BIT_BTN1	(1 << 3)
//#define BIT_BTN2	(1 << 2)
//#define BIT_BTN3	(1 << 16)
#define BIT_BTN0	(1 << 0)
#define BIT_BTN1	(1 << 26)

extern void btn_init();
extern int btn_get(int btn_id);

#endif /* SRC_BUTTON_H_ */
