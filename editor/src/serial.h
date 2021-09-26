#pragma once

#include <stdint.h>

#if _WIN32
#define NOMINMAX
#include "windows.h" // @TODO: Optimize this from Aras's article
#endif

enum SerialStopBits
{
	SerialStopBits_1 = 1,
	SerialStopBits_2 = 2,
	SerialStopBits_1_5
};

enum SerialParity
{
	SerialParity_None = 0,
	SerialParity_Odd  = 1,
	SerialParity_Even = 2
};

enum SerialFlowControl
{
	SerialFlowControl_None = 0,
	SerialFlowControl_Software,
	SerialFlowControl_Hardware
};

class Serial 
{
public:

	Serial(const char* port = "",
		uint32_t baudRate = 9600,
		uint8_t byteSize = 8,
		SerialParity parity = SerialParity_None,
		SerialStopBits stopBits = SerialStopBits_1,
		SerialFlowControl flowControl = SerialFlowControl_None);

	virtual ~Serial();

	void Open();
	void Close();
	void Reset();

	bool GetIsOpen() const { return IsOpen; }
	size_t GetAvailableBufferSize();

	size_t Read(uint8_t* buffer, size_t size);
	size_t Write(const uint8_t* data, size_t size);

	void Flush();
	void FlushInput();
	void FlushOutput();

	unsigned long     BaudRate;
	uint8_t           ByteSize;
	SerialParity      Parity;
	SerialStopBits    StopBits;
	SerialFlowControl FlowControl;

private:

	const char* Port;
	bool IsOpen;

#if _WIN32
	HANDLE FileHandle;
#elif __APPLE__
	int FileHandle;
#endif

};
