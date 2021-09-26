#include <stdio.h>

#include "dme7000.h"
#include "enums.h"
#include "imgui.h"

DME7000::DME7000(const U8 inChannel) 
	: Channel(inChannel)
	, SubPictureId(0x00)
	, GraphicGui(this)
{
	SerialConfig = SerialConfiguration("COM3", 256000);
	SerialComms = Serial(SerialConfig);
	SerialComms.Open();
}

DME7000::~DME7000()
{
	SerialComms.Close();
}

void DME7000::DrawGUI()
{
	ImGui::ShowDemoWindow();
	
	/*
	ImGui::Begin("Hello, world!");

	GraphicGui.DrawGUI();

	if (ImGui::Button("Test Input Freeze"))
	{
		Background_Color_Hue.Value = 0x7FFF;
		OnParameterChanged(Background_Color_Hue);
	}

	ImGui::End();
	*/
}

void DME7000::OnParameterChanged(const Parameter& changedParameter)
{
	if (changedParameter.IsValid())
	{
		U8 outChannel = Channel;
		size_t size;
		Packet packet;
		
		if (changedParameter.Flags & ParameterFlags_Global) {
			outChannel = 0x80;
		}

		if (changedParameter.Flags & ParameterFlags_SubPicture) {
			changedParameter.GetPacket(outChannel, SubPictureId, size);
		} else {
			changedParameter.GetPacket(outChannel, size);
		}

		size_t bytesWritten = SerialComms.Write(&packet[0], packet.size());

		printf("Parameter changed: %s %d bytes, wrote %d bytes\n", changedParameter.Name, size, bytesWritten);
	}
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