#include <limits>

#include "serial.h"

Serial::Serial(const SerialConfiguration inConfig)
	: Config(inConfig)
	, IsOpen(false)
{}

Serial::~Serial()
{
	Close();
}

void Serial::Open()
{
#if _WIN32
	FileHandle = CreateFileA(Config.Port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif

	Reset();
	IsOpen = true;
}

void Serial::Close()
{
	if (IsOpen)
	{
#if _WIN32
		CloseHandle(FileHandle);
		FileHandle = INVALID_HANDLE_VALUE;
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif

		IsOpen = false;
	}
}

void Serial::Reset()
{
#if _WIN32
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	// Setup baud rate
	dcbSerialParams.BaudRate = Config.BaudRate;

	// Setup stop bits
	switch (Config.StopBits)
	{
		case SerialStopBits_1:   dcbSerialParams.StopBits = ONESTOPBIT; break;
		case SerialStopBits_2:   dcbSerialParams.StopBits = TWOSTOPBITS; break;
		case SerialStopBits_1_5: dcbSerialParams.StopBits = ONE5STOPBITS; break;
	}

	// Setup parity
	switch (Config.Parity)
	{
		case SerialParity_None: dcbSerialParams.Parity = NOPARITY; break;
		case SerialParity_Even: dcbSerialParams.Parity = EVENPARITY; break;
		case SerialParity_Odd:  dcbSerialParams.Parity = ODDPARITY; break;
	}

	// Setup flow control
	if (Config.FlowControl == SerialFlowControl_None)
	{
		dcbSerialParams.fOutxCtsFlow = false;
		dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
		dcbSerialParams.fOutX = false;
		dcbSerialParams.fInX = false;
	}
	else if (Config.FlowControl == SerialFlowControl_Software)
	{
		dcbSerialParams.fOutxCtsFlow = false;
		dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
		dcbSerialParams.fOutX = true;
		dcbSerialParams.fInX = true;
	}
	else if (Config.FlowControl == SerialFlowControl_Hardware)
	{
		dcbSerialParams.fOutxCtsFlow = true;
		dcbSerialParams.fRtsControl = RTS_CONTROL_HANDSHAKE;
		dcbSerialParams.fOutX = false;
		dcbSerialParams.fInX = false;
	}

	// Setup timeouts
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = std::numeric_limits<uint32_t>::max();
	timeouts.ReadTotalTimeoutConstant = 1000;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 1000;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	// Activate timeouts
	SetCommTimeouts(FileHandle, &timeouts);

	// Activate settings
	SetCommState(FileHandle, &dcbSerialParams);
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif
}

size_t Serial::GetAvailableBufferSize()
{
#if _WIN32
	COMSTAT commStats;
	ClearCommError(FileHandle, NULL, &commStats);
	return static_cast<size_t>(commStats.cbInQue);
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif
}

size_t Serial::Read(uint8_t* buffer, size_t size)
{
#if _WIN32
	DWORD bytesRead;
	ReadFile(FileHandle, buffer, static_cast<DWORD>(size), &bytesRead, NULL);
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif

	return (size_t)bytesRead;
}

size_t Serial::Write(const uint8_t* data, size_t size)
{
#if _WIN32
	DWORD bytesWritten;
	WriteFile(FileHandle, data, static_cast<DWORD>(size), &bytesWritten, NULL);
#elif __APPLE__
#error "Apple platforms not implemented yet"
#endif

	return (size_t)bytesWritten;
}

void Serial::Flush()
{
#if _WIN32
	FlushFileBuffers(FileHandle);
#elif __APPLE__
	tcdrain(FileHandle);
#endif
}

void Serial::FlushInput()
{
#if _WIN32
	PurgeComm(FileHandle, PURGE_RXCLEAR);
#elif __APPLE__
	tcflush(FileHandle, TCIFLUSH);
#endif
}

void Serial::FlushOutput()
{
#if _WIN32
	PurgeComm(FileHandle, PURGE_TXCLEAR);
#elif __APPLE__
	tcflush(FileHandle, TCOFLUSH);
#endif
}