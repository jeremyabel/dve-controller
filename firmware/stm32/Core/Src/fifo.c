/*
 * fifo.c
 *
 *  Created on: Oct 11, 2021
 *      Author: jerem
 */

#include <stdlib.h>
#include <string.h>

#include "fifo.h"

bool FIFO_Init(FIFO_Data_Typedef* inStruct, uint8_t* inBuffer, uint16_t inBufferSize)
{
	if (inStruct == NULL || inBuffer == NULL)
	{
		return false;
	}

	inStruct->buffer = inBuffer;
	inStruct->headPos = 0;
	inStruct->tailPos = 0;
	inStruct->size = inBufferSize;

	return true;
}

bool FIFO_Write(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint32_t* Length)
{
	uint16_t len = (uint16_t)*Length;
	uint16_t tempHeadPos = inStruct->headPos;

	for (uint16_t i = 0; i < len; i++)
	{
		inStruct->buffer[tempHeadPos] = Buffer[i];

		// Increment position
		tempHeadPos++;
		if (tempHeadPos == inStruct->size)
		{
			tempHeadPos = 0;
		}

		if (tempHeadPos == inStruct->tailPos)
		{
			return false;
		}
	}

	inStruct->headPos = tempHeadPos;

	return true;
}

void FIFO_Read(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_Available(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[inStruct->tailPos];

		inStruct->tailPos++;
		if (inStruct->tailPos == inStruct->size)
		{
			inStruct->tailPos = 0;
		}
	}
}

void FIFO_Flush(FIFO_Data_Typedef* inStruct)
{
	memset(inStruct->buffer, 0, inStruct->size);

	inStruct->headPos = 0;
	inStruct->tailPos = 0;
}

void FIFO_Peek(FIFO_Data_Typedef* inStruct, uint8_t* Buffer, uint16_t Max)
{
	uint16_t bytesAvailable = FIFO_Available(inStruct);

	if (bytesAvailable > Max)
	{
		bytesAvailable = Max;
	}

	for (uint16_t i = 0; i < bytesAvailable; i++)
	{
		Buffer[i] = inStruct->buffer[inStruct->tailPos];
	}
}

uint16_t FIFO_Available(FIFO_Data_Typedef* inStruct)
{
	return (uint16_t)(inStruct->headPos - inStruct->tailPos) % inStruct->size;
}
