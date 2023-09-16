/*
 * uart.c
 *
 *  Created on: Sep 16, 2023
 *      Author: franc
 */

#include "debug.h"
#include "per/led.h"
#include "per/uart.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	SystemCoreClockUpdate();
	Delay_Init();

	uart1_init();

	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

	led_set(0, 1);

	while(1) {
		if (uart1_get_rx_idx() != 0) {
			printf("Received\r\n");
			uart1_clear();
		}
	}
}

