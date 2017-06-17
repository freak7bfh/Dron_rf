/*
 * rcc.c
 *
 *  Created on: 04-03-2015
 *      Author: Jarek
 */
#include "stm32f0xx_conf.h"


void RCCInit(){
	 	// Wyzerowanie poprzednich ustawie� RCC
	 	RCC_DeInit();

	 	ErrorStatus HSEStartUpStatus;

	 	// W��czenie HSE
	 	RCC_HSEConfig(RCC_HSE_ON);

	 	// Czekaj, a� HSE sie uruchomi lub zostanie przekroczony dozwolony czas
	 	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	 	if (HSEStartUpStatus == SUCCESS){
			// W��czenie op�nie� dla FLASH
			FLASH_SetLatency(FLASH_Latency_1);
			FLASH_PrefetchBufferCmd(ENABLE);

			// AHB
			RCC_HCLKConfig(RCC_SYSCLK_Div1);

			// APB1
			RCC_PCLKConfig(RCC_HCLK_Div1);

			// PLL
			RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);

			// W��czenie PLL
			RCC_PLLCmd(ENABLE);

			// Oczekiwanie na gotowo�� PLL
			while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {
			}

			// Wyb�r PLL na zegar systemowy
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

			// Oczekiwanie na wyb�r zegara systemowego
			while (RCC_GetSYSCLKSource() != 0x08) {
			}
		}
}
