#include <assert.h>

#if _WIN32
#define NOMINMAX
#include <windows.h>
#elif __APPLE__
#include <fcntl.h>
#include <ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#endif

#include "serial.h"

Serial::Serial()
	: IsOpen(false)
{}

Serial::~Serial()
{
	Close();
}

void Serial::Open()
{
#if _WIN32
	FileHandle = CreateFileA("COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	assert(FileHandle != INVALID_HANDLE_VALUE);
#elif __APPLE__
	FileHandle = open("COM3", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (FileHandle == -1 && errno == EINTR) {
		// Recurse, this just means the request was interrupted
		Open();
		return;
	}
	assert(FileHandle != -1);
#endif

	Reset();
	IsOpen = true;
}

void Serial::Close()
{
	if (IsOpen)
	{
#if _WIN32
		assert(FileHandle != INVALID_HANDLE_VALUE);
		CloseHandle(FileHandle);
		FileHandle = INVALID_HANDLE_VALUE;
#elif __APPLE__
		assert(FileHandle != -1);
		close(FileHandle);
		FileHandle = -1;
#endif

		IsOpen = false;
	}
}

void Serial::Reset()
{
#if _WIN32
	assert(FileHandle != INVALID_HANDLE_VALUE);

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate = 256000;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.fOutxCtsFlow = false;
	dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
	dcbSerialParams.fOutX = false;
	dcbSerialParams.fInX = false;
	
	// Setup timeouts
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = UINT32_MAX;
	timeouts.ReadTotalTimeoutConstant = 1000;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 1000;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	// Apply settings
	SetCommTimeouts(FileHandle, &timeouts);
	SetCommState(FileHandle, &dcbSerialParams);
#elif __APPLE__
	assert(FileHandle != -1);

	struct termios options;
	tcgetattr(FileHandle, &options);

	// Setup baud rate
	ioctl(FileHandle, IOSSIOSPEED, 256000, 1);

	// Setup flags
	options.c_iflag &= (tcflag_t) ~(INLCR | IGNCR | ICRNL | IGNBRK);
	options.c_oflag &= (tcflag_t) ~(OPOST | ONLCR | OCRNL);
	options.c_lflag &= (tcflag_t) ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS);
	options.c_cflag |= (tcflag_t) (CLOCAL | CREAD | CS8);
	options.c_lflag &= (tcflag_t) ~(ICANON | ISIG | ECHO);

	// Apply settings
	tcsetattr(FileHandle, TCSANOW, &options);
#endif
}

size_t Serial::GetAvailableBufferSize()
{
	assert(IsOpen);

#if _WIN32
	COMSTAT commStats;
	ClearCommError(FileHandle, NULL, &commStats);
	return static_cast<size_t>(commStats.cbInQue);
#elif __APPLE__
	int count = 0;
	ioctl(FileHandle, FIONREAD, &count);
	return static_cast<size_t>(count);
#endif
}

size_t Serial::Read(uint8_t* buffer, size_t size)
{
	assert(IsOpen);

#if _WIN32
	DWORD bytesRead;
	ReadFile(FileHandle, buffer, static_cast<DWORD>(size), &bytesRead, NULL);
#elif __APPLE__
	size_t bytesRead = read(FileHandle, buffer, size);
#endif

	return (size_t)bytesRead;
}

size_t Serial::Write(const uint8_t* data, size_t size)
{
	assert(IsOpen);

#if _WIN32
	DWORD bytesWritten;
	WriteFile(FileHandle, data, static_cast<DWORD>(size), &bytesWritten, NULL);
#elif __APPLE__
	size_t bytesWritten = write(FileHandle, data, size);
#endif

	return (size_t)bytesWritten;
}

void Serial::Flush()
{
	assert(IsOpen);

#if _WIN32
	FlushFileBuffers(FileHandle);
#elif __APPLE__
	tcdrain(FileHandle);
#endif
}

void Serial::FlushInput()
{
	assert(IsOpen);

#if _WIN32
	PurgeComm(FileHandle, PURGE_RXCLEAR);
#elif __APPLE__
	tcflush(FileHandle, TCIFLUSH);
#endif
}

void Serial::FlushOutput()
{
	assert(IsOpen);

#if _WIN32
	PurgeComm(FileHandle, PURGE_TXCLEAR);
#elif __APPLE__
	tcflush(FileHandle, TCOFLUSH);
#endif
}