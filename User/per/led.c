/*
 * led.c
 *
 *  Created on: Sep 16, 2023
 *      Author: franc
 */

#include "ch32v30x_conf.h"
#include "led.h"

/**
 *
 */
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 *
 */
void led_set(t_led led, bool turn_on)
{

}
