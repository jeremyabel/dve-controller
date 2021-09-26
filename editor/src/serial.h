#pragma once

#include <limits>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <exception>
#include <stdexcept>
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

struct SerialTimeout
{
// @QUESTION: This looks gross? Is it?
#ifdef max
#undef max
#endif
	static uint32_t max() { return std::numeric_limits<uint32_t>::max(); }

	static SerialTimeout simpleTimeout(uint32_t timeout)
	{
		return SerialTimeout(SerialTimeout::max(), timeout, 0, timeout, 0);
	}

	uint32_t interByteTimeout;
	uint32_t readTimeoutConstant;
	uint32_t readTimeoutMultiplier;
	uint32_t writeTimeoutConstant;
	uint32_t writeTimeoutMultiplier;

	explicit SerialTimeout(uint32_t inInterByteTimeout = 0,
		uint32_t inReadTimeoutConstant = 0,
		uint32_t inReadTimeoutMultiplier = 0,
		uint32_t inWriteTimeoutConstant = 0,
		uint32_t inWriteConstantMultiplier = 0)
		: interByteTimeout(inInterByteTimeout)
		, readTimeoutConstant(inReadTimeoutConstant)
		, readTimeoutMultiplier(inReadTimeoutMultiplier)
		, writeTimeoutConstant(inWriteTimeoutConstant)
		, writeTimeoutMultiplier(inWriteConstantMultiplier)
	{}
};

class Serial 
{
public:

	Serial(const std::string& port = "",
		uint32_t baudRate = 9600,
		SerialTimeout timeout = SerialTimeout(),
		uint8_t byteSize = 8,
		SerialParity parity = SerialParity_None,
		SerialStopBits stopBits = SerialStopBits_1,
		SerialFlowControl flowControl = SerialFlowControl_None);

	virtual ~Serial();

	void Open();
	void Close();
	void Reset();

	bool GetIsOpen() const;
	size_t GetAvailableBufferSize();

	size_t Read(uint8_t* buffer, size_t size);
	size_t Write(const uint8_t* data, size_t size);

	void Flush();
	void FlushInput();
	void FlushOutput();

private:

	class SerialImpl;
	SerialImpl* Impl;

	class ScopedReadLock;
	class ScopedWriteLock;
};
