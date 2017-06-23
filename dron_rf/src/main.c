/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "delay.h"
#include "spi.h"
#include "usart.h"

__IO uint8_t RxBufRS[RS_BUFF];
__IO uint8_t RxIndeksRS=0x00;

int main(){

	SystemInit();
	DelayInit();
	SPIInit();
	USARTInit();

	// led
	GPIO_InitTypeDef LEDS_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	LEDS_InitStruct.GPIO_Pin	= GPIO_Pin_13;
	LEDS_InitStruct.GPIO_Mode	= GPIO_Mode_Out_PP;
	LEDS_InitStruct.GPIO_Speed	= GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&LEDS_InitStruct);

	GPIOC->BSRR=GPIO_Pin_13;

	uint16_t h=0x00;

	while(1){
		_printfn("0x%04x",h++);
		GPIOC->ODR^=GPIO_Pin_13;
		Delay_ms(500);
//		GPIOC->ODR^=GPIO_Pin_13;
//		Delay_ms(800);

	}

	return 0;
}


void USART1_IRQHandler(){
	if(USART_GetITStatus(USART1, USART_IT_RXNE)){
		RxBufRS[RxIndeksRS++]=USART_ReceiveData(USART1);

		if(RxBufRS[0]=='+'){
			_putsn("received...");
			RxIndeksRS=0;
			RxBufRS[0]=0;
		}
		else{
			RxIndeksRS=0;
			for(uint8_t i=0; i<RS_BUFF; i++) RxBufRS[i]=0;
		}



		if(RxIndeksRS>=RS_BUFF){
			RxIndeksRS=0;
			for(uint8_t i=0; i<RS_BUFF; i++) RxBufRS[i]=0;
		}
	}
	USART_ClearFlag(USART1, USART_IT_RXNE);
}
