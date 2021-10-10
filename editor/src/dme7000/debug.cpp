#include <stdio.h>

#include "debug.h"
#include "dme7000.h"

void Debug::PrintPackets(const char* prefix, const uint8_t* packetBuffer, const size_t bufferSize)
{
	printf("%s", prefix);
	for (size_t i = 0; i < bufferSize; i++)
		printf("%02hhX ", packetBuffer[i]);
	printf("\n");
}

void Debug::Tests::SendSingleFullPacket(DME7000* DME)
{
	DME->ColorCorrection_Primary_Curve_R_1_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_1_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_2_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_2_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_3_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_3_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_4_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_4_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_5_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_5_Y.Value = 0x7FFF;

	// 10 * 6 bytes = 60 bytes
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_1_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_1_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_2_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_2_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_3_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_3_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_4_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_4_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_5_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_5_Y);
}

void Debug::Tests::SendTooManyFullPackets(DME7000* DME)
{
	DME->ColorCorrection_Primary_Curve_R_1_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_1_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_2_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_2_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_3_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_3_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_4_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_4_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_5_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_R_5_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_1_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_1_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_2_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_2_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_3_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_3_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_4_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_4_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_5_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_G_5_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_1_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_1_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_2_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_2_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_3_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_3_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_4_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_4_Y.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_5_X.Value = 0x7FFF;
	DME->ColorCorrection_Primary_Curve_B_5_Y.Value = 0x7FFF;

	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_1_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_1_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_2_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_2_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_3_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_3_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_4_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_4_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_5_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_R_5_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_1_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_1_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_2_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_2_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_3_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_3_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_4_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_4_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_5_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_G_5_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_1_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_1_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_2_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_2_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_3_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_3_Y);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_4_X);
	DME->OnParameterChanged(DME->ColorCorrection_Primary_Curve_B_4_Y);
}