#include <stdlib.h>
#include <stdio.h>

#include "../editor.h"
#include "dme7000.h"
#include "enums.h"
#include "debug.h"
#include "imgui.h"

#define MAX_BYTES_PER_FRAME 60

DME7000::DME7000(Editor* inEditor, const U8 inChannel) 
	: EditorRef(inEditor)
	, Channel(inChannel)
	, SubPictureId(0x00)
	, GraphicGui(this)
{}

DME7000::~DME7000()
{}

void DME7000::Init()
{	
	const uint8_t initPacket[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };
	EditorRef->SerialComms.Write(initPacket, sizeof(initPacket));
	Debug::PrintPackets("Transmit: ", initPacket, sizeof(initPacket) / sizeof(uint8_t));
}

void DME7000::Tick()
{	
	Debug::Tests::SendSingleFullPacket(this);

	// Fill the priority queues
	for (std::pair<const Parameter*, PacketPriority> element : ModifiedParametersByPriority)
	{
		switch (element.second)
		{
			case PacketPriority_Low: ModifiedParameters_LowPriority.push(element.first); break;
			case PacketPriority_High: ModifiedParameters_HighPriority.push(element.first); break;
		}
	}

	ModifiedParametersByPriority.clear();

	std::vector<U8> packets = { 0x02, 0x80, 0x86 }; // Header bytes
	packets.reserve(MAX_BYTES_PER_FRAME);

	// Accumulate packets until we run out of space or there are no more packets to transmit
	while (packets.size() < MAX_BYTES_PER_FRAME)
	{
		ParameterQueue* targetQueue = nullptr;

		// Check packet queues in order of priority
		if (!ModifiedParameters_HighPriority.empty()) {
			targetQueue = &ModifiedParameters_HighPriority;
		} else if (!ModifiedParameters_LowPriority.empty()) {
			targetQueue = &ModifiedParameters_LowPriority;
		} else {
			break;
		}
		
		const Parameter* modifiedParameter = targetQueue->front();

		size_t packetSize;
		Packet packet = GetParameterPacket(modifiedParameter, packetSize);

		// Only add the packet if the whole thing will fit
		if (MAX_BYTES_PER_FRAME - packets.size() >= packetSize)
		{
			packets.insert(packets.end(), packet.data(), packet.data() + packetSize);
			targetQueue->pop();
		}
		else
		{
			break;
		}
	}

	// Transmit accumulated packets
	if (packets.size() > 3) // @TODO: Replace with non-magic-number
	{
		Debug::PrintPackets("Transmit: ", packets.data(), packets.size());
		EditorRef->SerialComms.Write(&packets[0], packets.size() * sizeof(U8));
	}
}

void DME7000::DrawGUI()
{
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Hello, world!");

	GraphicGui.DrawGUI();

	if (ImGui::Button("Send Test Packets"))
	{
		Debug::Tests::SendSingleFullPacket(this);
	}

	ImGui::End();
}

void DME7000::OnParameterChanged(const Parameter& changedParameter, const PacketPriority priority)
{
	if (changedParameter.IsValid())
	{
		const bool insertResult = ModifiedParametersByPriority.insert({&changedParameter, priority}).second;
		if (!insertResult)
		{
			PacketPriority& currentPriority = ModifiedParametersByPriority[&changedParameter];
			if (currentPriority < priority)
			{
				currentPriority = priority;
			}
		}
	}
}

Packet DME7000::GetParameterPacket(const Parameter* parameter, size_t& outSize)
{
	Packet result;

	// Parameters with the Global flag use 0x80 as their channel
	U8 outChannel = parameter->Flags & ParameterFlags_Global ? 0x80 : Channel;

	if (parameter->Flags & ParameterFlags_SubPicture) {
		result = parameter->GetPacket(outChannel, SubPictureId, outSize);
	} else {
		result = parameter->GetPacket(outChannel, outSize);
	}
	
	return result;
}

void DME7000::InputFreeze_Setup(const bool Enabled, const U8 EffectType)
{
	// Default setup for Hard Freeze
	Parameter_Bool* EnableParamA = &InputFreeze_Enable_A; // Param: 0x90, 0x30
	Parameter_Bool* EnableParamB = &InputFreeze_Enable_C; // Param: 0x90, 0x33
	InputFreezeMode Mode = InputFreezeMode_Frame;

	if (EffectType == InputFreezeEffectType_LastFreeze)
	{
		EnableParamA = &InputFreeze_Enable_B; // Param: 0x90, 0x32
		EnableParamB = &InputFreeze_Enable_D; // Param: 0x90, 0x34
	}

	switch (EffectType)
	{
		case InputFreezeEffectType_TimeStrobe: Mode = InputFreezeMode_TimeStrobe; break;
		case InputFreezeEffectType_KFStrobe:   Mode = InputFreezeMode_KFStrobe; break;
		case InputFreezeEffectType_Film:       Mode = InputFreezeMode_Film; break;
	}

	EnableParamA->Value = EnableParamB->Value = Enabled;
	OnParameterChanged(*EnableParamA);
	OnParameterChanged(*EnableParamB);

	if (Enabled)
	{
		InputFreeze_Mode_A.Value = InputFreeze_Mode_B.Value = Mode;
		OnParameterChanged(InputFreeze_Mode_A);
		OnParameterChanged(InputFreeze_Mode_B);
	}
}

void DME7000::RecursiveTrails_Setup(const bool Enabled, const U8 Mode)
{
	RecursiveTrails_Enable.Value = Enabled;
	OnParameterChanged(RecursiveTrails_Enable);

	if (Mode == RecursiveTrailsMode_Wind)
	{
		RecursiveTrails_Wind.Value = true;
		OnParameterChanged(RecursiveTrails_Wind);
	}

	if (Enabled)
	{
		RecursiveTrails_Mode.Value = Mode;
		OnParameterChanged(RecursiveTrails_Mode);
	}
}

void DME7000::NonLinear_Setup(const bool Enabled, const U8 Effect)
{
	NonLinear_Enable.Value = Enabled;
	OnParameterChanged(NonLinear_Enable);

	if (Enabled)
	{
		U8 Setup1 = U8_MAX; // Param: 0x92, 0xA0
		U8 Setup2 = U8_MAX; // Param: 0x92, 0xC8

		switch (Effect)
		{
			case NonLinearEffect_Wave:           Setup1 = 0x04; break;
			case NonLinearEffect_MosaicGlass:    Setup1 = 0x06; break;
			case NonLinearEffect_Flag:           Setup1 = 0x07; break;
			case NonLinearEffect_Ripple:         Setup1 = 0x05; break;
			case NonLinearEffect_Rings:          Setup1 = 0x0A; Setup2 = 0x01; break;
			case NonLinearEffect_BrokenGlass:    Setup1 = 0x0A; Setup2 = 0x02; break;
			case NonLinearEffect_FlyingBars:     Setup1 = 0x0A; Setup2 = 0x03; break;
			case NonLinearEffect_SplitSlide:     Setup1 = 0x0C; break;
			case NonLinearEffect_CharacterTrail: Setup1 = 0x0E; break;
			case NonLinearEffect_Lens:           Setup1 = 0x0B; break;
			case NonLinearEffect_Circle:         Setup1 = 0x16; break;
			case NonLinearEffect_Panorama:       Setup1 = 0x08; break;
			case NonLinearEffect_PageTurn:       Setup1 = 0x00; break;
			case NonLinearEffect_Roll:           Setup1 = 0x01; break;
			case NonLinearEffect_Cylinder:       Setup1 = 0x02; break;
			case NonLinearEffect_Sphere:         Setup1 = 0x03; break;
			case NonLinearEffect_Twist:          Setup1 = 0x09; break;
			case NonLinearEffect_Explosion:      Setup1 = 0x0A; Setup2 = 0x04; break;
			case NonLinearEffect_Swirl:          Setup1 = 0x11; break;
			case NonLinearEffect_Blind:          Setup1 = 0x12; break;
			case NonLinearEffect_Kaleidoscope:   Setup1 = 0x13; break;
			case NonLinearEffect_MultiMirror:    Setup1 = 0x14; break;
			case NonLinearEffect_Melt:           Setup1 = 0x15; break;
		}

		if (Setup1 != U8_MAX)
		{
			NonLinear_Setup_1.Value = Setup1;
			OnParameterChanged(NonLinear_Setup_1);
		}

		if (Setup2 != U8_MAX)
		{
			NonLinear_Setup_2.Value = Setup2;
			OnParameterChanged(NonLinear_Setup_2);
		}
	}
}
