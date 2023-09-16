/*
 * uart.c
 *
 *  Created on: Sep 16, 2023
 *      Author: franc
 */
#include "ch32v30x_conf.h"
#include "uart.h"
#include <string.h>

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

uint8_t rx_bufer[256];
volatile uint16_t rx_cnt;
volatile uint16_t rx_idx;

/**
 *
 */
void uart1_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    // GPIO pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// tx
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	// rx
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART strcut
    USART_InitStructure.USART_BaudRate = (115200u);
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	// NVIC struct
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //NVIC_EnableIRQ(USART1_IRQn);	// needed ??

    memset(rx_bufer, 0, sizeof(rx_bufer));
    rx_idx = 0;
    rx_cnt = 0;

    USART_Cmd(USART1, ENABLE);
}

/**
 *
 */
void uart1_send(uint8_t* tx_buf, uint16_t length)
{
    uint16_t i;

    for(i = 0; i < length; i++) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, *tx_buf++);
    }
}

/**
 *
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    	rx_bufer[rx_idx++] = (uint8_t)(USART1->DATAR & (uint16_t)0xFF);
    }
}

/**
 *
 */
uint16_t uart1_get_rx_idx(void)
{
	return rx_idx;
}

/**
 *
 */
void uart1_clear(void)
{
	rx_idx = 0;
}
