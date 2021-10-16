/*
 * fifo.h
 *
 *  Created on: Oct 11, 2021
 *      Author: jerem
 */

#ifndef INC_FIFO_H_
#define INC_FIFO_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint8_t* buffer;
	uint16_t headPos;
	uint16_t tailPos;
	uint16_t size;
	uint16_t free;
	uint32_t overrun;
} FIFO_Data_Typedef;

bool FIFO_Init(FIFO_Data_Typedef* inStruct, uint8_t* inBuffer, uint16_t inBufferSize);
bool FIFO_Write(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Length);
void FIFO_Flush(FIFO_Data_Typedef* inStruct);
uint16_t FIFO_Peek(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max);
uint16_t FIFO_Read(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max);
uint16_t FIFO_ReadAvailable(FIFO_Data_Typedef* inStruct);
uint16_t FIFO_WriteAvailable(FIFO_Data_Typedef* inStruct);

#endif /* INC_FIFO_H_ */
