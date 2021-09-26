#pragma once

#include <stdint.h>

class Serial 
{
public:

	Serial();
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

private:

	bool IsOpen;

#if _WIN32
	void* FileHandle;
#elif __APPLE__
	int FileHandle;
#endif

};
