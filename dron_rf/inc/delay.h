/*
 * delay.h
 *
 *  Created on: 23-02-2015
 *      Author: Jarek
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "stm32f10x.h"

#define SYS_CLOCK 72

void DelayInit();
void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);

#endif /* DELAY_H_ */
