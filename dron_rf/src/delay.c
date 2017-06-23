/*

 * delay.c
 *
 *  Created on: 23-02-2015
 *      Author: Jarek
 */

#include "stm32f10x.h"
#include "delay.h"


void DelayInit(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_TimeBaseInitTypeDef TIM4_InitStruct;
	TIM_TimeBaseStructInit(&TIM4_InitStruct);

	TIM4_InitStruct.TIM_ClockDivision		= TIM_CKD_DIV1;
	TIM4_InitStruct.TIM_CounterMode			= TIM_CounterMode_Up;
	TIM4_InitStruct.TIM_Period				= 0xffff;
	TIM4_InitStruct.TIM_Prescaler			= SYS_CLOCK-1;
	TIM4_InitStruct.TIM_RepetitionCounter	= 0x0000;

	TIM_TimeBaseInit(TIM4, &TIM4_InitStruct);

	TIM_Cmd(TIM4,ENABLE);

//	USARTSendNow("DelayInit...\n\r");
}


void Delay_us(uint16_t us) {
	TIM4->CNT = 0;
	while((uint16_t)(TIM4->CNT) <= us);
}

void Delay_ms(uint16_t ms) {
	int i;
	for (i=0; i < ms; i++){
		Delay_us(1000);
	}
}
