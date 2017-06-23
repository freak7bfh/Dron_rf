/*
 * usart.c
 *
 *  Created on: 23-02-2015
 *      Author: Jarek
 */

#include "stm32f10x.h"
#include "string.h"


void USARTInit(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// piny							tx
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// piny							rx
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// usart
	USART_InitStructure.USART_BaudRate 			  = 57600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode				  = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity			  = USART_Parity_No;
	USART_InitStructure.USART_StopBits			  = USART_StopBits_1;
	USART_InitStructure.USART_WordLength		  = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);

	// NVIC dla USART
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	NVIC_InitTypeDef NVIC_UART1_InitStructure;
	NVIC_UART1_InitStructure.NVIC_IRQChannel 					= USART1_IRQn;
	NVIC_UART1_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;
	NVIC_UART1_InitStructure.NVIC_IRQChannelSubPriority 		= 0;
	NVIC_UART1_InitStructure.NVIC_IRQChannelCmd 				= ENABLE;
	NVIC_Init(&NVIC_UART1_InitStructure);



	NVIC_EnableIRQ(USART1_IRQn);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}

void USARTSendNow(char *s){
	uint16_t len = strlen(s);
	for (uint16_t i = 0; i < len; i++){
		while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		USART_SendData(USART1, s[i]);
	}
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC));
}

void USARTSendFrame(uint8_t *frame, uint16_t frame_len){
	for (uint16_t i = 0; i < frame_len; i++){
		while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		USART_SendData(USART1, frame[i]);
	}
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC));
}

