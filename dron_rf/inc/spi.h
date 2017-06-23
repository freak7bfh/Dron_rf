/*
 * spi.h
 *
 *  Created on: May 25, 2017
 *      Author: Jarek
 */

#ifndef SPI_H_
#define SPI_H_

void SPIInit();
void SPI_SendData(uint8_t address, uint8_t data);
uint8_t SPI_ReceiveData(uint8_t address);
//void SPI_SendFrame(uint8_t *data, uint8_t frame_len);

#endif /* SPI_H_ */
