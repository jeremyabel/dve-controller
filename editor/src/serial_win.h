#ifdef _WIN32

#pragma once

#include "serial.h"

#define WIN32_LEAN_AND_MEAN

#include "windows.h"

class Serial::SerialImpl
{
public:

	SerialImpl(const std::string& inPort = "",
		uint32_t inBaudRate = 9600,
		uint8_t inByteSize = 8,
		SerialParity inParity = SerialParity_None,
		SerialStopBits inStopBits = SerialStopBits_1,
		SerialFlowControl inFlowControl = SerialFlowControl_None);

	virtual ~SerialImpl();

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

	void ReadLock();
	void ReadUnlock();
	void WriteLock();
	void WriteUnlock();

	unsigned long     BaudRate;
	SerialTimeout	  Timeout;
	uint8_t           ByteSize;
	SerialParity      Parity;
	SerialStopBits    StopBits;
	SerialFlowControl FlowControl;

private:
	
	std::wstring Port;
	HANDLE FileHandle;

	bool IsOpen;

	HANDLE ReadMutex;
	HANDLE WriteMutex;
};

#endif // ifdef _WIN32