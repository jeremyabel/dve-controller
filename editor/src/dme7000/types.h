#pragma once

#include <array>

#define NAME_NONE "NONE"
#define U8_MAX 0xFF

typedef signed char    S8;
typedef unsigned char  U8;
typedef signed short   S16;
typedef unsigned short U16;
typedef float          F32;

typedef std::array<U8, 9> Packet;

typedef int ParameterFlags;
enum ParameterFlags_
{
	ParameterFlags_None        = 0,
	ParameterFlags_Global      = 1 << 0,
	ParameterFlags_SubPicture  = 1 << 1
};

struct Parameter 
{
	const U8 Module = U8_MAX;
	const U8 Id = U8_MAX;
	const char* Name = NAME_NONE;
	const ParameterFlags Flags = 0;
	
	virtual Packet GetPacket(const U8 channel, size_t& size) const = 0;
	virtual Packet GetPacket(const U8 channel, const U8 subId, size_t& size) const  = 0;

	bool IsValid() const
	{
		return Module != U8_MAX && Id != U8_MAX && Name != NAME_NONE;
	}

	Parameter(const U8 inModule, const U8 inId, const char* inName, const ParameterFlags inFlags = 0)
		: Module(inModule) 
		, Id(inId)
		, Name(inName)
		, Flags(inFlags)
	{}
};

struct Parameter_Bool : public Parameter
{
	bool Value;

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		size = 5;
		Packet packet = { 0x04, channel, Module, Id, Value };
		return packet;
	}

	Packet GetPacket(const U8 channel, const U8 subId, size_t& size) const
	{
		size = 6;
		Packet packet = { 0x05, channel, Module, Id, Value, subId };
		return packet;
	}

	using Parameter::Parameter;
};

struct Parameter_Enum : public Parameter
{
	U8 Value;

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		size = 5;
		Packet packet = { 0x04, channel, Module, Id, Value };
		return packet;
	}

	Packet GetPacket(const U8 channel, const U8 subId, size_t& size) const
	{
		size = 6;
		Packet packet = { 0x05, channel, Module, Id, Value, subId };
		return packet;
	}

	using Parameter::Parameter;
};

struct Parameter_S16 : public Parameter
{
	S16 Value;

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		size = 6;
		Packet packet = { 0x05, channel, Module, Id, (U8)((Value >> 8) & 0xFF), (U8)(Value & 0xFF) };
		return packet;
	}

	Packet GetPacket(const U8 channel, const U8 subId, size_t& size) const
	{
		size = 7;
		Packet packet = { 0x06, channel, Module, Id, (U8)((Value >> 8) & 0xFF), (U8)(Value & 0xFF), subId };
		return packet;
	}

	using Parameter::Parameter;
};

struct Parameter_F32 : public Parameter
{
	F32 Value;

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		U8 valueBytes[4];
		memcpy(valueBytes, &Value, sizeof(F32));

		size = 8;
		Packet packet = { 0x07, channel, Module, Id, valueBytes[3], valueBytes[2], valueBytes[1], valueBytes[0] };
		return packet;
	}

	Packet GetPacket(const U8 channel, const U8 subId, size_t& size) const
	{
		U8 valueBytes[4];
		memcpy(valueBytes, &Value, sizeof(F32));

		size = 9;
		Packet packet = { 0x08, channel, Module, Id, valueBytes[3], valueBytes[2], valueBytes[1], valueBytes[0], subId };
		return packet;
	}

	using Parameter::Parameter;
};

struct Parameter_F32_Light : public Parameter_F32
{
	const U8 LightId;

	Parameter_F32_Light(const U8 inModule, const U8 inLightId, const U8 inParameterId, const char* inName, const ParameterFlags inFlags = 0)
		: Parameter_F32(inModule, inParameterId, inName, inFlags)
		, LightId(inLightId)
	{}

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		U8 valueBytes[4];
		memcpy(valueBytes, &Value, sizeof(F32));

		size = 9;
		Packet packet = { 0x08, channel, Module, LightId, Id, valueBytes[3], valueBytes[2], valueBytes[1], valueBytes[0] };
		return packet;
	}
};

struct Parameter_Enum_Video : public Parameter_Enum
{
	const U8 SourceId;

	Parameter_Enum_Video(const U8 inModule, const U8 inSourceId, const U8 inParameterId, const char* inName, const ParameterFlags inFlags = 0)
		: Parameter_Enum(inModule, inParameterId, inName, ParameterFlags_Global | inFlags)
		, SourceId(inSourceId)
	{}

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		size = 7;
		Packet packet = { 0x06, channel, Module, Id, SourceId, SourceId, Value };
		return packet;
	}
};

struct Parameter_S16_Video : public Parameter_S16
{
	const U8 SourceId;

	Parameter_S16_Video(const U8 inModule, const U8 inSourceId, const U8 inParameterId, const char* inName, const ParameterFlags inFlags = 0)
		: Parameter_S16(inModule, inParameterId, inName, ParameterFlags_Global | inFlags)
		, SourceId(inSourceId)
	{}

	Packet GetPacket(const U8 channel, size_t& size) const
	{
		size = 8;
		Packet packet = { 0x07, channel, Module, Id, SourceId, SourceId, (U8)((Value >> 8) & 0xFF), (U8)(Value & 0xFF) };
		return packet;
	}
};
