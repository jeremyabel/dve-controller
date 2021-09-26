#if __APPLE__

#pragma once

#include "serial.h"
#include <pthread.h>

class Serial::SerialImpl
{
public:

	SerialImpl(const std::string &inPort,
		uint32_t inBaudRate,
		uint8_t inByteSize,
		SerialParity inParity,
		SerialStopBits inStopBits,
		SerialFlowControl inFlowControl);

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

	std::string Port;
	int FileHandle;

	bool IsOpen;

	pthread_mutex_t ReadMutex;
	pthread_mutex_t WriteMutex;
};

#endif