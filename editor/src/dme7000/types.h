#pragma once

#define NAME_NONE "NONE"


typedef signed char		S8;
typedef unsigned char	U8;
typedef signed short	S16;
typedef unsigned short	U16;
typedef float			F32;

typedef int ParameterFlags;
enum ParameterFlags_
{
	ParameterFlags_None        = 0,
	ParameterFlags_Global      = 1 << 0,
	ParameterFlags_SubPicture  = 2 << 1
};

struct Parameter 
{
	const U8 Module;
	const U8 Id;
	const char* Name;
	const ParameterFlags Flags;
	
	virtual unsigned char* GetPacket(const U8 channel) { return nullptr; }
	virtual unsigned char* GetPacket(const U8 channel, const U8 controlId) { return nullptr; }

	Parameter() 
		: Module(0xFF)
		, Id(0xFF)
		, Name(NAME_NONE)
		, Flags(0)
	{}

	Parameter(const U8 inModule, const U8 inId, const char* inName, ParameterFlags inFlags = 0) 
		: Module(inModule) 
		, Id(inId)
		, Name(inName)
		, Flags(inFlags)
	{}
};

struct Parameter_Bool : public Parameter
{
	using Parameter::Parameter;

	bool Value;

	unsigned char* GetPacket(const U8 channel) const
	{
		unsigned char packet[5] = { 0x04, channel, Module, Id, Value };
		return packet;
	}

	unsigned char* GetPacket(const U8 channel, const U8 controlId) const
	{
		unsigned char packet[6] = { 0x05, channel, Module, Id, Value, controlId };
		return packet;
	}
};

struct Parameter_Enum : public Parameter
{
	using Parameter::Parameter;

	U8 Value;

	unsigned char* GetPacket(const U8 channel) const
	{
		unsigned char packet[5] = { 0x04, channel, Module, Id, Value };
		return packet;
	}

	unsigned char* GetPacket(const U8 channel, const U8 controlId) const
	{
		unsigned char packet[6] = { 0x05, channel, Module, Id, Value, controlId };
		return packet;
	}
};

struct Parameter_S16 : public Parameter
{
	using Parameter::Parameter;

	S16 Value;

	unsigned char* GetPacket(const U8 channel) const
	{
		//char packet[6] = { 0x05, channel, module, id, value };
		return nullptr;
	}

	unsigned char* GetPacket(const U8 channel, const U8 controlId) const
	{
		//char packet[7] = { 0x06, channel, module, id, value, controlId };
		return nullptr;
	}
};

struct Parameter_F32 : public Parameter
{
	using Parameter::Parameter;

	F32 Value;

	unsigned char* GetPacket(const U8 channel) const
	{
		return nullptr;
	}

	unsigned char* GetPacket(const U8 channel, const U8 controlId) const
	{
		return nullptr;
	}
};

struct Parameter_F32_Light : public Parameter_F32
{
	const U8 LightId;

	Parameter_F32_Light(const U8 inModule, const U8 inLightId, const U8 inParameterId, const char* inName, const ParameterFlags inFlags = 0)
		: Parameter_F32(inModule, inParameterId, inName, inFlags)
		, LightId(inLightId)
	{}

	unsigned char* GetPacket(const U8 channel) const
	{
		return nullptr;
	}
};

struct Parameter_Enum_Video : public Parameter_Enum
{
	const U8 SourceId;

	Parameter_Enum_Video(const U8 inModule, const U8 inSourceId, const U8 inParameterId, const char* inName, const ParameterFlags inFlags = 0)
		: Parameter_Enum(inModule, inParameterId, inName, ParameterFlags_Global | inFlags)
		, SourceId(inSourceId)
	{}

	unsigned char* GetPacket(const U8 channel) const
	{
		unsigned char packet[7] = { 0x06, channel, Module, Id, SourceId, SourceId, Value };
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

	unsigned char* GetPacket(const U8 channel) const
	{
		return nullptr;
	}
};
