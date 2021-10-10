#pragma once

#include "types.h"

struct DME7000;

struct Debug
{
	struct Tests
	{
		static void SendSingleFullPacket(DME7000* DME);
		static void SendTooManyFullPackets(DME7000* DME);
	};

	static void PrintPackets(const char* prefix, const uint8_t* packetBuffer, const size_t bufferSize);

};