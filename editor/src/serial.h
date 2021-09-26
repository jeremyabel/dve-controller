#pragma once

#include <stdint.h>

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

struct SerialConfiguration
{
	const char* Port = "";
	uint32_t BaudRate = 9600;
	uint8_t ByteSize = 8;
	SerialParity Parity = SerialParity_None;
	SerialStopBits StopBits = SerialStopBits_1;
	SerialFlowControl FlowControl = SerialFlowControl_None;
	
	SerialConfiguration() {}
	SerialConfiguration(const char* inPort,
		uint32_t inBaudRate = 9600,
		uint8_t inByteSize = 8,
		SerialParity inParity = SerialParity_None,
		SerialStopBits inStopBits = SerialStopBits_1,
		SerialFlowControl inFlowControl = SerialFlowControl_None)
		: Port(inPort)
		, BaudRate(inBaudRate)
		, Parity(inParity)
		, StopBits(inStopBits)
		, FlowControl(inFlowControl)
	{}
};

class Serial 
{
public:

	Serial() : IsOpen(false) {}
	Serial(const SerialConfiguration config);

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

	SerialConfiguration Config;

private:

	bool IsOpen;

#if _WIN32
	void* FileHandle;
#elif __APPLE__
	int FileHandle;
#endif

};
