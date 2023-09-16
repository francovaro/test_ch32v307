/*
 * led.h
 *
 *  Created on: Sep 16, 2023
 *      Author: franc
 */

#ifndef USER_PER_LED_H_
#define USER_PER_LED_H_

#include <stdbool.h>

typedef enum {
	e_red,
	e_blue,
	e_green,
	e_max
}t_led;

extern void led_init(void);
extern void led_set(t_led led, bool turn_on);

#endif /* USER_PER_LED_H_ */
