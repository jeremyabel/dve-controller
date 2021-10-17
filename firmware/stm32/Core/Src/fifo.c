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

	return true;
}

void FIFO_Read(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_WriteAvailable(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[inStruct->tailPos];
		inStruct->tailPos++;

		if (inStruct->tailPos >= inStruct->size)
		{
			inStruct->tailPos = 0;
		}
	}

	inStruct->free += bytesAvailable;
}

void FIFO_Flush(FIFO_Data_Typedef* inStruct)
{
	memset(inStruct->buffer, 0, inStruct->size);

	inStruct->headPos = 0;
	inStruct->tailPos = 0;
	inStruct->overrun = 0;
	inStruct->free = inStruct->size;
}

void FIFO_Peek(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_ReadAvailable(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	uint16_t tempTailPos = inStruct->tailPos;
	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[tempTailPos];
		tempTailPos++;

		if (tempTailPos == inStruct->size)
		{
			tempTailPos = 0;
		}
	}
}

uint16_t FIFO_ReadAvailable(FIFO_Data_Typedef* inStruct)
{
	return inStruct->size - inStruct->free;
}

uint16_t FIFO_WriteAvailable(FIFO_Data_Typedef* inStruct)
{
	return inStruct->free;
}
