/*
 * fifo.c
 *
 *  Created on: Oct 11, 2021
 *      Author: jerem
 */

#include <stdlib.h>
#include <string.h>

#include "fifo.h"
#include "asm.h"

bool FIFO_Init(FIFO_Data_Typedef* inStruct, uint8_t* inBuffer, uint16_t inBufferSize)
{
	if (inStruct == NULL || inBuffer == NULL)
	{
		return false;
	}

	inStruct->buffer = inBuffer;
	inStruct->headPos = 0;
	inStruct->tailPos = 0;
	inStruct->overrun = 0;
	inStruct->size = inBufferSize;
	inStruct->free = inBufferSize;

	return true;
}

bool FIFO_Write(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Length)
{
	if (inStruct->free < Length)
	{
		inStruct->overrun++;
		return false;
	}

	for (uint16_t i = 0; i < Length; i++)
	{
		inStruct->buffer[inStruct->headPos] = Buffer[i];
		inStruct->headPos++;

		if (inStruct->headPos >= inStruct->size)
		{
			inStruct->headPos = 0;
		}
	}

	inStruct->free -= Length;

//	uint16_t workFree;
//	do {
//		workFree = LDREXH(&inStruct->free);
//		workFree -= Length;
//	} while (STREXH(workFree, &inStruct->free));

	return true;
}

uint16_t FIFO_Read(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_WriteAvailable(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	uint16_t bytesRead = 0;
	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[inStruct->tailPos];
		inStruct->tailPos++;

		if (inStruct->tailPos >= inStruct->size)
		{
			inStruct->tailPos = 0;
		}

		bytesRead++;
	}

	inStruct->free += bytesRead;

//	uint16_t workFree;
//	do {
//		workFree = LDREXH(&inStruct->free);
//		workFree += bytesAvailable;
//	} while (STREXH(workFree, &inStruct->free));

	return bytesRead;
}

void FIFO_Flush(FIFO_Data_Typedef* inStruct)
{
	//memset(inStruct->buffer, 0, inStruct->size);

	//inStruct->headPos = 0;
	//inStruct->tailPos = 0;
	//inStruct->overrun = 0;
	//inStruct->free = inStruct->size;
}

uint16_t FIFO_Peek(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_ReadAvailable(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	uint16_t bytesPeeked = 0;
	uint16_t tempTailPos = inStruct->tailPos;
	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[tempTailPos];
		tempTailPos++;

		if (tempTailPos == inStruct->size)
		{
			tempTailPos = 0;
		}

		bytesPeeked++;
	}

	return bytesPeeked;
}

uint16_t FIFO_ReadAvailable(FIFO_Data_Typedef* inStruct)
{
	return inStruct->size - inStruct->free;
}

uint16_t FIFO_WriteAvailable(FIFO_Data_Typedef* inStruct)
{
	return inStruct->free;
}
