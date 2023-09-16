/*
 * uart.h
 *
 *  Created on: Sep 16, 2023
 *      Author: franc
 */

#ifndef USER_PER_UART_H_
#define USER_PER_UART_H_

#include <stdint.h>

extern void uart1_init(void);
extern uint16_t uart1_get_rx_idx(void);
extern void uart1_send(uint8_t* tx_buf, uint16_t length);
extern void uart1_clear(void);

#endif /* USER_PER_UART_H_ */
