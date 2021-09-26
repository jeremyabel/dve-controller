#ifdef _WIN32

#include <sstream>

#include "serial_win.h"

Serial::SerialImpl::SerialImpl(const std::string& inPort, 
	uint32_t inBaudRate, 
	uint8_t inByteSize, 
	SerialParity inParity, 
	SerialStopBits inStopBits, 
	SerialFlowControl inFlowControl)
	: Port(inPort.begin(), inPort.end())
	, FileHandle(INVALID_HANDLE_VALUE)
	, IsOpen(false)
	, BaudRate(inBaudRate)
	, Parity(inParity)
	, ByteSize(inByteSize)
	, StopBits(inStopBits)
	, FlowControl(inFlowControl)
{
	ReadMutex  = CreateMutex(NULL, false, NULL);
	WriteMutex = CreateMutex(NULL, false, NULL);
}

Serial::SerialImpl::~SerialImpl()
{
	Close();
	CloseHandle(ReadMutex);
	CloseHandle(WriteMutex);
}

void Serial::SerialImpl::Open()
{
	if (Port.empty()) 
	{
		throw std::invalid_argument("Empty port is invalid.");
	}

	if (IsOpen) 
	{
		throw std::runtime_error("Port is already open.");
	}

	FileHandle = CreateFileW(Port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		std::string portString = std::string(Port.begin(), Port.end());

		DWORD createFileError = GetLastError();
		switch (createFileError)
		{
			case ERROR_FILE_NOT_FOUND: 
				throw std::runtime_error("Specified port " + portString + " does not exist.");
			default: 
				throw std::runtime_error("Unknown error opening port " + portString);
		}
	}

	Reset();
	IsOpen = true;
}

void Serial::SerialImpl::Reset()
{
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Invalid file descriptor. Is the serial port open?");
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(FileHandle, &dcbSerialParams))
	{
		throw std::runtime_error("Error getting the serial port state.");
	}

	// Setup baud rate
	switch (BaudRate)
	{
#ifdef CBR_9600
		case 9600: dcbSerialParams.BaudRate = CBR_9600; break;
#endif
#ifdef CBR_14400
		case 14400: dcbSerialParams.BaudRate = CBR_14400; break;
#endif
#ifdef CBR_19200
		case 19200: dcbSerialParams.BaudRate = CBR_19200; break;
#endif
#ifdef CBR_38400
		case 38400: dcbSerialParams.BaudRate = CBR_38400; break;
#endif
#ifdef CBR_57600
		case 57600: dcbSerialParams.BaudRate = CBR_57600; break;
#endif
#ifdef CBR_115200
		case 115200: dcbSerialParams.BaudRate = CBR_115200; break;
#endif
#ifdef CBR_128000
		case 128000: dcbSerialParams.BaudRate = CBR_128000; break;
#endif
#ifdef CBR_256000
		case 256000: dcbSerialParams.BaudRate = CBR_256000; break;
#endif
		default: dcbSerialParams.BaudRate = BaudRate;
	}

	// Setup byte size
	if (ByteSize >= 5 && ByteSize <= 8) {
		dcbSerialParams.ByteSize = ByteSize;
	} else {
		throw std::invalid_argument("Invalid byte size");
	}
	
	// Setup stop bits
	switch (StopBits)
	{
		case SerialStopBits_1:   dcbSerialParams.StopBits = ONESTOPBIT; break;
		case SerialStopBits_2:   dcbSerialParams.StopBits = TWOSTOPBITS; break;
		case SerialStopBits_1_5: dcbSerialParams.StopBits = ONE5STOPBITS; break;
		default:
			throw std::invalid_argument("Invalid stop bit");
	}

	// Setup parity
	switch (Parity)
	{
		case SerialParity_None: dcbSerialParams.Parity = NOPARITY; break;
		case SerialParity_Even: dcbSerialParams.Parity = EVENPARITY; break;
		case SerialParity_Odd:  dcbSerialParams.Parity = ODDPARITY; break;
		default:
			throw std::invalid_argument("Invalid parity");
	}

	// Setup flow control
	if (FlowControl == SerialFlowControl_None) 
	{
		dcbSerialParams.fOutxCtsFlow = false;
		dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
		dcbSerialParams.fOutX = false;
		dcbSerialParams.fInX = false;
	}
	else if (FlowControl == SerialFlowControl_Software) 
	{
		dcbSerialParams.fOutxCtsFlow = false;
		dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
		dcbSerialParams.fOutX = true;
		dcbSerialParams.fInX = true;
	}
	else if (FlowControl == SerialFlowControl_Hardware)
	{
		dcbSerialParams.fOutxCtsFlow = true;
		dcbSerialParams.fRtsControl = RTS_CONTROL_HANDSHAKE;
		dcbSerialParams.fOutX = false;
		dcbSerialParams.fInX = false;
	}

	// Activate settings
	if (!SetCommState(FileHandle, &dcbSerialParams))
	{
		CloseHandle(FileHandle);
		throw std::runtime_error("Error setting serial port settings.");
	}

	// Setup timeouts
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout         = Timeout.interByteTimeout;
	timeouts.ReadTotalTimeoutConstant    = Timeout.readTimeoutConstant;
	timeouts.ReadTotalTimeoutMultiplier  = Timeout.readTimeoutMultiplier;
	timeouts.WriteTotalTimeoutConstant   = Timeout.writeTimeoutConstant;
	timeouts.WriteTotalTimeoutMultiplier = Timeout.writeTimeoutMultiplier;
	
	// Activate timeouts
	if (!SetCommTimeouts(FileHandle, &timeouts)) 
	{
		throw std::runtime_error("Error setting timeouts.");
	}
}

void Serial::SerialImpl::Close()
{
	if (IsOpen)
	{
		if (FileHandle != INVALID_HANDLE_VALUE)
		{
			int result = CloseHandle(FileHandle);
			if (result == 0) {
				throw std::runtime_error("Error closing serial port.");
			} else {
				FileHandle = INVALID_HANDLE_VALUE;
			}
		}

		IsOpen = false;
	}
}

size_t Serial::SerialImpl::GetAvailableBufferSize()
{
	if (!IsOpen)
	{
		return 0;
	}

	COMSTAT cs;
	if (!ClearCommError(FileHandle, NULL, &cs))
	{
		throw std::runtime_error("Error while checking the status of the serial port.");
	}

	return static_cast<size_t>(cs.cbInQue);
}

size_t Serial::SerialImpl::Read(uint8_t* buffer, size_t size)
{
	if (!IsOpen) 
	{
		throw std::runtime_error("Cannot read, port is not open.");
	}
	
	DWORD bytesRead;
	if (!ReadFile(FileHandle, buffer, static_cast<DWORD>(size), &bytesRead, NULL)) 
	{
		throw std::runtime_error("Error while reading from the serial port.");
	}
	
	return (size_t)bytesRead;
}

size_t Serial::SerialImpl::Write(const uint8_t* data, size_t size)
{
	if (!IsOpen) 
	{
		throw std::runtime_error("Cannot write, port is not open.");
	}

	DWORD bytesWritten;
	if (!WriteFile(FileHandle, data, static_cast<DWORD>(size), &bytesWritten, NULL)) 
	{
		throw std::runtime_error("Error while writing to the serial port.");
	}

	return (size_t)bytesWritten;
}

void Serial::SerialImpl::Flush()
{
	if (!IsOpen) 
	{
		throw std::runtime_error("Cannot flush, port is not open.");
	}

	FlushFileBuffers(FileHandle);
}

void Serial::SerialImpl::FlushInput()
{
	if (!IsOpen) 
	{
		throw std::runtime_error("Cannot flush input, port is not open.");
	}

	PurgeComm(FileHandle, PURGE_RXCLEAR);
}

void Serial::SerialImpl::FlushOutput()
{
	if (!IsOpen) 
	{
		throw std::runtime_error("Cannot flush output, port is not open.");
	} 

	PurgeComm(FileHandle, PURGE_TXCLEAR);
}

void Serial::SerialImpl::ReadLock()
{
	if (WaitForSingleObject(ReadMutex, INFINITE) != WAIT_OBJECT_0) 
	{
		throw std::runtime_error("Error claiming read mutex.");
	}
}

void Serial::SerialImpl::ReadUnlock()
{
	if (!ReleaseMutex(ReadMutex)) 
	{
		throw std::runtime_error("Error releasing read mutex.");
	}
}

void Serial::SerialImpl::WriteLock()
{
	if (WaitForSingleObject(WriteMutex, INFINITE) != WAIT_OBJECT_0)
	{
		throw std::runtime_error("Error claiming write mutex.");
	}
}

void Serial::SerialImpl::WriteUnlock()
{
	if (!ReleaseMutex(WriteMutex))
	{
		throw std::runtime_error("Error releasing write mutex.");
	}
}

#endif