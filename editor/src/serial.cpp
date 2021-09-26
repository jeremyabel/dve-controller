#include <algorithm>

#include "serial.h"

#ifdef _WIN32
#include "serial_win.h"
#elif __APPLE__
#include "serial_macos.h"
#endif

class Serial::ScopedReadLock
{
public:
	
	ScopedReadLock(SerialImpl* inImpl) : Impl(inImpl) { Impl->ReadLock(); }
	~ScopedReadLock() { Impl->ReadUnlock(); }

private:

	// Disable copy constructors
	// @QUESTION: Why?
	ScopedReadLock(const ScopedReadLock&);
	const ScopedReadLock& operator=(ScopedReadLock);

	SerialImpl* Impl;

};

class Serial::ScopedWriteLock
{
public:

	ScopedWriteLock(SerialImpl* inImpl) : Impl(inImpl) { Impl->WriteLock(); }
	~ScopedWriteLock() { Impl->WriteUnlock(); }

private:

	// Disable copy constructors
	ScopedWriteLock(const ScopedWriteLock&);
	const ScopedWriteLock& operator=(ScopedWriteLock);

	SerialImpl* Impl;

};

Serial::Serial(const std::string &port,
	uint32_t baudRate,
	SerialTimeout timeout,
	uint8_t byteSize,
	SerialParity parity,
	SerialStopBits stopBits,
	SerialFlowControl flowControl)
	: Impl(new SerialImpl(port, baudRate, byteSize, parity, stopBits, flowControl))
{
	Impl->Timeout = timeout;
}

Serial::~Serial()
{
	delete Impl;
}

void Serial::Open()
{
	Impl->Open();
}

void Serial::Close()
{
	Impl->Close();
}

void Serial::Reset()
{
	Impl->Reset();
}

bool Serial::GetIsOpen() const
{
	return Impl->GetIsOpen();
}

size_t Serial::GetAvailableBufferSize()
{
	return Impl->GetAvailableBufferSize();
}

size_t Serial::Read(uint8_t* buffer, size_t size)
{
	ScopedReadLock lock(Impl);
	return Impl->Read(buffer, size);
}

size_t Serial::Write(const uint8_t* data, size_t size)
{
	ScopedWriteLock lock(Impl);
	return Impl->Write(data, size);
}

void Serial::Flush()
{
	ScopedReadLock rLock(Impl);
	ScopedWriteLock wLock(Impl);
	Impl->Flush();
}

void Serial::FlushInput()
{
	ScopedReadLock lock(Impl);
	Impl->FlushInput();
}

void Serial::FlushOutput()
{
	ScopedWriteLock lock(Impl);
	Impl->FlushOutput();
}